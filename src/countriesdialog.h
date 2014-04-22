#ifndef COUNTRIESDIALOG_H
#define COUNTRIESDIALOG_H

#include <QDialog>

class LocalDatabase;
class QSqlTableModel;
class QTableView;

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

    /*!
     * The countries table view.
     */
    QTableView *countriesView;

public:
    /*!
     * Setup the dialog with widget components.
     *
     * @param localDatabase The local database.
     * @param parent The parent widget.
     */
    CountriesDialog( LocalDatabase *localDatabase ,QWidget *parent = 0 );

private slots:
    /*!
     * The popup menu for countries table.
     *
     * @param pos The position of the mouse.
     */
    void customMenuRequested( QPoint pos );

    /*!
     * Show the AddCountryDialog and add the given country.
     */
    void addSlot();

    /*!
     * Remove the selected rows.
     */
    void removeSlot();
};

#endif // COUNTRIESDIALOG_H
