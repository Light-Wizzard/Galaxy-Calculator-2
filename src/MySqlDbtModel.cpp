#include "MySqlDbtModel.h"
/************************************************
 * @brief MySqlDbtModel Constructor.
 * MySqlDbtModel
 ***********************************************/
MySqlDbtModel::MySqlDbtModel(QObject *parent) : QAbstractTableModel(parent)
{
    // MySettings Settings
    mySetting = new MyOrgSettings(parent);
}
/************************************************
 * @brief MySqlDbtModel Deconstructor.
 * ~MySqlDbtModel
 ***********************************************/
MySqlDbtModel::~MySqlDbtModel()
{
    #ifdef USE_SQL_FLAG
    if (myDb.isOpen()) { myDb.close(); }
    #endif
}
/************************************************
 * @brief set Debug Message.
 * setDebugMessage
 ***********************************************/
void MySqlDbtModel::setDebugMessage(bool thisState)
{
    isDebugMessage = thisState;
}
/************************************************
 * @brief get Debug Message.
 * getDebugMessage
 ***********************************************/
bool MySqlDbtModel::getDebugMessage()
{
    return isDebugMessage;
}
/************************************************
 * @brief row Count.
 * rowCount
 ***********************************************/
int MySqlDbtModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    setMessage("rowCount");
    return myGalaxy.length();
}
/************************************************
 * @brief column Count.
 * columnCount
 ***********************************************/
int MySqlDbtModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    setMessage("columnCount");
    return 7;
}
/************************************************
 * @brief data.
 * data
 ***********************************************/
QVariant MySqlDbtModel::data(const QModelIndex &index, int role) const
{
    setMessage("data");
    if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::TextAlignmentRole) return {};
    //
    const auto & galaxy = myGalaxy[index.row()];
    //
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
    //
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
/************************************************
 * @brief header Data.
 * headerData
 ***********************************************/
QVariant MySqlDbtModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    setMessage("headerData");
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
/************************************************
 * @brief clear Records.
 * clearRecords
 ***********************************************/
void MySqlDbtModel::clearRecords()
{
    setMessage("clearRecords");
    for( int i = 0; i < myGalaxy.count(); ++i )
    {
        myGalaxy.removeAt(i);
    }
    myGalaxy.clear();
}
#ifdef USE_SQL_FLAG
/************************************************
 * @brief is Db Table.
 * isDbTable
 ***********************************************/
bool MySqlDbtModel::isDbTable(const QString &thisTable, QSqlDatabase *db)
{
    setMessage("isDatabase");
    QStringList tables = db->tables();
    if (tables.contains(thisTable, Qt::CaseInsensitive))  { return true; }
    else                                                  { return false; }
}
/************************************************
 * @brief set Sql Database.
 * setSqlDatabase
 ***********************************************/
void MySqlDbtModel::setSqlDatabase(const QSqlDatabase &thisDatabase)
{
    setMessage("setSqlDatabase");
    myDb = thisDatabase;
}
/************************************************
 * @brief get Sql Database.
 * getSqlDatabase
 ***********************************************/
QSqlDatabase MySqlDbtModel::getSqlDatabase()
{
    setMessage("getSqlDatabase");
    return myDb;
}
#endif
/************************************************
 * @brief set Connection Name.
 * setConnectionName
 ***********************************************/
void MySqlDbtModel::setConnectionName(const QString &thisConnectionName)
{
    setMessage("setConnectionName");
    myConnectionName = thisConnectionName;
}
/************************************************
 * @brief get Connection Name.
 * getConnectionName
 ***********************************************/
QString MySqlDbtModel::getConnectionName()
{
    setMessage("getConnectionName");
    return myConnectionName;
}
/************************************************
 * @brief get Sql Driver.
 * getSqlDriver
 ***********************************************/
QString MySqlDbtModel::getSqlDriver()
{
    setMessage("getSqlDriver");
    return mySqlDriver;
}
/************************************************
 * @brief set Sql Table Name.
 * setSqlTableName
 ***********************************************/
void MySqlDbtModel::setSqlTableName(const QString &thisTableName)
{
    setMessage("setSqlTableName");
    myTableName = thisTableName;
}
/************************************************
 * @brief get Sql Table Name.
 * getSqlTableName
 ***********************************************/
QString MySqlDbtModel::getSqlTableName()
{
    setMessage("getSqlTableName");
    return myTableName;
}
/************************************************
 * @brief set Sql Host Name.
 * setSqlHostName
 ***********************************************/
void MySqlDbtModel::setSqlHostName(const QString &thisHostName)
{
    setMessage("setSqlHostName");
    myHostName = thisHostName;
}
/************************************************
 * @brief get Sql Host Name.
 * getSqlHostName
 ***********************************************/
QString MySqlDbtModel::getSqlHostName()
{
    setMessage("getSqlHostName");
    return myHostName;
}
/************************************************
 * @brief set Sql User Name.
 * setSqlUserName
 ***********************************************/
void MySqlDbtModel::setSqlUserName(const QString &thisUserName)
{
    setMessage("setSqlUserName");
    myUserName = thisUserName;
}
/************************************************
 * @brief get Sql User Name.
 * getSqlUserName
 ***********************************************/
QString MySqlDbtModel::getSqlUserName()
{
    setMessage("getSqlUserName");
    return myUserName;
}
/************************************************
 * @brief set Sql Database Name.
 * setSqlDatabaseName
 ***********************************************/
void MySqlDbtModel::setSqlDatabaseName(const QString &thisPassword)
{
    setMessage("setSqlDatabaseName");
    myDatabaseName = thisPassword;
}
/************************************************
 * @brief get Sql Database Name.
 * getSqlDatabaseName
 ***********************************************/
QString MySqlDbtModel::getSqlDatabaseName()
{
    setMessage("getSqlDatabaseName");
    return myDatabaseName;
}
/************************************************
 * @brief set Sql Password.
 * setSqlPassword
 ***********************************************/
void MySqlDbtModel::setSqlPassword(const QString &thisPassword)
{
    setMessage("setSqlPassword");
    myPassword = thisPassword;
}
/************************************************
 * @brief get Sql Password.
 * getSqlPassword
 ***********************************************/
QString MySqlDbtModel::getSqlPassword()
{
    setMessage("getSqlPassword");
    return myPassword;
}
/************************************************
 * @brief set ComboBox Sql Value.
 * setComboBoxSqlValue
 ***********************************************/
void MySqlDbtModel::setComboBoxSqlValue(const QString &thisComboBoxSqlValue)
{
    myComboBoxSqlValue = thisComboBoxSqlValue;
}
/************************************************
 * @brief get ComboBox Sql Value.
 * getComboBoxSqlValue
 ***********************************************/
QString MySqlDbtModel::getComboBoxSqlValue()
{
    return myComboBoxSqlValue;
}
/************************************************
 * @brief set Sql Driver.
 * setSqlDriver
 ***********************************************/
void MySqlDbtModel::setSqlDriver(const QString &thisDriver)
{
    setMessage("setSqlDriver");
    QString theDriver = thisDriver;
    if (theDriver.length() == 0)  { theDriver = mySetting->myConstants->MY_SQL_DEFAULT; }
    // Check for Database memory setting
    // ui->checkBoxSettingsMemory->isChecked() || combobox
    // Database Driver
    if (theDriver == ":memory:")
    {
        // SQLite version 3 SQLite version 2 Note: obsolete since Qt 5.14
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QSQLITE" || theDriver == "QSQLITE2")
    {
        // SQLite version 3 SQLite version 2 Note: obsolete since Qt 5.14
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QMYSQL" || theDriver == "MARIADB")
    {
        // MySQL or MariaDB (version 5.0 and above)
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QPSQL")
    {
        // PostgreSQL (versions 7.3 and above)
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QDB2")
    {
        // IBM DB2 (version 7.1 and above)
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QIBASE")
    {
        // Borland InterBase
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QOCI")
    {
        // Oracle Call Interface Driver
        mySqlDriver = theDriver;
    }
    else if (theDriver == "QTDS")
    {
        // Sybase Adaptive Server - Note: obsolete since Qt 4.7
        mySqlDriver = theDriver;
    }
    else
    {
        mySqlDriver = theDriver;
    }
} // end setSqlDriver
/************************************************
 * @brief create DataBase Connection.
 * createDataBaseConnection
 ***********************************************/
bool MySqlDbtModel::createDataBaseConnection()
{
    setMessage("createDataBaseConnection");
#ifdef USE_SQL_FLAG
    // Make sure Drive is set
    if (mySqlDriver == "NOTSET") { setSqlDriver(mySetting->myConstants->MY_SQL_DEFAULT); }
    QString theDb = getSqlDatabaseName();
    // Database Driver
    if (mySqlDriver == ":memory:")
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE"); //!< set myDb SQLite
        myDb.setDatabaseName(":memory:");
    }
    else
    {
        if (mySqlDriver == "QSQLITE" || mySqlDriver == "QSQLITE2")
        {   //!< set myDb QSQLITE or QSQLITE2
            // SQLite version 3 and SQLite version 2 Note: obsolete since Qt 5.14
            if (theDb.contains(".db"))
            {
                if (!mySetting->isFileExists(theDb))
                {
                    qCritical() << "createDataBaseConnection new DB: " << theDb;
                }
            }
            else
            {
                theDb = QString("%1%2%3.db").arg(mySetting->getAppDataLocation(), QDir::separator(), getSqlDatabaseName());
            }
            //
            myDb = QSqlDatabase::addDatabase(mySqlDriver); //!< set myDb SQLite
            myDb.setDatabaseName(theDb);
            //    myDb.setHostName(getSqlHostName());
            //    myDb.setUserName(getSqlUserName());
            //    myDb.setPassword(getSqlPassword());
            //
        }
        else if (mySqlDriver == "QDB2")
        {   //!< set myDb QDB2
            // IBM DB2 (version 7.1 and above)
            myDb = QSqlDatabase::addDatabase(mySqlDriver, myConnectionName);
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QIBASE")
        {   //!< set myDb QIBASE
            // Borland InterBase
            myDb = QSqlDatabase::addDatabase(mySqlDriver, myConnectionName);
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QMYSQL" || mySqlDriver == "MARIADB")
        {   //!< set myDb QMYSQL or MARIADB
            // MySQL or MariaDB (version 5.0 and above)
            myDb = QSqlDatabase::addDatabase(mySqlDriver, myConnectionName);
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QOCI")
        {   //!< set myDb QOCI
            // Oracle Call Interface Driver
            myDb = QSqlDatabase::addDatabase(mySqlDriver, myConnectionName);
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QPSQL")
        {   //!< set myDb QPSQL
            // PostgreSQL (versions 7.3 and above)
            myDb = QSqlDatabase::addDatabase(mySqlDriver, myConnectionName);
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
        else if (mySqlDriver == "QTDS")
        {   //!< set myDb QTDS
            // Sybase Adaptive Server - Note: obsolete since Qt 4.7
            myDb = QSqlDatabase::addDatabase(mySqlDriver, myConnectionName);
            myDb.setHostName(getSqlHostName());
            myDb.setDatabaseName(getSqlDatabaseName());
            myDb.setUserName(getSqlUserName());
            myDb.setPassword(getSqlPassword());
        }
    } // end ! if (:memory:)
    if (!myDb.open())
    {
        if(!QSqlDatabase::isDriverAvailable(mySqlDriver))
        {
            mySetting->showMessageBox(tr("Database SQL Driver is missing").toLocal8Bit(), tr("Install SQL").toLocal8Bit(), mySetting->Critical);
            return false;
        }
        else
        {
            mySetting->showMessageBox(QString("%1: %2").arg(tr("Cannot open database"), myDb.lastError().text()).toLocal8Bit(), tr("Unable to establish a database connection").toLocal8Bit(), mySetting->Critical);
            return false;
        }
    }
    // Set Settings
    mySetting->writeSettings(mySetting->myConstants->MY_SQL_DB_NAME, theDb);
    mySetting->writeSettings(mySetting->myConstants->MY_SQL_DB_TYPE, "QSQLITE");
#endif
    return true;
} // end createDataBaseConnection
/************************************************
 * @brief check Database.
 * checkDatabase
 ***********************************************/
bool MySqlDbtModel::checkDatabase()
{
    setMessage("checkDatabase");
#ifdef USE_SQL_FLAG
    // Database
    setSqlDriver(myComboBoxSqlValue);
    if (createDataBaseConnection())
    {
        myDb = getSqlDatabase();
    }
    else
    {
        return false;
    }
    //
    // Galaxy Table
    if (!isDbTable("galaxy", &myDb))
    {
        //
        if (!runQuery(QLatin1String(R"(CREATE TABLE galaxy(id integer PRIMARY KEY autoincrement, GalaxyName varchar, SunSize varchar, PlanetSize varchar, TrinaryEngines varchar, GalaxyRadius varchar, Nthtrack varchar))")))
        {
            setMessage(getSqlDriver() +  "  CREATE TABLE galaxy error:");
        }
        //
        const auto DEFAULT_GALAXY_SQL = QLatin1String(R"(INSERT INTO galaxy (GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack) values('Milky Way', '864575.9', '7926.2109', '333', '241828072282107.5071453596951', '66'))");
        if (!runQuery(DEFAULT_GALAXY_SQL))
        {
            setMessage(getSqlDriver() +  "  INSERT galaxy error:");
        }
    }
    // Planet
    //
    if (!isDbTable("planets", &myDb))
    {
        //
        if (!runQuery(QLatin1String(R"(CREATE TABLE planets(id integer PRIMARY KEY autoincrement, PlanetName varchar, Diameter varchar, Sidereal varchar, OrbitalDistance varchar, OrbitalPeriod varchar))")))
        {
            setMessage(getSqlDriver() +  "  CREATE TABLE galaxy error:");
        }
        //
        if (!insertPlanet("Sun", "864575.9", "25.379995", "1011954093357316200", "242000000"))
        {
            setMessage("Error INSERT Sun planets:");
        }
        if (!insertPlanet("Mercury", "3031.9186", "58.646225", "223700000", "87.97"))
        {
            setMessage("Error INSERT Mercury planets:");
        }
        if (!insertPlanet("Venus", "7521.0769", "243.0187", "422500000", "224.7"))
        {
            setMessage("Error INSERT Venus planets:");
        }
        if (!insertPlanet("Earth", "7926.2109", "0.99726968", "584000000", "365"))
        {
            setMessage("Error INSERT Earth planets:");
        }
        if (!insertPlanet("Moon", "2159", "27.321661", "1499070", "27.323"))
        {
            setMessage("Error INSERT Moon planets:");
        }
        if (!insertPlanet("Mars", "4217.246", "1.02595675", "888000000", "686.98"))
        {
            setMessage("Error INSERT Mars planets:");
        }
        if (!insertPlanet("Jupiter", "88731.8063", "0.41007", "3037000000", "4330.6"))
        {
            setMessage("Error INSERT Jupiter planets:");
        }
        if (!insertPlanet("Saturn", "74974.6481", "0.426", "5565900000", "10755.7"))
        {
            setMessage("Error INSERT Saturn planets:");
        }
        if (!insertPlanet("Uranus", "31763.253", "0.71833", "11201300000", "30685"))
        {
            setMessage("Error INSERT Uranus planets:");
        }
        if (!insertPlanet("Neptune", "30775.272", "0.67125", "17562300000", "60190"))
        {
            setMessage("Error INSERT Neptune planets:");
        }
    }
    // Math Constant Table
    if (!isDbTable("math", &myDb))
    {
        //
        if (!runQuery(QLatin1String(R"(CREATE TABLE math(id integer PRIMARY KEY autoincrement, Name varchar, Constant varchar))")))
        {
            setMessage(getSqlDriver() +  "  CREATE TABLE math error:");
        }
        // Constants
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Constants', ''))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // e, Napier's constant, or Euler's number
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('e', '2.71828182845904523536028747135266249'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Pythagoras' constant, square root of 2 √2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Pythagoras', '1.41421356237309504880168872420969807'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Theodorus' constant, square root of 3 √3
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Theodorus', '1.73205080756887729352744634150587236'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // square root of 5 √2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('SqrRoot5', '2.23606797749978969640917366873127623'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Euler–Mascheroni constant \gamma
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Euler–Mascheroni', '0.57721566490153286060651209008240243')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Golden ratio \varphi
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Golden-Ratio', '1.61803398874989484820458683436563811'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Meissel–Mertens constant M1
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Meissel–Mertens', '0.26149721284764278375542683860869585')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Bernstein's constant \beta
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Bernstein', '0.28016949902386913303'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Gauss–Kuzmin–Wirsing constant \lambda
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Gauss–Kuzmin–Wirsing', '0.30366300289873265859744812190155623')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Hafner–Sarnak–McCurley constant \sigma
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Hafner–Sarnak–McCurley', '0.35323637185499598454351655043268201')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Landau's constant L
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Landau', '0.5'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Omega constant Ω
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Omega', '0.56714329040978387299996866221035554'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Golomb–Dickman constant \lambda , μ {\displaystyle \mu } \mu
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Golomb–Dickman', '0.62432998854355087099293638310083724')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Cahen's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Cahen', '0.6434105462'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Twin prime constant C2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Twin-Prime', '0.66016181584686957392781211001455577'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Laplace limit
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Laplace', '0.66274341934918158097474209710925290'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Embree–Trefethen constant
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Embree–Trefethen', '0.70258')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Landau–Ramanujan constant K
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Landau–Ramanujan', '0.76422365358922066299069873125009232')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Brun's constant for prime quadruplets B4
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Brun-Prime-Quadruplets', '0.87058838'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Catalan's constant K
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Catalan', '0.91596559417721901505460351493238411'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Viswanath's constant K
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Viswanath', '1.13198824'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Apéry's constant \zeta (3)
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Apery', '1.20205690315959428539973816151144999'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Conway's constant \lambda
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Conway', '1.30357726903429639125709911215255189'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Mills' constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Mills', '1.30637788386308069046861449260260571'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Plastic constant p
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Plastic', '1.32471795724474602596090885447809734'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Ramanujan–Soldner constant \mu
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Ramanujan-Soldner', '1.45136923488338105028396848589202744'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Backhouse's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Backhouse', '1.45607494858268967139959535111654356'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Porter's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Porter', '1.4670780794'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Lieb's square ice constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Lieb-Square-Ice', '1.5396007178'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Erdős–Borwein constant EB
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Erdos–Borwein', '1.60669515241529176378330152319092458')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Niven's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Niven', '1.70521114010536776428855145343450816'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Brun's constant for twin primes B2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Brun-Twin-Primes', '1.902160583104'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Universal parabolic constant P2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Universal-Parabolic', '2.29558714939263807403429804918949039'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Feigenbaum constant \alpha
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Feigenbaum', '2.50290787509589282228390287321821578'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Sierpiński's constant K
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Sierpinski', '2.58498175957925321706589358738317116'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Khinchin's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Khinchin', '2.68545200106530644530971483548179569'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Fransén–Robinson constant F
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Fransen–Robinson', '2.80777024202851936522150118655777293')")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Lévy's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Levy', '3.27582291872181115978768188245384386'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Reciprocal Fibonacci constant \psi
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Reciprocal-Fibonacci', '3.35988566624317755317201130291892717'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
        // Feigenbaum constant \delta
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Feigenbaum', '4.66920160910299067185320382046620161'))")))
        {
            setMessage(getSqlDriver() +  "  INSERT math error:");
        }
    } // end if (!myGalaxyModel->isDbTable("math", &myDb))
    #endif
    //
    return true;
}
/************************************************
 * @brief run Query.
 * runQuery
 ***********************************************/
bool MySqlDbtModel::runQuery(const QString &thisQuery)
{
    setMessage("runQuery");
    #ifdef USE_SQL_FLAG
    QSqlQuery query; //!< SQL Query
    if (!query.exec(thisQuery))
    {
        setMessage("Error running Query: " + thisQuery + query.lastError().text() + ", SqLite error code:" + query.lastError().text());
        return false;
    }
    #endif
    return true;
}
/************************************************
 * @brief insert Planet.
 * insertPlanet
 ***********************************************/
bool MySqlDbtModel::insertPlanet(const QString &thisPlanetName, const QString &thisDiameter, const QString &thisSidereal, const QString &thisOrbitalDistance, const QString &thisOrbitalPeriod)
{
    setMessage("insertPlanet");
    QString myQuery = QString("INSERT INTO planets (PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod) values('%1', '%2', '%3', '%4', '%5')").arg(thisPlanetName, thisDiameter, thisSidereal, thisOrbitalDistance, thisOrbitalPeriod);
    setMessage("insertPlanet: " + myQuery);

//    if (!runQuery(QLatin1String(R"(INSERT INTO planets (PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod) values('%1', '%2', '%3', '%4', '%5'))").arg(thisPlanetName, thisDiameter, thisSidereal, thisOrbitalDistance, thisOrbitalPeriod)))
    if (!runQuery(myQuery))
    {
        setMessage("INSERT planets error: " + myQuery);
        return false;
    }
    return true;
}
/************************************************
 * @brief move Db.
 * @brief on Insert Galaxy Record
 * @param thisCurrentTrackNumber QString current Track Number
 * @param thistrackEngines       QString track Engines
 * @param thisMaxSpeed           QString max Speed
 * @param thisMinSpeed           QString min Speed
 * @param thisLpFrequency        QString lp Frequency
 * @param thisOrbitDist          QString orbit Dist
 * @param thisTrackFreq          QString track Freq
 ***********************************************/
void MySqlDbtModel::onInsertGalaxyRecord(const QString &thisCurrentTrackNumber,const QString &thistrackEngines,const QString &thisMaxSpeed,const QString &thisMinSpeed,const QString &thisLpFrequency,const QString &thisOrbitDist,const QString &thisTrackFreq)
{
    setMessage("insertRecord c++ msgx: " + thisCurrentTrackNumber + thistrackEngines + thisMaxSpeed + thisMinSpeed + thisLpFrequency + thisOrbitDist + thisTrackFreq);
    beginInsertRows({}, myGalaxy.count(), myGalaxy.count());
    GalaxyClass theGalaxy(thisCurrentTrackNumber, thistrackEngines, thisMaxSpeed, thisMinSpeed, thisLpFrequency, thisOrbitDist, thisTrackFreq);
    myGalaxy.append(theGalaxy);
    endInsertRows();
    emit sendGalaxyDataTableProgress();
}
/************************************************
 * @brief move Db.
 * moveDb
 ***********************************************/
bool MySqlDbtModel::moveDb(const QString &thisSourceFile,const QString &thisSourcePath, const QString &thisDestinationFolder)
{
    setMessage("moveDb");
    #ifdef USE_SQL_FLAG
    QFile file(QString("%1%2%3").arg(thisSourcePath, QDir::separator(), thisSourceFile));
    //
    QString theNewDatabaseName = QString("%1%2%3").arg(thisDestinationFolder, QDir::separator(), thisSourceFile);
    //
    if (mySetting->isFileExists(theNewDatabaseName))
    {
        if (!mySetting->questionYesNo("Overwrite Database", "Are you sure you want to overwrite existing Database?"))
        {
            return true;
        }
    }
    //
    if (myDb.isOpen()) { myDb.close(); }
    if (file.rename(theNewDatabaseName))
    {
        myDatabaseName = theNewDatabaseName;
        return createDataBaseConnection();
    }
    else { return true; }
    #else
    return true;
    #endif
}
/************************************************
 * @brief run Procces given exe path, argument, and if you want to wait and how long,
 *        in both cases this is a blocking call and will wait till finished and return value.
 * runProcces
 ***********************************************/
QString MySqlDbtModel::runProcces(const QString &thisExePath, const QString &thisArgument, bool isWait, int thisWaitTimeSec)
{
    QProcess *thisProcess = new QProcess(this);
    if (isWait)
    {
        thisProcess->start(thisExePath, QStringList() << thisArgument);
        // default wait time 30 sec
        if(!thisProcess->waitForStarted()) { qWarning() << tr("runProcces cannot start process"); }
        // wait time
        int waitTime = thisWaitTimeSec * 1000; // 60000 = 60 sec divide by 1000
        // now wait
        if (!thisProcess->waitForFinished(waitTime)) { qWarning() << tr("runProcces timeout .."); }
    }
    else
    {
        thisProcess->start(thisExePath, QStringList() << thisArgument);
        thisProcess->waitForFinished();
    }
    //
    thisProcess->setProcessChannelMode(QProcess::MergedChannels);
    myRunReturnCode = thisProcess->exitCode();
    return QString(thisProcess->readAllStandardOutput().simplified());
}
/************************************************
 * @brief get Run eturn Code.
 * getRunReturnCode
 ***********************************************/
int MySqlDbtModel::getRunReturnCode()
{
    return myRunReturnCode;
}
/************************************************
 * @brief set Project ID.
 * setProjectID
 ***********************************************/
void MySqlDbtModel::setProjectID(const QString &thisProjectID)
{
    setMessage("setProjectID");
    myProjectID = thisProjectID;
}
/************************************************
 * @brief get Project ID.
 * getProjectID
 ***********************************************/
QString MySqlDbtModel::getProjectID()
{
    setMessage("getProjectID");
    return myProjectID;
}
/************************************************
 * @brief set Project Name.
 * setProjectName
 ***********************************************/
void MySqlDbtModel::setProjectName(const QString &thisProjectName)
{
    setMessage("setProjectID");
    myProjectName = thisProjectName;
}
/************************************************
 * @brief get Project Name.
 * getProjectName
 ***********************************************/
QString MySqlDbtModel::getProjectName()
{
    setMessage("getProjectName");
    return myProjectName;
}
/************************************************
 * @brief set Message.
 * setMessage
 ***********************************************/
void MySqlDbtModel::setMessage(const QString &thisMessage) const
{
    if (isDebugMessage)
    {
        qDebug() << thisMessage;
        //std::cout << thisMessage.toStdString() << std::endl;
    }
}
/*** ************************* End of File ***********************************/
