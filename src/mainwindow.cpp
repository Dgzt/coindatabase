#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QDir"
#include "QtWidgets/QVBoxLayout"
#include "QtWidgets/QTableView"
#include <QtWidgets/QHeaderView>
#include <QtSql/QSqlTableModel>
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

    QTableView *coinsView = new QTableView;
    coinsView->setModel( m_localDatabase->getCoinsModel() );
    coinsView->hideColumn(0); //id
    coinsView->hideColumn(1); //id_server
    coinsView->hideColumn(5); //head_image_url
    coinsView->hideColumn(6); //head_image_path
    coinsView->hideColumn(7); //tail_image_url
    coinsView->hideColumn(8); //tail_image_path
    coinsView->hideColumn(9); //deleted
    coinsView->hideColumn(10); //modified_date
    coinsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( coinsView );

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout( layout );

    setCentralWidget( centralWidget );
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

        if( !m_localDatabase->haveCoinsTable() ){
            if( m_localDatabase->createCoinsTable() ){
                qDebug() << "Coins table created.";
            }
        }else{
            qDebug() << "Have coins table.";
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
    m_localDatabase->close();

    close();
}
