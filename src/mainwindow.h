#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

class MainWindow : public QMainWindow
{

    QSqlDatabase localDb;

public:
    MainWindow( QWidget *parent = 0 );

private:
    /*!
     * Create the menu.
     */
    void createMenu();

    void checkLocalFiles();

};

#endif // MAINWINDOW_H
