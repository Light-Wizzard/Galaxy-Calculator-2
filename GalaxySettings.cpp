#include "GalaxySettings.h"

/**************************************************************************
* \class GalaxySettings
* Creates QSettings for organizationName, organizationDomain, applicationName
***************************************************************************/
GalaxySettings::GalaxySettings(QObject *parent) : QObject(parent)
{

}
/**************************************************************************
* \fn class ~GalaxySettings
* Creates QSettings for organizationName, organizationDomain, applicationName
***************************************************************************/
GalaxySettings::~GalaxySettings()
{

}
/**************************************************************************
* \fn void GalaxySettings::getSettings()
* Creates QSettings for organizationName, organizationDomain, applicationName
***************************************************************************/
QSettings *GalaxySettings::getSettings()
{
    if (isDebugMessage) qDebug() << "getSettings";
    // organizationName, organizationDomain, applicationName and applicationName
    // are set in main.cpp, and passed into Constuctor, so they are set
    QCoreApplication::setOrganizationName(getOrgName());
    QCoreApplication::setOrganizationDomain(getOrgDomain());
    QCoreApplication::setApplicationName(getAppName());
    //QCoreApplication::setApplicationDisplayName(getAppName());
    // see *.pro file where it is: DEFINES *= APP_VERSION=$${VERSION}
    QCoreApplication::setApplicationVersion(QObject::tr(APP_VERSION));
    QString myIni = getDataPath("GalaxyCalculator.ini");
    QDir settingsPath;
    if (!isFileMake(settingsPath.currentPath(), "GalaxyCalculator.ini"))
    {
        qDebug() << "Failed to make File in GetSettings GalaxyCalculator.ini";
    }
    return new QSettings(myIni, QSettings::IniFormat);
} // end qSettingsInstance
/**************************************************************************
* \fn bool GalaxySettings::isSetting(const QString &thisFieldName)
***************************************************************************/
bool GalaxySettings::isSetting(const QString &thisFieldName)
{
    if (isDebugMessage) qDebug() << "isSetting";
    QSettings *mySettings = getSettings();
    return mySettings->contains(thisFieldName);
} // end isSetting
/******************************************************************************
* \fn readSettings
*******************************************************************************/
QString GalaxySettings::readSettings(const QString thisSetting, const QString thisDefault)
{
    if (isDebugMessage) qDebug() << "readSettings";
    QSettings *mySettings = getSettings();
    mySettings->beginGroup("General");
    QString theSetting = mySettings->value(thisSetting, thisDefault).toString();
    mySettings->endGroup();
    return theSetting;
}
/******************************************************************************
* \fn readSettingsBool
*******************************************************************************/
bool GalaxySettings::readSettingsBool(const QString thisSetting, bool thisDefault)
{
    if (isDebugMessage) qDebug() << "readSettingsBool";
    QSettings *mySettings = getSettings();
    mySettings->beginGroup("General");
    bool theSetting = mySettings->value(thisSetting, thisDefault).toBool();
    mySettings->endGroup();
    return theSetting;
}
/******************************************************************************
* \fn readSettingsInt
*******************************************************************************/
int GalaxySettings::readSettingsInt(const QString thisSetting, int thisDefault)
{
    if (isDebugMessage) qDebug() << "readSettingsInt";
    QSettings *mySettings = getSettings();
    mySettings->beginGroup("General");
    int theSetting = mySettings->value(thisSetting, thisDefault).toInt();
    mySettings->endGroup();
    return theSetting;
}
/******************************************************************************
* \fn writeSettings
*******************************************************************************/
void GalaxySettings::writeSettings(const QString thisSetting, const QString thisValue)
{
    if (isDebugMessage) qDebug() << "writeSettings";
    QSettings *mySettings = getSettings();
    mySettings->beginGroup("General");
    mySettings->setValue(thisSetting, thisValue);
    mySettings->endGroup();
}
/******************************************************************************
* \fn getDataPath
*******************************************************************************/
QString GalaxySettings::getDataPath(const QString thisFileName)
{
    if (isDebugMessage) qDebug() << "getDataPath";
    //
    QDir settingsPath;
    // FIXME Path
    QString myDataPath = QString(settingsPath.currentPath()).append(QDir::separator()).append(thisFileName);
    if (isDebugMessage) qDebug() << "getDataPath = " << myDataPath;
    return myDataPath;
}
/**************************************************************************
* \fn QString GalaxySettings::combinePathFileName(QString thisPath, QString thisFileName)
***************************************************************************/
QString GalaxySettings::combinePathFileName(const QString thisPath, QString thisFileName)
{
    if (isDebugMessage) qDebug() << "combinePathFileName";
    return QString("%1%2%3").arg(thisPath, QDir::separator(), thisFileName);
} // end combinePathFileName
/**************************************************************************
* \fn bool GalaxySettings::isFileExists(QString thisFile)
***************************************************************************/
bool GalaxySettings::isFileExists(QString thisFile)
{
    if (isDebugMessage) qDebug() << "isFileExists";
    // check if file exists and if yes: Is it really a file and not directory?
    return QFileInfo::exists(thisFile) && QFileInfo(thisFile).isFile();
} // end isFileExists
/**************************************************************************
* \fn bool GalaxySettings::isFileMake(const QString &thisPath, const QString &thisFileName)
***************************************************************************/
bool GalaxySettings::isFileMake(const QString &thisPath, const QString &thisFileName)
{
    if (isDebugMessage) qDebug() << "isFileMake";
    if (!isMakeDir(thisPath)) return false;
    if (!isFileExists(combinePathFileName(thisPath, thisFileName)))
    {
        QFile file(combinePathFileName(thisPath, thisFileName));
        if (file.open(QIODevice::WriteOnly))
        {
            file.close();
            return true;
        }
        else return false;
    }
    return true;
} // end isFileMake
/**************************************************************************
* \fn bool GalaxySettings::isMakeDir(const QString &thisPath)
***************************************************************************/
bool GalaxySettings::isMakeDir(const QString &thisPath)
{
    if (isDebugMessage) qDebug() << "isMakeDir";
    QDir dir(thisPath);
    if (!dir.exists())
    {
        if (!dir.mkpath("."))
        {
            qFatal("%s", QString("Error: cannot create file %1").arg(thisPath).toLocal8Bit().constData());
        }
        else return true;
    }
    return isPathExists(thisPath);
} // end isMakeDir
/**************************************************************************
* \fn bool GalaxySettings::isPathExists(QString thisPath)
***************************************************************************/
bool GalaxySettings::isPathExists(QString thisPath)
{
    return QDir(thisPath).exists();
} // end isPathExists
/**************************************************************************
* \fn QString GalaxySettings::getOrgName()
* This value is used for Qt Settings: GitHub Account Name is one example
***************************************************************************/
QString GalaxySettings::getOrgName()
{
    if (isDebugMessage) qDebug() << "getOrgName";
    return myOrganizationName;
} // end getOrgName
/**************************************************************************
* \fn void GalaxySettings::setOrgName(const QString &thisOrgName)
***************************************************************************/
void GalaxySettings::setOrgName(const QString &thisOrgName)
{
    if (isDebugMessage) qDebug() << "setOrgName";
    if (myOrganizationName != thisOrgName)
    {
        myOrganizationName = thisOrgName;
    }
} // end setOrgName
/**************************************************************************
* \fn QString GalaxySettings::getOrgDomain()
***************************************************************************/
QString GalaxySettings::getOrgDomain()
{
    if (isDebugMessage) qDebug() << "getOrgDomain";
    return myOrganizationDomain;
} // end getOrgDomain
/**************************************************************************
* \fn void GalaxySettings::setOrgDomain(const QString &thisOrgDomain)
***************************************************************************/
void GalaxySettings::setOrgDomain(const QString &thisOrgDomain)
{
    if (isDebugMessage) qDebug() << "setOrgDomain";
    if (myOrganizationDomain != thisOrgDomain)
    {
        myOrganizationDomain = thisOrgDomain;
    }
} // end setOrgDomain
/**************************************************************************
* \fn QString GalaxySettings::getAppName()
***************************************************************************/
QString GalaxySettings::getAppName()
{
    if (isDebugMessage) qDebug() << "getAppName";
    return myApplicationName;
} // end getAppName
/**************************************************************************
* \fn void GalaxySettings::setAppName(const QString &thisAppName)
***************************************************************************/
void GalaxySettings::setAppName(const QString &thisAppName)
{
    if (isDebugMessage) qDebug() << "setAppName";
    if (myApplicationName != thisAppName)
    {
        myApplicationName = thisAppName;
    }
} // end setAppName
/**************************************************************************
* \fn void GalaxySettings::setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin)
***************************************************************************/
void GalaxySettings::setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin)
{
    if (isDebugMessage) qDebug() << "isSetting";
    QSettings *mySettings = getSettings();
    mySettings->beginGroup("General");
    mySettings->setValue(ConstSettingsGeometryPos, thisPos);
    mySettings->setValue(ConstSettingsGeometryMax, isMax);
    mySettings->setValue(ConstSettingsGeometryMin, isMin);
    if(!isMax && !isMin) mySettings->setValue(ConstSettingsGeometrySize, thisSize);
    mySettings->endGroup();
} // end setGeometry
/**************************************************************************
* \fn QPoint GalaxySettings::getGeometry(const QPoint &thisDefaultValue)
***************************************************************************/
void GalaxySettings::getGeometry()
{
    if (isDebugMessage) qDebug() << "readSettingsBool";
    // Geometry
    QSettings *mySettings = getSettings();
    mySettings->beginGroup("General");
    myGeometryPos = mySettings->value(ConstSettingsGeometryPos, ConstDefaultGeometryPos).toPoint();
    myGeometrySize = mySettings->value(ConstSettingsGeometrySize, ConstDefaultGeometrySize).toSize();
    myGeometryMax = mySettings->value(ConstSettingsGeometryMax, true).toBool();
    myGeometryMin = mySettings->value(ConstSettingsGeometryMin, false).toBool();
    mySettings->endGroup();
} // end getGeometry
/**************************************************************************
* \fn QPoint GalaxySettings::getGeometryPos(const QPoint &thisDefaultValue)
***************************************************************************/
QPoint GalaxySettings::getGeometryPos()
{
    return myGeometryPos;
} // end getGeometryPos
/**************************************************************************
* \fn QSize GalaxySettings::getGeometrySize(const QSize &thisDefaultValue)
***************************************************************************/
QSize GalaxySettings::getGeometrySize()
{
    return myGeometrySize;
} // end getGeometrySize
/**************************************************************************
* \fn bool GalaxySettings::getGeometryMax(const bool &thisDefaultValue)
***************************************************************************/
bool GalaxySettings::getGeometryMax()
{
    return myGeometryMax;
} // end getGeometryMax
/**************************************************************************
* \fn bool GalaxySettings::getGeometryMin(const bool &thisDefaultValue)
***************************************************************************/
bool GalaxySettings::getGeometryMin()
{
    return myGeometryMin;
} // end getGeometryMin
/**************************************************************************
* \fn QString GalaxySettings::getGeometryMin(const bool &thisDefaultValue)
***************************************************************************/
QString GalaxySettings::readFile(const QString &thisFileName)
{
    QFile file(thisFileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return "";
    }
    QTextStream in(&file);
    QString thisText = in.readAll();
    file.close();
    return thisText;
}
/*** ************************* End of File ***********************************/
