#include <QDebug>
#include <QTableWidget>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QMenu>
#include "localdatabase.h"
#include "addcountrydialog.h"
#include "countriesdialog.h"

CountriesDialog::CountriesDialog( LocalDatabase *localDatabase, QWidget *parent ) :
    QDialog( parent )
{
    m_localDatabase = localDatabase;

    tableModel = m_localDatabase->getCountriesModel();

    countriesView = new QTableView;
    countriesView->setContextMenuPolicy( Qt::CustomContextMenu );
    countriesView->setModel(tableModel);
    countriesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    countriesView->hideColumn(0); //Id
    countriesView->hideColumn(1); //server_id
    countriesView->hideColumn(3); //deleted
    countriesView->hideColumn(4); //modified_date

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(countriesView);

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    QPushButton *addButton = buttonBox->addButton(tr("Add"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(QDialogButtonBox::Close);
    connect( buttonBox, SIGNAL(rejected()), this, SLOT(close()) );
    connect( addButton, SIGNAL(clicked()), this, SLOT(addSlot()));
    layout->addWidget(buttonBox);

    setLayout(layout);

    connect( countriesView, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( customMenuRequested( QPoint ) ) );
}

void CountriesDialog::customMenuRequested( QPoint pos )
{
    QAction *removeAction = new QAction( tr( "Remove" ), this );
    connect( removeAction, SIGNAL( triggered() ), this, SLOT( removeSlot() ) );

    QMenu *menu = new QMenu( this );
    menu->addAction( removeAction );

    menu->popup( countriesView->viewport()->mapToGlobal( pos ) );
}

void CountriesDialog::addSlot()
{
    qDebug() << "add";

    AddCountryDialog addCountryDialog( m_localDatabase->getMaxCountryNameLength() );

    if( addCountryDialog.exec() ){
        qDebug() << "Add:" << addCountryDialog.getName();
        if( m_localDatabase->insertCountry( addCountryDialog.getName() ) ){
            tableModel->select();
        }
    }
}

void CountriesDialog::removeSlot()
{
    foreach( QModelIndex index, countriesView->selectionModel()->selectedIndexes() ){
        m_localDatabase->removeCountry( tableModel->record( index.row() ).field("id").value().toInt() );
    }

    tableModel->select();
}
