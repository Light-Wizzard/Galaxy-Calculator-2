#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <stdio.h>
#include <stdlib.h>
/******************************************************************************
* myMessageHandler                                                            *
*******************************************************************************/
void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type)
    {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
    }
}
/******************************************************************************
* main                                                                        *
*******************************************************************************/
int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageHandler);
    // Load Resource File GalaxyCalculator2.qrc
    Q_INIT_RESOURCE(GalaxyCalculator2);
    QApplication a(argc, argv);
    a.setOrganizationName("Light Wizzard");
    a.setApplicationName("Galaxy Calculator 2");
    a.setApplicationDisplayName("Galaxy Calculator 2");
    a.setApplicationVersion("v0.1.0");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "GalaxyCalculator2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
/*** ************************* End of File ***********************************/
