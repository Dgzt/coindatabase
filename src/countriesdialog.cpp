#include <QDebug>
#include <QTableWidget>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QPushButton>
#include <QSqlQuery>
#include "localdatabase.h"
#include "addcountrydialog.h"
#include "countriesdialog.h"

CountriesDialog::CountriesDialog( LocalDatabase *localDatabase, QWidget *parent ) :
    QDialog( parent )
{
    m_localDatabase = localDatabase;

    tableModel = m_localDatabase->getCountriesModel();

    QTableView *countriesView = new QTableView;
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
