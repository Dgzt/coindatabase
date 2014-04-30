#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtSql/QSqlDatabase>

class LocalDatabase;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    LocalDatabase *m_localDatabase;

    QTableWidget *coinsTable;
public:
    MainWindow( QWidget *parent = 0 );
    ~MainWindow();

private:
    /*!
     * Create the menu.
     */
    void createMenu();

    void checkLocalFiles();

private slots:
    void countriesDialogSlot();

    void exitSlot();

    void addCoinSlot();

};

#endif // MAINWINDOW_H
