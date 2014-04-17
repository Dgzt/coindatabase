#include <QDebug>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "addcountrydialog.h"

AddCountryDialog::AddCountryDialog( int maxNameLength, QWidget *parent ) :
    QDialog( parent ),
    m_maxNameLength( maxNameLength )
{
    m_nameText = new QLineEdit;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_nameText);
    layout->addWidget(buttonBox);
    setLayout(layout);

    connect( buttonBox, SIGNAL(accepted()), this, SLOT(okSlot()) );

}

void AddCountryDialog::okSlot()
{
    if( m_nameText->text().length() > m_maxNameLength ){
        qDebug() << "Too big!";
        return;
    }

    accept();
}

QString AddCountryDialog::getName()
{
    return m_nameText->text();
}
