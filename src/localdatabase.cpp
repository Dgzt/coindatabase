#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QObject>
#include <QtWidgets/QTableWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDateTime>
#include <QtSql/QSqlResult>
#include "localdatabase.h"

const QString LocalDatabase::EMPTY_NAME = "";

const QString DATABASE_DRIVER = "QSQLITE";

const int NAME_LENGTH_IN_COUNTRIES_TABLE = 64;

LocalDatabase::LocalDatabase( QString databasePath )
{
    m_database = QSqlDatabase::addDatabase( DATABASE_DRIVER );
    m_database.setDatabaseName( databasePath );
}

bool LocalDatabase::haveCountriesTable()
{
    return m_database.tables().contains( "countries" );
}

bool LocalDatabase::createCountriesTable()
{
    QSqlQuery query(m_database);
    bool ret = query.exec( QString("CREATE TABLE countries (")+
                                QString("id               INTEGER PRIMARY KEY,")+
                                QString("id_server        BIGINT,")+
                                QString("name             VARCHAR("+QString::number(NAME_LENGTH_IN_COUNTRIES_TABLE)+") NOT NULL,")+
                                QString("deleted          BOOLEAN DEFAULT 0 NOT NULL CHECK (deleted IN (0,1)),")+
                                QString("modified_date      DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL")+
                             QString(")"));

    if( !ret ){
        qDebug() << "Cannot create countries table: " << query.lastError().text();
    }

    return ret;
}

QSqlTableModel* LocalDatabase::getCountriesModel()
{
    QSqlTableModel *model = new QSqlTableModel( 0, m_database );
    model->setTable("countries");
    model->setFilter("deleted = 0");
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    model->select();

    return model;
}

int LocalDatabase::getMaxCountryNameLength()
{
    return NAME_LENGTH_IN_COUNTRIES_TABLE;
}

bool LocalDatabase::insertCountry( QString name )
{
    QSqlQuery query(m_database);
    bool ret = query.exec( "INSERT INTO countries(name,deleted,modified_date) VALUES ('"+name+"',0,'"+QDateTime::currentDateTime().toString()+"')" );

    if( !ret ){
        qDebug() << "Cannot insert into countries table:" << query.lastError().text();
    }

    return ret;
}

bool LocalDatabase::removeCountry( int id )
{
    QSqlQuery query( m_database );

    query.prepare("UPDATE countries SET deleted = 1 , modified_date = :current_date WHERE id = :id");
    query.bindValue( ":id", id);
    query.bindValue( ":current_date", QDateTime::currentDateTime().toString() );

    bool ret = query.exec();

    if( !ret ){
        qDebug() << "Cannot update the countries table:" << query.lastError().text();
    }

    return ret;
}

bool LocalDatabase::updateCountry( int id, QString name )
{
    QSqlQuery query( m_database );

    query.prepare( "UPDATE countries SET name = ':name', modified_date = :current_date WHERE id = :id" );
    query.bindValue( ":id", id );
    query.bindValue( ":name", name );
    query.bindValue( ":current_date", QDateTime::currentDateTime().toString() );

    bool ret = query.exec();

    if( !ret ){
        qDebug() << "Cannot update the countries table:" << query.lastError().text();
    }

    return ret;
}

bool LocalDatabase::haveCoinsTable()
{
    return m_database.tables().contains("coins");
}

bool LocalDatabase::createCoinsTable()
{
    QSqlQuery query( m_database );

    query.prepare( QString("CREATE TABLE coins (" )+
                    QString("id                 INTEGER PRIMARY KEY,")+
                    QString("id_server          BIGINT,")+
                    QString("name               VARCHAR(32),")+
                    QString("country_id         BIGINT,")+
                    QString("year               INT,")+
                    QString("head_image_url     VARCHAR(128),")+
                    QString("head_image         BLOB NOT NULL,")+
                    QString("tail_image_url     VARCHAR(128),")+
                    QString("tail_image         BLOB NOT NULL,")+
                    QString("deleted            BOOLEAN NOT NULL CHECK (deleted IN (0,1)),")+
                    QString("modified_date      DATETIME NOT NULL,")+
                    QString("FOREIGN KEY (country_id) REFERENCES countries(id)")+
                   QString(")"));

    bool ret = query.exec();

    if( !ret ){
        qDebug() << "Cannot create coins table:" << query.lastError().text();
    }

    return ret;
}

void LocalDatabase::loadCoinsTable( QTableWidget *table )
{
    table->clearContents();

    QSqlQuery query( m_database );

    QString queryString;
    queryString.append( "SELECT " );
    queryString.append("   coins.id as coins_id, ");
    queryString.append("   coins.name as coins_name, ");
    queryString.append("   countries.name as countries_name, ");
    queryString.append("   coins.year as coins_year ");
    queryString.append("FROM coins LEFT JOIN countries ");
    queryString.append("ON coins.country_id = countries.id");

    bool ret = query.exec( queryString );

    if( ret ){

        while( query.next() ){
            table->insertRow( table->rowCount() );
            table->setItem( table->rowCount()-1, 0, new QTableWidgetItem( query.value("coins_id").toString() ) );
            table->setItem( table->rowCount()-1, 1, new QTableWidgetItem( query.value("coins_name").toString() ) );
            table->setItem( table->rowCount()-1, 2, new QTableWidgetItem( query.value("countries_name").toString() ) );
            table->setItem( table->rowCount()-1, 3, new QTableWidgetItem( query.value("coins_year").toString() ) );
        }

    }else{
        qDebug() << "Cannot sleect coins table:" << query.lastError().text();
    }
}

QList<QPair<int,QString> > LocalDatabase::getCountryList()
{
    QSqlQuery query( m_database );

    query.exec( "SELECT id,name FROM countries WHERE deleted = 0" );

    QList<QPair<int,QString> > countryList;

    while( query.next() ){
        QPair<int,QString> pair;
        pair.first = query.value("id").toInt();
        pair.second = query.value("name").toString();
        countryList.append( pair );
    }

    return countryList;
}

bool LocalDatabase::insertCoin( QString headImagePath, QString tailImagePath, QString name, int countryId, int year )
{
    QString queryString = "INSERT INTO coins(";

    if( name != EMPTY_NAME ){
        queryString += "name,";
    }
    if( countryId != EMPTY_COUNTRY_ID ){
        queryString += "country_id,";
    }
    if( year != EMPTY_YEAR ){
        queryString += "year,";
    }

    queryString += "head_image,tail_image,deleted,modified_date) values(";

    if( name != EMPTY_NAME ){
        queryString += ":name,";
    }
    if( countryId != EMPTY_COUNTRY_ID ){
        queryString += ":countryId,";
    }
    if( year != EMPTY_YEAR ){
        queryString += ":year,";
    }

    queryString += ":headImage,:tailImage,:deleted,:modifiedDate)";
    qDebug() << queryString;

    QFile headFile(headImagePath);
    if( !headFile.open( QIODevice::ReadOnly ) ) return false;
    QByteArray headByteArray = headFile.readAll();
    headFile.close();

    QFile tailFile(tailImagePath);
    if( !tailFile.open( QIODevice::ReadOnly ) ) return false;
    QByteArray tailByteArray = tailFile.readAll();
    tailFile.close();

    QSqlQuery query( m_database );
    query.prepare( queryString );
    if( name != EMPTY_NAME ){
        query.bindValue( ":name", name );
    }
    if( countryId != EMPTY_COUNTRY_ID ){
        query.bindValue( ":countryId", countryId );
    }
    if( year != EMPTY_YEAR ){
        query.bindValue( ":year", year );
    }

    query.bindValue( ":headImage", headByteArray );
    query.bindValue( ":tailImage", tailByteArray );
    query.bindValue( ":deleted", 0 );
    query.bindValue( ":modifiedDate", QDateTime::currentDateTime().toString() );

    bool ret = query.exec();

    if( !ret ){
        qDebug() << "Cannot insert to coins table:" << query.lastError().text();
    }
    return ret;
}
