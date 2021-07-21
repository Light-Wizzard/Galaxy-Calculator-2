/******************************************************************************
* Help
*******************************************************************************/
#pragma once
#ifndef HELPDIALOG_H
#define HELPDIALOG_H


#include "GalaxySettings.h"
#include "ui_HelpDialog.h"
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtDebug>
#include <QLocale>
#include <QTextBrowser>
#include <QPushButton>
#include <QtGlobal>
#include <QSysInfo>
/*
 DARWIN   - Darwin OS (synonym for Q_OS_MAC)
 SYMBIAN  - Symbian
 MSDOS    - MS-DOS and Windows
 OS2      - OS/2
 OS2EMX   - XFree86 on OS/2 (not PM)
 WIN32    - Win32 (Windows 2000/XP/Vista/7 and Windows Server 2003/2008)
 WINCE    - WinCE (Windows CE 5.0)
 CYGWIN   - Cygwin
 SOLARIS  - Sun Solaris
 HPUX     - HP-UX
 ULTRIX   - DEC Ultrix
 LINUX    - Linux
 FREEBSD  - FreeBSD
 NETBSD   - NetBSD
 OPENBSD  - OpenBSD
 BSDI     - BSD/OS
 IRIX     - SGI Irix
 OSF      - HP Tru64 UNIX
 SCO      - SCO OpenServer 5
 UNIXWARE - UnixWare 7, Open UNIX 8
 AIX      - AIX
 HURD     - GNU Hurd
 DGUX     - DG/UX
 RELIANT  - Reliant UNIX
 DYNIX    - DYNIX/ptx
 QNX      - QNX
 QNX6     - QNX RTP 6.1
 LYNX     - LynxOS
 BSD4     - Any BSD 4.4 system
 UNIX     - Any UNIX BSD/SYSV system
 *
*/
#if defined(Q_WS_X11) || defined(Q_OS_LINUX) || defined(LINUX)
    #include <QWebEngineView>
#elif defined(Q_OS_ANDROID)
    #include <QWebEngineView>
#elif defined(Q_OS_BLACKBERRY)
    #include <QWebEngineView>
#elif defined(Q_OS_IOS)
    #include <QWebEngineView>
#elif defined(Q_OS_MAC) || defined(DARWIN)
    #include <QWebEngineView>
#elif defined(Q_OS_UNIX) || defined(UNIX)
    #include <QWebEngineView>
#elif defined(Q_OS_WINCE) || defined(WINCE)
    #include <QTextEdit>
#elif defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(WIN32)
    #include <QTextEdit>
#else
    #include <QWebEngineView>
#endif

namespace Ui { class HelpDialog; }
/******************************************************************************
* class HelpDialog : public QDialog
*******************************************************************************/
class HelpDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit HelpDialog(QWidget *parent = nullptr);
        ~HelpDialog();

        void readHelp();
        void back();

    private slots:
        void on_buttonBoxHelpOk_clicked();

    private:
        Ui::HelpDialog *ui;                 //!< \c ui \brief Pointer to HelpDialog.ui
        GalaxySettings *myGalaxySettings;   //!< \c myGalaxySettings \brief Galaxy Settings
        QPushButton *MyCloseButton;         //!< \c MyCloseButton \brief MyCloseButton
        QPushButton *MyBackButton;          //!< \c MyBackButton \brief MyBackButton
        #if defined(Q_WS_X11) || defined(Q_OS_LINUX) || defined(LINUX)
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_OS_ANDROID)
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_OS_BLACKBERRY)
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_OS_IOS)
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_OS_MAC) || defined(DARWIN)
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_OS_UNIX) || defined(UNIX)
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_OS_WINCE) || defined(WINCE)
            QTextEdit *myWebView;          //!< \c myGalaxySettings \brief Web View
        #elif defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(WIN32)
            QTextEdit *myWebView;          //!< \c myGalaxySettings \brief Web View
        #else
            QWebEngineView *myWebView;          //!< \c myGalaxySettings \brief Web View
        #endif
}; // end class HelpDialog
#endif // HELPDIALOG_H
/******************************* End of File *********************************/
