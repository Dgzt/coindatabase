#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QDir"
#include "QtWidgets/QVBoxLayout"
#include "QtWidgets/QTableWidget"
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include <QtSql/QSqlTableModel>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "addcoindialog.h"
#include "countriesdialog.h"
#include "localdatabase.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow( parent )
{
    qDebug()<< "Init.";

    createMenu();

    checkLocalFiles();

    coinsTable = new QTableWidget;
    coinsTable->setEditTriggers( QTableWidget::NoEditTriggers );
    coinsTable->setSelectionMode( QTableWidget::SingleSelection );
    coinsTable->setSelectionBehavior( QTableWidget::SelectRows );
    coinsTable->setColumnCount( 4 );
    coinsTable->setHorizontalHeaderLabels( QStringList() << "ID" << "Name" << "Country" << "Year" );
    coinsTable->hideColumn( 0 );
    m_localDatabase->loadCoinsTable( coinsTable );
    coinsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *addButton = new QPushButton( tr( "Add" ) );
    connect( addButton, SIGNAL( clicked() ), this, SLOT( addCoinSlot() ) );

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton( addButton, QDialogButtonBox::ActionRole );

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( coinsTable );
    layout->addWidget( buttonBox );

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout( layout );

    setCentralWidget( centralWidget );
}

MainWindow::~MainWindow()
{
    m_localDatabase->close();
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

void MainWindow::addCoinSlot()
{
    AddCoinDialog dialog( m_localDatabase->getCountryList() );

    if( dialog.exec() ){
        //Name
        QString name = LocalDatabase::EMPTY_NAME;
        if( !dialog.getName().isEmpty() ){
            name = dialog.getName();
        }

        //Country id
        int countryId = LocalDatabase::EMPTY_COUNTRY_ID;
        if( dialog.getCountryId() != AddCoinDialog::INVALID_COUNTRY_ID ){
            countryId = dialog.getCountryId();
        }

        int year = LocalDatabase::EMPTY_YEAR;
        if( dialog.getYear() != AddCoinDialog::INVALID_YEAR ){
            year = dialog.getYear();
        }

        qDebug() << m_localDatabase->insertCoin( dialog.getHeadImagePath(), dialog.getTailImagePath(), name, countryId, year );

        coinsTable->setRowCount( 0 );
        m_localDatabase->loadCoinsTable( coinsTable );
    }
}
