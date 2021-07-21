/******************************************************************************
* Help Dialog
*******************************************************************************/
#include "HelpDialog.h"
/******************************************************************************
* HelpDialog Constructor
*******************************************************************************/
/*!
   \class HelpDialog
   \fn HelpDialog::HelpDialog(QWidget *parent) : QDialog(parent), ui(new Ui::HelpDialog)
   \brief Show Help Dialog Box.
 */
HelpDialog::HelpDialog(QWidget *parent) : QDialog(parent), ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    // Galaxy Settings
    myGalaxySettings = new GalaxySettings(this);
    #if defined(Q_WS_X11) || defined(Q_OS_LINUX) || defined(LINUX)
        myWebView = new QWebEngineView(this);
    #elif defined(Q_OS_ANDROID)
        myWebView = new QWebEngineView(this);
    #elif defined(Q_OS_BLACKBERRY)
        myWebView = new QWebEngineView(this);
    #elif defined(Q_OS_IOS)
        myWebView = new QWebEngineView(this);
    #elif defined(Q_OS_MAC) || defined(DARWIN)
        myWebView = new QWebEngineView(this);
    #elif defined(Q_OS_UNIX) || defined(UNIX)
        myWebView = new QWebEngineView(this);
    #elif defined(Q_OS_WINCE) || defined(WINCE)
        myWebView = new QTextEdit(this);
    #elif defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(WIN32)
        myWebView = new QTextEdit(this);
    #else
        myWebView = new QWebEngineView(this);
    #endif
    //
    MyCloseButton = new QPushButton(this);
    MyCloseButton->setText(tr("Close"));
    connect(MyCloseButton, &QPushButton::clicked,  this, &QDialog::close);
    //
    MyBackButton = new QPushButton(this);
    MyBackButton->setText(tr("Back"));
    connect(MyBackButton, &QPushButton::clicked,  this, &HelpDialog::back);
    //
    ui->verticalLayoutHelp->addWidget(MyBackButton);
    //
    #if defined(Q_WS_X11) || defined(Q_OS_LINUX) || defined(LINUX)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_OS_ANDROID)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_OS_BLACKBERRY)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_OS_IOS)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_OS_MAC) || defined(DARWIN)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_OS_UNIX) || defined(UNIX)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_OS_WINCE) || defined(WINCE)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #elif defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(WIN32)
        ui->verticalLayoutHelp->addWidget(myWebView);
    #else
        ui->verticalLayoutHelp->addWidget(myWebView);
    #endif


    ui->verticalLayoutHelp->addWidget(MyCloseButton);
    readHelp();
} // end HelpDialog
/******************************************************************************
* HelpDialog Destructor
*******************************************************************************/
HelpDialog::~HelpDialog()
{
    delete ui;
} // end ~AboutDialog
/******************************************************************************
* on_buttonBoxHelpOk_clicked
*******************************************************************************/
void HelpDialog::on_buttonBoxHelpOk_clicked()
{
    close();
}
/******************************************************************************
* \fn readHelp
*******************************************************************************/
void HelpDialog::readHelp()
{
    QString thisFileName;
    if (QGuiApplication::inputMethod()->locale().name().mid(0, 3) == "en_")
    { thisFileName = "Help-en.html"; }
    else
    { thisFileName = "Help-en.html"; }
    #if defined(Q_WS_X11) || defined(Q_OS_LINUX) || defined(LINUX)
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_OS_ANDROID)
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_OS_BLACKBERRY)
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_OS_IOS)
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_OS_MAC) || defined(DARWIN)
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_OS_UNIX) || defined(UNIX)
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_OS_WINCE) || defined(WINCE)
        myWebView->setHtml(myGalaxySettings->readFile(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #elif defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(WIN32)
        myWebView->setHtml(myGalaxySettings->readFile(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #else
        //myWebView->setHtml(myGalaxySettings->getDataPath(thisFileName));
        myWebView->load(QUrl(QString("qrc:/help/%1").arg(thisFileName)));
        myWebView->show();
    #endif
}
/******************************************************************************
* \fn back
*******************************************************************************/
void HelpDialog::back()
{
    #if defined(Q_WS_X11) || defined(Q_OS_LINUX) || defined(LINUX)
        myWebView->back();
    #elif defined(Q_OS_ANDROID)
        myWebView->back();
    #elif defined(Q_OS_BLACKBERRY)
        myWebView->back();
    #elif defined(Q_OS_IOS)
        myWebView->back();
    #elif defined(Q_OS_MAC) || defined(DARWIN)
        myWebView->back();
    #elif defined(Q_OS_WINCE) || defined(WINCE)
        // myWebView->back();
    #elif defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(WIN32)
        //myWebView->back();
    #elif defined(Q_OS_UNIX) || defined(UNIX)
        myWebView->back();
    #else
        myWebView->back();
    #endif

}
/******************************* End of File *********************************/
