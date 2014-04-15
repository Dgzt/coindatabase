#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QDir"
#include "QtSql/QSqlDatabase"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow( parent )
{
    qDebug()<< "Init.";

    createMenu();

    checkLocalFiles();
}

void MainWindow::createMenu()
{
    QAction *quitAction = new QAction(tr("Quit"), this);

    connect(quitAction, SIGNAL( triggered() ), this, SLOT( exitSlot() ) );

    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction( quitAction );
}

void MainWindow::checkLocalFiles()
{
    QDir homeDir = QDir::home();
    qDebug() << homeDir.absolutePath();

    if( !homeDir.exists(".coins") ){
        if( homeDir.mkdir(".coins") ){

        }else{
            qDebug() << "Cannot create $home/.coins directory!";
        }

    }else{
        qDebug() << "yes";
    }


    localDb = QSqlDatabase::addDatabase("QSQLITE");
    localDb.setDatabaseName(homeDir.absolutePath() + "/.coins/local.db");

    if( localDb.open() ){
        qDebug() << "Open.";
    }else{
        qDebug() << "not open.";
    }
}

void MainWindow::exitSlot()
{
    localDb.close();

    close();
}
