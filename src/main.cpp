#include "MainWindow.h"
/************************************************
* @brief get App Data Location, Linux: $HOME/.local/share/AppName, Windows:.
* getAppDataLocation
 ***********************************************/
QString getAppDataLocation()
{
    QString theAppDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (theAppDataLocation.isEmpty())
    {
        theAppDataLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
        if (theAppDataLocation.isEmpty())
        { theAppDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation); }
        if (theAppDataLocation.isEmpty())
        { theAppDataLocation = QDir::currentPath(); }
    }

    return theAppDataLocation;
}
/************************************************
* @brief get Message Log File.
* getMessageLogFile
 ***********************************************/
QString getMessageLogFile()
{
    return QString("%1%2%3").arg(getAppDataLocation(), QDir::separator(), "messageLog.txt");
}
/************************************************
* @brief get File Error Message.
* getFileErrorMessage
 ***********************************************/
QString getFileErrorMessage()
{
    return QString("%1: %2").arg(QObject::tr("Failed to open log file"), getMessageLogFile());
}
/************************************************
* @brief set Message Log File.
* setMessageLogFile
 ***********************************************/
bool setMessageLogFile(const QString &thisAppName)
{
    QString theLogFile = getMessageLogFile();
    if (QFileInfo::exists(theLogFile) && QFileInfo(theLogFile).isFile())
        { QFile::remove(theLogFile); }
    QFile theFile(theLogFile);
    if(!theFile.open(QFile::WriteOnly | QFile::Text | QIODevice::Truncate))
    {
        QString theErrorMessage = getFileErrorMessage();
        std::cout << theErrorMessage.toStdString() << std::endl;
        return false;
    }
    // Write to log file
    QTextStream theFileStream(&theFile);
    const QDateTime theDateTimeStamp = QDateTime::currentDateTime();
    QString theDateStamp = QString("%1: %2 - %3 %4").arg(QObject::tr("Log File"), thisAppName, theDateTimeStamp.toString("dd MMM yyyy hh:mm:ss"), theDateTimeStamp.timeZoneAbbreviation());
    theFileStream << theDateStamp  << '\n';
    theFile.flush();
    theFile.close();
    if (QFileInfo::exists(theLogFile) && QFileInfo(theLogFile).isFile())
        { return true; }
    else
        { return false; }
}
/************************************************
* @brief log Events.
* logEvents
 ***********************************************/
void logEvents(const QString &thisMessage)
{
    QFile theFileHandle(getMessageLogFile());
    if(!theFileHandle.open( QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text ))
    {
        // Do not use qDebug() since that is a loop
        QString theErrorMessage = getFileErrorMessage();
        std::cout << theErrorMessage.toStdString() << std::endl;
        return;
    }
    QTextStream theFileStream(&theFileHandle);
    theFileStream << thisMessage;
    theFileStream.flush();
    theFileHandle.close();
}
/************************************************
 * @brief I use a special Message Handler to format the output of Error.
 * myMessageHandler
 ***********************************************/
void myMessageHandler(QtMsgType thisType, const QMessageLogContext &thisContext, const QString &thisMsg)
{
    QByteArray localMsg = thisMsg.toLocal8Bit();
    const char *file = thisContext.file ? thisContext.file : "";
    const char *function = thisContext.function ? thisContext.function : "";
    switch (thisType)
    {
        case QtDebugMsg:
            logEvents(QString("Debug: %1 (%2:%3, %4)\n").arg(thisMsg, thisContext.file ? thisContext.file : "", QString::number(thisContext.line), thisContext.function ? thisContext.function : ""));
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, thisContext.line, function);
            break;
        case QtInfoMsg:
            logEvents(QString("Info: %1 (%2:%3, %4)\n").arg(thisMsg, thisContext.file ? thisContext.file : "", QString::number(thisContext.line), thisContext.function ? thisContext.function : ""));
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, thisContext.line, function);
            break;
        case QtWarningMsg:
            logEvents(QString("Warning: %1 (%2:%3, %4)\n").arg(thisMsg, thisContext.file ? thisContext.file : "", QString::number(thisContext.line), thisContext.function ? thisContext.function : ""));
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, thisContext.line, function);
            break;
        case QtCriticalMsg:
            logEvents(QString("Critical: %1 (%2:%3, %4)\n").arg(thisMsg, thisContext.file ? thisContext.file : "", QString::number(thisContext.line), thisContext.function ? thisContext.function : ""));
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, thisContext.line, function);
            break;
        case QtFatalMsg:
            logEvents(QString("Fatal: %1 (%2:%3, %4)\n").arg(thisMsg, thisContext.file ? thisContext.file : "", QString::number(thisContext.line), thisContext.function ? thisContext.function : ""));
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, thisContext.line, function);
            break;
    }
}
/************************************************
 * @brief main.
 * main
 ***********************************************/
int main(int argc, char *argv[])
{
    // Load Resource File GalaxyCalculator2.qrc before creating Application
    Q_INIT_RESOURCE(GalaxyCalculator2);
    QApplication theApplication(argc, argv);
    theApplication.setOrganizationName("Light-Wizzard");
    theApplication.setApplicationName("GalaxyCalculator2");
    theApplication.setApplicationDisplayName("Galaxy Calculator 2");
    theApplication.setApplicationVersion(VERSION);
    // Run after the Application is created and given a name and before creating MainWindow
    qInstallMessageHandler(myMessageHandler);
    setMessageLogFile(theApplication.applicationName()); // FIXME what if error
    //
    MainWindow theMainWindow;
    theMainWindow.show();
    return theApplication.exec();
}
/******************************* End of File *********************************/
