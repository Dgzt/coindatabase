#ifndef ADDCOINDIALOG_H
#define ADDCOINDIALOG_H

#include <QtWidgets/QDialog>

class QLineEdit;
class QListWidget;

class AddCoinDialog : public QDialog
{
    Q_OBJECT

    QLineEdit *nameLineEdit;

    QListWidget *countryListWidget;

    QLineEdit *yearLineEdit;

    QLineEdit *headImagePath;

    QLineEdit *tailImagePath;

    QList<QPair<int, QString> > m_countryList;

private slots:
    void headImageFileDialogSlot();

    void tailImageFileDialogSlot();

    void addButtonSlot();

public:
    static const int INVALID_COUNTRY_ID = -1;

    static const int INVALID_YEAR = 10000000;

    AddCoinDialog( QList<QPair<int,QString> > countryList );

    QString getName();

    int getCountryId();

    int getYear();

    QString getHeadImagePath();

    QString getTailImagePath();


};

#endif // ADDCOINDIALOG_H
