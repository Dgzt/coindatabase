#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QDir"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
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

        if( !localDb.tables().contains("countries") ){

            QSqlQuery createCountriesQuery(localDb);
            bool ok = createCountriesQuery.exec( QString("CREATE TABLE countries (")+
                                                    QString("id               INTEGER PRIMARY KEY,")+
                                                    QString("id_server        BIGINT,")+
                                                    QString("name             VARCHAR(64) NOT NULL,")+
                                                    QString("modify_date      DATETIME NOT NULL")+
                                                 QString(")"));

            if(ok){
                qDebug() << "Ok create countries table";
            }else{
                qDebug() << "Not ok create countries table";
                qDebug() << createCountriesQuery.lastError().text();
            }

        }

    }else{
        qDebug() << "not open.";
    }
}

void MainWindow::exitSlot()
{
    localDb.close();

    close();
}
