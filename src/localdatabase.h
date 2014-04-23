#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H

#include <QSqlDatabase>

class QSqlTableModel;

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

    /*!
     * Get the model of countries.
     *
     * @return The model of countries.
     */
    QSqlTableModel* getCountriesModel();

    /*!
     * Get the max length of name of country.
     *
     * @return The max length of name of country.
     */
    int getMaxCountryNameLength();

    /*!
     * Insert a country.
     *
     * @param name The name of the country.
     * @return The success of insert.
     */
    bool insertCountry( QString name );

    /*!
     * Remove the country where id equal woth the given id.
     *
     * @param id The id.
     * @return The success of insert.
     */
    bool removeCountry( int id );

    /*!
     * Update the country with current date.
     *
     * @param id The id of modified country.
     * @param name The new name of the country.
     * @return The success of update.
     */
    bool updateCountry( int id, QString name );

    /*!
     * Check have 'cions' table.
     *
     * @return Have 'cions' table.
     */
    bool haveCoinsTable();

    /*!
     * Create 'cions' table.
     *
     * @return Success the table creating.
     */
    bool createCoinsTable();

    /*!
     * Get the model of the coins table.
     *
     * @return The model of cions table.
     */
    QSqlTableModel* getCoinsModel();

};

#endif // LOCALDATABASE_H
