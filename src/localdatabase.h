#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H

#include <QSqlDatabase>

class LocalDatabase
{
    QSqlDatabase m_database;

public:
    /*!
     * Setup the local database.
     *
     * @param databasePath The path of the local database.
     */
    LocalDatabase( QString databasePath );

    /*!
     * Open the database connection.
     *
     * @return
     */
    bool open(){ return m_database.open(); }

    /*!
     * Close the database connection.
     */
    void close(){ m_database.close(); }

    /*!
     * Have countries table in the database.
     *
     * @return
     */
    bool haveCountriesTable();

    /*!
     * Create countries table in the database.
     *
     * @return
     */
    bool createCountriesTable();

};

#endif // LOCALDATABASE_H
