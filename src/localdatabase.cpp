#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "localdatabase.h"

const QString DATABASE_DRIVER = "QSQLITE";

const QString COUNTRIES_TABLE = "countries";

const int NAME_LENGTH_IN_COUNTRIES_TABLE = 64;

LocalDatabase::LocalDatabase( QString databasePath )
{
    m_database = QSqlDatabase::addDatabase( DATABASE_DRIVER );
    m_database.setDatabaseName( databasePath );
}

bool LocalDatabase::haveCountriesTable()
{
    return m_database.tables().contains( COUNTRIES_TABLE );
}

bool LocalDatabase::createCountriesTable()
{
    QSqlQuery query(m_database);
    bool ret = query.exec( QString("CREATE TABLE "+ COUNTRIES_TABLE +" (")+
                                QString("id               INTEGER PRIMARY KEY,")+
                                QString("id_server        BIGINT,")+
                                QString("name             VARCHAR("+QString::number(NAME_LENGTH_IN_COUNTRIES_TABLE)+") NOT NULL,")+
                                QString("deleted          BOOLEAN NOT NULL CHECK (deleted IN (0,1)),")+
                                QString("modified_date      DATETIME NOT NULL")+
                             QString(")"));

    if( !ret ){
        qDebug() << "Cannot create "+COUNTRIES_TABLE+" table: " << query.lastError().text();
    }

    return ret;
}
