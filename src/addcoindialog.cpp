#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "addcoindialog.h"


const QString FILE_FILTER = QObject::tr( "Image Files (*.png *.jpg)" );

const QString FILE_DIALOG_TITLE = QObject::tr( "Select Image" );

const QString WARNING_TITLE = QObject::tr( "Warning" );

AddCoinDialog::AddCoinDialog( QList<QPair<int,QString> > countryList )
    : m_countryList( countryList )
{
    setWindowTitle( tr( "Add Coin Dialog" ) );

    nameLineEdit = new QLineEdit;

    countryListWidget = new QListWidget;
    countryListWidget->setSelectionMode( QAbstractItemView::SingleSelection );

    for( int i = 0; i < m_countryList.size(); ++i ){
        countryListWidget->addItem( m_countryList.at(i).second );
    }

    yearLineEdit = new QLineEdit;

    headImagePath = new QLineEdit;
    headImagePath->setReadOnly( true );

    QPushButton *headImagePathButton = new QPushButton( "Open" );
    connect( headImagePathButton, SIGNAL( clicked() ), this, SLOT( headImageFileDialogSlot() ) );

    QHBoxLayout *headButtonLayout = new QHBoxLayout;
    headButtonLayout->addStretch();
    headButtonLayout->addWidget( headImagePathButton );

    QVBoxLayout *headLayout = new QVBoxLayout;
    headLayout->addWidget( headImagePath );
    headLayout->addLayout( headButtonLayout );

    tailImagePath = new QLineEdit;
    tailImagePath->setReadOnly( true );

    QPushButton *tailImagePathButton = new QPushButton( "Open" );
    connect( tailImagePathButton, SIGNAL( clicked() ), this, SLOT( tailImageFileDialogSlot() ) );

    QHBoxLayout *tailButtonLayout = new QHBoxLayout;
    tailButtonLayout->addStretch();
    tailButtonLayout->addWidget( tailImagePathButton );

    QVBoxLayout *tailLayout = new QVBoxLayout;
    tailLayout->addWidget( tailImagePath );
    tailLayout->addLayout( tailButtonLayout );

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow( tr( "Name:" ), nameLineEdit );
    formLayout->addRow( tr( "Country:" ), countryListWidget );
    formLayout->addRow( tr( "Year:" ), yearLineEdit );
    formLayout->addRow( tr( "Head Image:" ), headLayout );
    formLayout->addRow( tr( "Tail Image:" ), tailLayout );

    QPushButton *addButton = new QPushButton( tr( "Add" ) );
    connect( addButton, SIGNAL( clicked() ), this, SLOT( addButtonSlot() ) );

    QDialogButtonBox *dialogBox = new QDialogButtonBox;
    dialogBox->addButton( addButton, QDialogButtonBox::ActionRole );
    dialogBox->addButton( QDialogButtonBox::Cancel );
    connect( dialogBox, SIGNAL( rejected() ), this, SLOT( close() ) );

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout( formLayout );
    mainLayout->addWidget( dialogBox );

    setLayout( mainLayout );
}

void AddCoinDialog::headImageFileDialogSlot()
{
    QString filePath = QFileDialog::getOpenFileName( this, FILE_DIALOG_TITLE, QDir::homePath(), FILE_FILTER );
    headImagePath->setText( filePath );
}

void AddCoinDialog::tailImageFileDialogSlot()
{
    QString filePath = QFileDialog::getOpenFileName( this, FILE_DIALOG_TITLE, QDir::homePath(), FILE_FILTER );
    tailImagePath->setText( filePath );
}

void AddCoinDialog::addButtonSlot()
{
    bool yearNum = true;
    int year = yearLineEdit->text().toInt(&yearNum);
    Q_UNUSED( year )
    if( !yearLineEdit->text().isEmpty() && !yearNum ){
        QMessageBox::warning( this, WARNING_TITLE, tr( "Year is not number!" ) );
        return;
    }

    if( headImagePath->text().isEmpty() ){
        QMessageBox::warning( this, WARNING_TITLE, tr( "Need head image!" ) );
        return;
    }

    if( tailImagePath->text().isEmpty() ){
        QMessageBox::warning( this, WARNING_TITLE, tr( "Need tail image!" ) );
        return;
    }

    accept();
}

QString AddCoinDialog::getName()
{
    return nameLineEdit->text();
}

int AddCoinDialog::getCountryId()
{
    if( !countryListWidget->selectedItems().isEmpty() ){
        return m_countryList.at( countryListWidget->row( countryListWidget->selectedItems().at(0) ) ).first;
    }

    return INVALID_COUNTRY_ID;
}

int AddCoinDialog::getYear()
{
    if( !yearLineEdit->text().isEmpty() ){
        return yearLineEdit->text().toInt();
    }

    return INVALID_YEAR;
}

QString AddCoinDialog::getHeadImagePath()
{
    return headImagePath->text();
}

QString AddCoinDialog::getTailImagePath()
{
    return tailImagePath->text();
}
