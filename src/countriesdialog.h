#ifndef COUNTRIESDIALOG_H
#define COUNTRIESDIALOG_H

#include <QDialog>

class LocalDatabase;
class QSqlTableModel;

class CountriesDialog : public QDialog
{
    Q_OBJECT

    /*!
     * The local database.
     */
    LocalDatabase *m_localDatabase;

    /*!
     * The sql table model.
     */
    QSqlTableModel *tableModel;

public:
    /*!
     * Setup the dialog with widget components.
     *
     * @param localDatabase The local database.
     * @param parent The parent widget.
     */
    CountriesDialog( LocalDatabase *localDatabase ,QWidget *parent = 0 );

public slots:
    /*!
     * Show the AddCountryDialog and add the given country.
     */
    void addSlot();
};

#endif // COUNTRIESDIALOG_H
