#ifndef MYSQLDBTMODEL_H
#define MYSQLDBTMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QtDebug>
#include <QtSql>
#include <QtWidgets>

#include "MyOrgSettings.h"
/************************************************
 * @brief GalaxyClass.
 * GalaxyClass
* myTableModel.insertRecord(CurrentTrackNumber, TrackEngines, MaxSpeed, MinSpeed, LpFrequency, OrbitDist, TrackFreq});
 ***********************************************/
class GalaxyClass
{
    public:
        GalaxyClass(const QString &thisCurrentTrackNumber, const QString &thisTrackEngines, const QString &thisMaxSpeed, const QString &thisMinSpeed, const QString &thisLpFrequency, const QString &thisOrbitDist, const QString &thisTrackFreq)
            : myCurrentTrackNumber{thisCurrentTrackNumber}, myTrackEngines{thisTrackEngines}, myMaxSpeed{thisMaxSpeed}, myMinSpeed{thisMinSpeed}, myLpFrequency{thisLpFrequency}, myOrbitDist{thisOrbitDist}, myTrackFreq{thisTrackFreq} {}
        QString getCurrentTrackNumber() const { return myCurrentTrackNumber; }
        QString getTrackEngines()       const { return myTrackEngines; }
        QString getMaxSpeed()           const { return myMaxSpeed; }
        QString getMinSpeed()           const { return myMinSpeed; }
        QString getLpFrequency()        const { return myLpFrequency; }
        QString getOrbitDist()          const { return myOrbitDist; }
        QString getTrackFreq()          const { return myTrackFreq; }

        void setCurrentTrackNumber(const QString &s) { myCurrentTrackNumber = s; }
        void setTrackEngines(const QString &s)       { myTrackEngines = s; }
        void setMaxSpeed(const QString &s)           { myMaxSpeed = s; }
        void setMinSpeed(const QString &s)           { myMinSpeed = s; }
        void setLpFrequency(const QString &s)        { myLpFrequency = s; }
        void setOrbitDist(const QString &s)          { myOrbitDist = s; }
        void setTrackFreq(const QString &s)          { myTrackFreq = s; }

    private:
        QString myCurrentTrackNumber, myTrackEngines, myMaxSpeed, myMinSpeed, myLpFrequency, myOrbitDist, myTrackFreq;
};
/************************************************
 * @brief SQL Database Table Model.
 * \class MySqlDbtModel
 * @author Jeffrey Scott Flesher
 ***********************************************/
class MySqlDbtModel : public QAbstractTableModel
{
        Q_OBJECT
    public:
        MySqlDbtModel(QObject *parent = 0); //!< DataTable
        ~MySqlDbtModel();
        // Public
        MyOrgSettings  *mySetting;                                  //!< \c mySetting @brief Domain Settings
        // Constants
        const QString MY_SQL_DEFAULT     = "QSQLITE";          //!< \c myDefaultSql @brief Default Sql Driver QSQLITE
        const QString MY_SQL_COMBO_INDEX = "SqlComboBoxIndex"; //!< \c mySqlComboBoxIndex @brief Sql ComboBox Index
        const QString MY_SQL_COMBO_VALUE = "SqlComboBoxValue"; //!< \c mySqlComboBoxValue @brief Sql ComboBox Value
        const QString MY_SQL_COMBO_STATE = "SqlComboBoxState"; //!< \c SqlComboBoxState @brief Sql ComboBox Value
        const QString MY_SQL_PROJECT_ID  = "ProjectID";        //!< \c myDefaultSql @brief Default Sql Driver QSQLITE
        const QString MY_SQL_DB_MEMORY   = "DbMemory";         //!< \c myDbMemory @brief Sql Driver DbMemory

        int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;    //!< rowCount
        int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE; //!< columnCount

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;                       //!< data
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE; //!< headerData
        void clearRecords();                                        //!< clearRecords

        bool createDataBaseConnection();                            //!< createDataBaseConnection
        bool isDbTable(const QString &thisTable, QSqlDatabase *db); //!< isDbTable
        void setSqlDriver(const QString &thisDriver);               //!< setSqlDriver
        QString getSqlDriver();                                     //!< getSqlDriver

        void setSqlTableName(const QString &thisTableName);         //!< setSqlTableName
        QString getSqlTableName();                                  //!< getSqlTableName

        void setSqlHostName(const QString &thisHostName);           //!< setSqlHostName
        QString getSqlHostName();                                   //!< getSqlHostName

        void setSqlUserName(const QString &thisUserName);           //!< setSqlUserName
        QString getSqlUserName();                                   //!< getSqlUserName

        void setSqlPassword(const QString &thisPassword);           //!< setSqlPassword
        QString getSqlPassword();                                   //!< getSqlPassword

        void setSqlDatabaseName(const QString &thisPassword);       //!< setSqlDatabaseName
        QString getSqlDatabaseName();                               //!< getSqlDatabaseName

        void setSqlDatabase(const QSqlDatabase &thisDatabase);      //!< set Sql Database
        QSqlDatabase getSqlDatabase();                              //!< get Sql Database

        void setConnectionName(const QString &thisConnectionName);  //!< setConnectionName
        QString getConnectionName();                                //!< getConnectionName

        void setComboBoxSqlValue(const QString &thisComboBoxSqlValue);
        QString getComboBoxSqlValue();

        void setDebugMessage(bool thisState);
        bool getDebugMessage();

        bool checkDatabase();                                               //!< checkDatabase
        bool runQuery(const QString &thisQuery);                            //!< runQuery
        bool insertPlanet(const QString &thisPlanetName, const QString &thisDiameter, const QString &thisSidereal, const QString &thisOrbitalDistance, const QString &thisOrbitalPeriod); //!< insertPlanet

        int getRunReturnCode();
        QString runProcces(const QString &thisExePath, const QString &thisArgument, bool isWait, int thisWaitTimeSec);
        bool moveDb(const QString &thisSourceFile, const QString &thisSourcePath, const QString &thisDestinationFolder);
        // Project ID
        void setProjectID(const QString &thisProjectID);                    //!< set Project ID
        QString getProjectID();                                             //!< get Project ID
        // Project Name
        void setProjectName(const QString &thisProjectName);
        QString getProjectName();

    public slots:
         void onInsertGalaxyRecord(const QString &thisCurrentTrackNumber, const QString &thistrackEngines, const QString &thisMaxSpeed, const QString &thisMinSpeed, const QString &thisLpFrequency, const QString &thisOrbitDist, const QString &thisNthTrack); //!< onInsertRecord

    signals:
        void sendGalaxyDataTableProgress();                         //!< send Galaxy DataTable Progress

    private:
        QList<GalaxyClass>  myGalaxy;                                   //!< \c myGalaxy           @brief Galaxy
        QSqlDatabase        myDb;                                       //!< \c myDb               @brief Database
        QString             myDatabaseName     = "GalaxyCalculator";    //!< \c myDatabaseName     @brief Sql Driver DatabaseName with extention
        QString             myTableName        = "Galaxy";;             //!< \c myTableName        @brief TableName
        QString             mySqlDriver        = "NOTSET";              //!< \c mySqlDriver        @brief Sql Driver NOTSET
        QString             myHostName         = "localhost";           //!< \c myHostName         @brief Sql HostName location of your MySQL server and database
        QString             myUserName         = "";                    //!< \c myUserName         @brief Sql Driver CalcDecimal
        QString             myPassword         = "";                    //!< \c myPassword         @brief Sql Driver CalcDecimal
        QString             myConnectionName   = "Galaxy";              //!< \c myConnectionName   @brief myConnectionName
        bool                isDebugMessage     = false;                 //!< \c isDebugMessage     @brief Debug Message
        QString             myComboBoxSqlValue = "-1";                  //!< \c myComboBoxSqlValue @brief ComboBox Sql Value
        QString             myInsertID         = "-1";                  //!< \c myInsertID         @brief InsertID for last SQL insert
        int                 myRunReturnCode    = 1;                     //!< \c myRunReturnCode    @brief Run Return Code
        QString             myProjectID        = "-1";                  //!< \c myProjectID        @brief Project ID
        QString             myProjectName      = "";                    //!< \c myProjectName      @brief Project Name

};
#endif // MYSQLDBTMODEL_H
/*** ************************* End of File ***********************************/
