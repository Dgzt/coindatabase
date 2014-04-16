#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QDir"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "countriesdialog.h"
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
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *countriesAction = new QAction(tr("Countries"), this);
    connect( countriesAction, SIGNAL( triggered() ), this, SLOT( countriesDialogSlot() ) );

    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL( triggered() ), this, SLOT( exitSlot() ) );

    fileMenu->addAction( countriesAction );
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
                                                    QString("deleted          BOOLEAN NOT NULL CHECK (deleted IN (0,1)),")+
                                                    QString("modified_date      DATETIME NOT NULL")+
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

void MainWindow::countriesDialogSlot()
{
    CountriesDialog countriesDialog;
    countriesDialog.exec();
}

void MainWindow::exitSlot()
{
    localDb.close();

    close();
}
