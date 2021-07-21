#include "GalaxyDataTable.h"
/******************************************************************************
* \class DataTable
*******************************************************************************/
GalaxyDataTable::GalaxyDataTable(QObject *parent) : QAbstractTableModel(parent)
{
    // Galaxy Settings
    myGalaxySettings = new GalaxySettings();
}
/******************************************************************************
* \fn rowCount
*******************************************************************************/
int GalaxyDataTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (isDebugMessage) qDebug() << "rowCount";
    return myGalaxy.length();
}
/******************************************************************************
* \fn columnCount
*******************************************************************************/
int GalaxyDataTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (isDebugMessage) qDebug() << "columnCount";
    return 7;
}
/******************************************************************************
* \fn data
* myCurrentTrackNumber, myTrackEngines, myMaxSpeed, myMinSpeed,
* myLpFrequency, myOrbitDist, myTrackFreq
*******************************************************************************/
QVariant GalaxyDataTable::data(const QModelIndex &index, int role) const
{
    if (isDebugMessage) qDebug() << "data";
    if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::TextAlignmentRole) return {};

    const auto & galaxy = myGalaxy[index.row()];

    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column())
        {
            case 0: return Qt::AlignRight;
            case 1: return Qt::AlignRight;
            case 2: return Qt::AlignRight;
            case 3: return Qt::AlignRight;
            case 4: return Qt::AlignRight;
            case 5: return Qt::AlignRight;
            case 6: return Qt::AlignRight;
            default: return {};
        };
    }

    switch (index.column())
    {
        case 0: return galaxy.getCurrentTrackNumber();
        case 1: return galaxy.getTrackEngines();
        case 2: return galaxy.getMaxSpeed();
        case 3: return galaxy.getMinSpeed();
        case 4: return galaxy.getLpFrequency();
        case 5: return galaxy.getOrbitDist();
        case 6: return galaxy.getTrackFreq();
        default: return {};
    };
}
/******************************************************************************
* \fn headerData
*******************************************************************************/
QVariant GalaxyDataTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (isDebugMessage) qDebug() << "headerData";
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == 0)      { return QString("Track");  }
        else if (section == 1) { return QString("Trinary Engines"); }
        else if (section == 2) { return QString("Max"); }
        else if (section == 3) { return QString("Min"); }
        else if (section == 4) { return QString("Frequency"); }
        else if (section == 5) { return QString("Distance");  }
        else if (section == 6) { return QString("Track Frequency"); }
    }
    return QVariant();
}
/******************************************************************************
* \fn onInsertGalaxyRecord
* currentTrackNumber, trackEngines, maxSpeed, minSpeed,
* lpFrequency, orbitDist, trackFreq
*******************************************************************************/
void GalaxyDataTable::onInsertGalaxyRecord(const QString &thisCurrentTrackNumber,const QString &thistrackEngines,const QString &thisMaxSpeed,const QString &thisMinSpeed,const QString &thisLpFrequency,const QString &thisOrbitDist,const QString &thisTrackFreq)
{
    if (isDebugMessage) qDebug() << "insertRecord c++ msgx: " << thisCurrentTrackNumber << thistrackEngines << thisMaxSpeed << thisMinSpeed << thisLpFrequency<< thisOrbitDist << thisTrackFreq;
    beginInsertRows({}, myGalaxy.count(), myGalaxy.count());
    GalaxyClass theGalaxy(thisCurrentTrackNumber, thistrackEngines, thisMaxSpeed, thisMinSpeed, thisLpFrequency, thisOrbitDist, thisTrackFreq);
    myGalaxy.append(theGalaxy);
    endInsertRows();

    emit sendGalaxyDataTableProgress();
}
/******************************************************************************
* \fn clearRecords
*******************************************************************************/
void GalaxyDataTable::clearRecords()
{
    if (isDebugMessage) qDebug() << "clearRecords";
    for( int i = 0; i < myGalaxy.count(); ++i )
    {
        myGalaxy.removeAt(i);
    }
    myGalaxy.clear();
}
/******************************************************************************
* \fn isDbTable
*******************************************************************************/
bool GalaxyDataTable::isDbTable(const QString thisTable, QSqlDatabase *db)
{
    if (isDebugMessage) qDebug() << "isDatabase";
    QStringList tables = db->tables();
    if (tables.contains(thisTable, Qt::CaseInsensitive))  { return true; }
    else                                                  { return false; }
}
/******************************************************************************
* \fn setSqlDatabase
*******************************************************************************/
void GalaxyDataTable::setSqlDatabase(QSqlDatabase thisDatabase)
{
    if (isDebugMessage) qDebug() << "setSqlDatabase";
    myDb = thisDatabase;
}
/******************************************************************************
* \fn getSqlDatabase
*******************************************************************************/
QSqlDatabase GalaxyDataTable::getSqlDatabase()
{
    if (isDebugMessage) qDebug() << "getSqlDatabase";
    return myDb;
}
/******************************************************************************
* \fn setSqlDriver
*******************************************************************************/
void GalaxyDataTable::setSqlDriver(const QString thisDriver)
{
    if (isDebugMessage) qDebug() << "setSqlDriver";
    mySqlDriver = thisDriver;
}
/******************************************************************************
* \fn getSqlDriver
*******************************************************************************/
QString GalaxyDataTable::getSqlDriver()
{
    if (isDebugMessage) qDebug() << "getSqlDriver";
    return mySqlDriver;
}
/******************************************************************************
* \fn setSqlTableName
*******************************************************************************/
void GalaxyDataTable::setSqlTableName(const QString thisTableName)
{
    if (isDebugMessage) qDebug() << "setSqlTableName";
    myTableName = thisTableName;
}
/******************************************************************************
* \fn getSqlTableName
*******************************************************************************/
QString GalaxyDataTable::getSqlTableName()
{
    if (isDebugMessage) qDebug() << "getSqlTableName";
    return myTableName;
}
/******************************************************************************
* \fn setSqlHostName
*******************************************************************************/
void GalaxyDataTable::setSqlHostName(const QString thisHostName)
{
    if (isDebugMessage) qDebug() << "setSqlHostName";
    myHostName = thisHostName;
}
/******************************************************************************
* \fn getSqlHostName
*******************************************************************************/
QString GalaxyDataTable::getSqlHostName()
{
    if (isDebugMessage) qDebug() << "getSqlHostName";
    return myHostName;
}
/******************************************************************************
* \fn setSqlUserName
*******************************************************************************/
void GalaxyDataTable::setSqlUserName(const QString thisUserName)
{
    if (isDebugMessage) qDebug() << "setSqlUserName";
    myUserName = thisUserName;
}
/******************************************************************************
* \fn getSqlUserName
*******************************************************************************/
QString GalaxyDataTable::getSqlUserName()
{
    if (isDebugMessage) qDebug() << "getSqlUserName";
    return myUserName;
}
/******************************************************************************
* \fn setSqlDatabaseName
*******************************************************************************/
void GalaxyDataTable::setSqlDatabaseName(const QString thisPassword)
{
    if (isDebugMessage) qDebug() << "setSqlDatabaseName";
    myDatabaseName = thisPassword;
}
/******************************************************************************
* \fn getSqlDatabaseName
*******************************************************************************/
QString GalaxyDataTable::getSqlDatabaseName()
{
    if (isDebugMessage) qDebug() << "getSqlDatabaseName";
    return myDatabaseName;
}
/******************************************************************************
* \fn setSqlPassword
*******************************************************************************/
void GalaxyDataTable::setSqlPassword(const QString thisPassword)
{
    if (isDebugMessage) qDebug() << "setSqlPassword";
    myPassword = thisPassword;
}
/******************************************************************************
* \fn getSqlPassword
*******************************************************************************/
QString GalaxyDataTable::getSqlPassword()
{
    if (isDebugMessage) qDebug() << "getSqlPassword";
    return myPassword;
}
/******************************************************************************
* \fn createDataBaseConnection
*******************************************************************************/
bool GalaxyDataTable::createDataBaseConnection()
{
    if (isDebugMessage) qDebug() << "createDataBaseConnection";
    // Database Driver
    myDb = QSqlDatabase::addDatabase(mySqlDriver); //!< db


    if (isDbMemory) // ui->checkBoxSettingsMemory->isChecked()
    {
        myDb.setDatabaseName(":memory:");
    }
    else
    {
        myDb.setDatabaseName(myGalaxySettings->getDataPath("GalaxyCalculator.db"));
        if (mySqlDriver == "QSQLITE" || mySqlDriver == "QSQLITE2")
        {
            // SQLite version 2 Note: obsolete since Qt 5.14
            // SQLite version 3
            //    myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(QString("%1.db").arg(getSqlDatabaseName()));
            //    myDb.setUserName(getSqlUserName());
            //    myDb.setPassword(getSqlPassword());
            //
        }
        else if (mySqlDriver == "QDB2")
        {
            // IBM DB2 (version 7.1 and above)
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QIBASE")
        {
            // Borland InterBase
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QMYSQL" || mySqlDriver == "MARIADB")
        {
            // MySQL or MariaDB (version 5.0 and above)
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QOCI")
        {
            // Oracle Call Interface Driver
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QPSQL")
        {
            // PostgreSQL (versions 7.3 and above)
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QTDS")
        {
            // Sybase Adaptive Server - Note: obsolete since Qt 4.7
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
    } // end if (isDbMemory)
    if (!myDb.open())
    {
        if(!QSqlDatabase::isDriverAvailable(mySqlDriver))
        {
            QMessageBox::critical(nullptr, QObject::tr("Database Driver for Sqlite is missing"), QObject::tr("Install Sqlite"), QMessageBox::Cancel);
            return false;
        }
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database: %1").arg(myDb.lastError().text()), QObject::tr("Unable to establish a database connection.\nClick Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    return true;
} // end createDataBaseConnection
/*** ************************* End of File ***********************************/
