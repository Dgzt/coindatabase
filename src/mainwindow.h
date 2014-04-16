#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtSql/QSqlDatabase>

class LocalDatabase;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //QSqlDatabase localDb;
    LocalDatabase *m_localDatabase;

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

};

#endif // MAINWINDOW_H
