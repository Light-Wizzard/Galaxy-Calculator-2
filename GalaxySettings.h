#ifndef GALAXYSETTINGS_H
#define GALAXYSETTINGS_H

#include <QCoreApplication>
#include <QtCore>
#include <QObject>
#include <QtDebug>
/******************************************************************************
* \fn GalaxySettings
*******************************************************************************/
class GalaxySettings : public QObject
{
        Q_OBJECT
    public:
         explicit GalaxySettings(QObject *parent = nullptr);                         //!< GalaxySettings Constructor
        ~GalaxySettings();                                                           //!< GalaxySettings Destructor
        //
        QString readSettings(const QString thisSetting, const QString thisDefault);  //!< readSettings
        bool readSettingsBool(const QString thisSetting, bool thisDefault);          //!< readSettingsBool
        int readSettingsInt(const QString thisSetting, int thisDefault);             //!< readSettingsInt
        //
        void writeSettings(const QString thisSetting, const QString thisValue);      //!< writeSettings
        //
        QSettings *getSettings();                                                    //!< getSettings
        QString getDataPath(const QString thisFileName);                             //!< GetDataPath
        QString getOrgName();                                                        //!< getOrgName
        void setOrgName(const QString &thisOrgName);                                 //!< setOrgName
        QString getOrgDomain();                                                      //!<  myOrganizationDomain
        void setOrgDomain(const QString &thisOrgDomain);
        // Application Name
        QString getAppName();                                                        //!< myApplicationName
        void setAppName(const QString &thisAppName);                                 //!< setAppName
        // UserName
        QString combinePathFileName(const QString thisPath, const QString thisFileName);  //!< combinePathFileName
        bool isFileExists(QString thisFile);                                         //!< File Functions
        bool isFileMake(const QString &thisPath, const QString &thisFileName);       //!< isFileMake
        bool isPathExists(QString thisPath);                                         //!< isPathExists
        bool isPathMake(const QString &thisRootPath, const QString &thisPath);       //!< isPathMake
        bool isMakeDir(const QString &thisPath);                                     //!< isMakeDir
        bool isSetting(const QString &thisFieldName);                                //!< isSetting
        // Screen Geometry
        void setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin);    //!< Screen Geometry
        void getGeometry();                                                          //!< getGeometry
        QPoint getGeometryPos();                                                     //!< getGeometryPos
        QSize getGeometrySize();                                                     //!< getGeometrySize
        bool getGeometryMax();                                                       //!< getGeometryMax
        bool getGeometryMin();                                                       //!< getGeometryMin
        QString readFile(const QString &thisFileName);                               //!< readFile

        const QString ConstSettingsApplicationName = "SettingsApplicationName"; //!< \c ConstSettingsApplicationName \brief QSettings Field Settings Application Name.
        const QString ConstSettingsOrgName         = "SettingsOrgName";         //!< \c ConstSettingsOrgName         \brief QSettings Field Settings Org Name.
        const QString ConstSettingsOrgDomain       = "SettingsOrgDomain";       //!< \c ConstSettingsOrgDomain       \brief QSettings Field Settings Org Domain.
        const QString ConstSettingsGeometryPos     = "SettingsGeometryPos";     //!< \c ConstSettingsGeometryPos     \brief QSettings Field Settings Geometry Pos.
        const QString ConstSettingsGeometrySize    = "SettingsGeometrySize";    //!< \c ConstSettingsGeometrySize    \brief QSettings Field Settings Geometry Size.
        const QString ConstSettingsGeometryMax     = "SettingsGeometryMax";     //!< \c ConstSettingsGeometryMax     \brief QSettings Field Settings Geometry Max.
        const QString ConstSettingsGeometryMin     = "SettingsGeometryMin";     //!< \c ConstSettingsGeometryMin     \brief QSettings Field Settings Geometry Min.
        const QString ConstDefaultAppName          = "Galaxy Calculator";       //!< \c ConstDefaultAppName          \brief Default App Name.
        const QString ConstDefaultOrgName          = "Light-Wizzard";           //!< \c ConstDefaultOrgName          \brief Default Org Name.
        // This is the User Name and Project or GitHub URL, but does not have to be
        const QString ConstDefaultDomain                = "https://github.com"; //!< \c ConstDefaultDomain      \brief Default Domain, This can be any URL.
        // "https://github.com/Light-Wizzard/WeBookClient";
        const QString ConstDefaultOrgDomain             = ConstDefaultDomain + "/" + ConstDefaultOrgName + "/" + ConstDefaultAppName; //!< \c ConstDefaultOrgDomain \brief Default Org Domain .
        const QPoint  ConstDefaultGeometryPos           = QPoint(10, 10);   //!< \c ConstDefaultGeometryPos     \brief Top, Left.
        const QSize   ConstDefaultGeometrySize          = QSize(1134, 817); //!< \c ConstDefaultGeometrySize    \brief Width x Height.

    private:
        QSettings               *mySettings             = nullptr;                          //!< \c mySettings              \brief QSettings is used for this class.
        bool                    isDebugMessage          = false;                            //!< \c isDebugMessage          \brief true of false
        QString                 myOrganizationName      = "";                               //!< \c myOrganizationName      \brief Organization Name.
        QString                 myOrganizationDomain    = "";                               //!< \c myOrganizationDomain    \brief Organization Domain.
        QString                 myApplicationName       = "";                               //!< \c myApplicationName       \brief Application Name.
        QPoint                  myGeometryPos;                                              //!< \c myGeometryPos           \brief Windows Geometry Pos
        QSize                   myGeometrySize;                                             //!< \c myGeometrySize          \brief Windows Geometry Size
        bool                    myGeometryMax;                                              //!< \c myGeometryMax           \brief Windows Geometry Max
        bool                    myGeometryMin;                                              //!< \c myGeometryMin           \brief Windows Geometry Min
};
#endif // GALAXYSETTINGS_H
/*** ************************* End of File ***********************************/
