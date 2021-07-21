#ifndef GALAXYDATATABLE_H
#define GALAXYDATATABLE_H

#include <QObject>
#include <QAbstractTableModel>
#include <QtDebug>
#include <QtSql>
#include <QtWidgets>

#include "GalaxySettings.h"
/******************************************************************************
* \fn GalaxyClass
* myTableModel.insertRecord(CurrentTrackNumber, TrackEngines, MaxSpeed, MinSpeed, LpFrequency, OrbitDist, TrackFreq});
*******************************************************************************/
class GalaxyClass
{
        QString myCurrentTrackNumber, myTrackEngines, myMaxSpeed, myMinSpeed, myLpFrequency, myOrbitDist, myTrackFreq;
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

        void setCurrentTrackNumber(const QString s) { myCurrentTrackNumber = s; }
        void setTrackEngines(const QString s)       { myTrackEngines = s; }
        void setMaxSpeed(const QString s)           { myMaxSpeed = s; }
        void setMinSpeed(const QString s)           { myMinSpeed = s; }
        void setLpFrequency(const QString s)        { myLpFrequency = s; }
        void setOrbitDist(const QString s)          { myOrbitDist = s; }
        void setTrackFreq(const QString s)          { myTrackFreq = s; }
};
/******************************************************************************
* \fn DataTable
*******************************************************************************/
class GalaxyDataTable : public QAbstractTableModel
{
        Q_OBJECT
    public:
        GalaxyDataTable(QObject *parent = 0); //!< DataTable


        int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;    //!< rowCount
        int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE; //!< columnCount

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;                       //!< data
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE; //!< headerData
        void clearRecords();                                        //!< clearRecords

        bool createDataBaseConnection();                            //!< createDataBaseConnection
        bool isDbTable(const QString thisTable, QSqlDatabase *db);  //!< isDbTable
        void setSqlDriver(const QString thisDriver);                //!< setSqlDriver
        QString getSqlDriver();                                     //!< getSqlDriver

        void setSqlTableName(const QString thisTableName);          //!< setSqlTableName
        QString getSqlTableName();                                  //!< getSqlTableName

        void setSqlHostName(const QString thisHostName);            //!< setSqlHostName
        QString getSqlHostName();                                   //!< getSqlHostName

        void setSqlUserName(const QString thisUserName);            //!< setSqlUserName
        QString getSqlUserName();                                   //!< getSqlUserName

        void setSqlPassword(const QString thisPassword);            //!< setSqlPassword
        QString getSqlPassword();                                   //!< getSqlPassword

        void setSqlDatabaseName(const QString thisPassword);        //!< setSqlDatabaseName
        QString getSqlDatabaseName();                               //!< getSqlDatabaseName

        void setSqlDatabase(QSqlDatabase thisDatabase);             //!< set Sql Database
        QSqlDatabase getSqlDatabase();                              //!< get Sql Database

    public slots:
         void onInsertGalaxyRecord(const QString &thisCurrentTrackNumber, const QString &thistrackEngines, const QString &thisMaxSpeed, const QString &thisMinSpeed, const QString &thisLpFrequency, const QString &thisOrbitDist, const QString &thisNthTrack); //!< onInsertRecord

    signals:
        void sendGalaxyDataTableProgress();                         //!< send Galaxy DataTable Progress

    private:
        QList<GalaxyClass>  myGalaxy;                               //!< \c myGalaxy         \brief Galaxy
        GalaxySettings     *myGalaxySettings;                       //!< \c myGalaxySettings \brief Galaxy Settings
        QSqlDatabase        myDb;                                   //!< \c myDb             \brief Database
        QString             myDatabaseName = "GalaxyCalculator";    //!< \c myDatabaseName   \brief Sql Driver DatabaseName with extention
        QString             myTableName = "Galaxy";;                //!< \c myTableName      \brief TableName
        QString             mySqlDriver = "QSQLITE";                //!< \c mySqlDriver      \brief Sql Driver QSQLITE
        QString             myHostName = "localhost";               //!< \c myHostName       \brief Sql HostName location of your MySQL server and database
        QString             myUserName = "";                        //!< \c myUserName       \brief Sql Driver CalcDecimal
        QString             myPassword = "";                        //!< \c myPassword       \brief Sql Driver CalcDecimal
        bool                isDbMemory = false;                     //!< \c isDbMemory       \brief Db Memory
        bool                isDebugMessage = false;                 //!< \c isDebugMessage   \brief Debug Message
};
#endif // GALAXYDATATABLE_H
/*** ************************* End of File ***********************************/
