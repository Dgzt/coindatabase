#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QDir"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "countriesdialog.h"
#include "localdatabase.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow( parent )
{
    qDebug()<< "Init.";

    createMenu();

    checkLocalFiles();
}

MainWindow::~MainWindow()
{
    delete m_localDatabase;
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

    m_localDatabase = new LocalDatabase(homeDir.absolutePath() + "/.coins/local.db");

    if( m_localDatabase->open() ){
        if( !m_localDatabase->haveCountriesTable() ){
            if( m_localDatabase->createCountriesTable() ){
                qDebug() << "Countries table created.";
            }
        }else{
            qDebug() << "Have countries table.";
        }
    }else{
        qDebug() << "Database doesn't open.";
    }

}

void MainWindow::countriesDialogSlot()
{
    CountriesDialog countriesDialog(m_localDatabase);
    countriesDialog.exec();
}

void MainWindow::exitSlot()
{
    //localDb.close();
    m_localDatabase->close();

    close();
}
