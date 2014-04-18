#include <QDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDateTime>
#include "localdatabase.h"

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
