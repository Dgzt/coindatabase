#ifndef ADDCOUNTRYDIALOG_H
#define ADDCOUNTRYDIALOG_H

#include <QDialog>

class QLineEdit;

class AddCountryDialog : public QDialog
{
    Q_OBJECT

    /*!
     * The name of the country.
     */
    QLineEdit *m_nameText;

    /*!
     * The max length of name of country.
     */
    int m_maxNameLength;

public:
    /*!
     * Setup the dialog with widget components.
     *
     * @param maxNameLength The max length of name of country.
     * @param parent The parent widget.
     */
    AddCountryDialog( int maxNameLength,  QWidget *parent = 0 );

    /*!
     * Get the given name of country.
     *
     * @return The name of country.
     */
    QString getName();

private slots:
    /*!
     * The slot when call when click to the Ok button.
     */
    void okSlot();
};

#endif // ADDCOUNTRYDIALOG_H
