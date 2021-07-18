/******************************************************************************
* WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
* About Dialog                                                               *
*******************************************************************************/
#include "AboutDialog.h"
/******************************************************************************
* AboutDialog Constructor                                                    *
*******************************************************************************/
/*!
   \class AboutDialog
   \fn AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
   \brief Show About Dialog Box.
 */
AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBoxOk, &QPushButton::clicked,  this, &QDialog::close);
} // end AboutDialog
/******************************************************************************
* AboutDialog Destructor                                                     *
*******************************************************************************/
AboutDialog::~AboutDialog()
{
    delete ui;
} // end ~AboutDialog
/******************************* End of File *********************************/

