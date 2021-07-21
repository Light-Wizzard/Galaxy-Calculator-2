#include "MainWindow.h"
#include "MainWindow.h"
/******************************************************************************
* \class MainWindow
*******************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Galaxy Settings
    myGalaxySettings = new GalaxySettings(this);
    // TrinaryMath
    myTrinaryMath = new TrinaryMath(this);
    // Create model:
    myGalaxyModel = new GalaxyDataTable(this);
    // App Icon
    QApplication::setWindowIcon(QIcon(":/images/logo32.png"));
    //
    ui->setupUi(this);
    // Validator Double Settings
    QDoubleValidator* validatorDouble = new QDoubleValidator(this);
    ui->lineEditSettingsSunSize->setValidator(validatorDouble);
    ui->lineEditSettingsPlanetSize->setValidator(validatorDouble);
    ui->lineEditSettingsGalaxyRadius->setValidator(validatorDouble);
    // Validator Int Settings
    QIntValidator* validatorInt = new QIntValidator(this);
    ui->lineEditSettingsTrinaryEngines->setValidator(validatorInt);
    ui->lineEditSettingsNthTrack->setValidator(validatorInt);
    // Validator Double Engery
    ui->lineEditEnergyEnergy->setValidator(validatorDouble);
    ui->lineEditEnergyCurrent->setValidator(validatorDouble);
    // Validator Double Engery
    ui->lineEditPlanetSize->setValidator(validatorDouble);
    ui->lineEditPlanetSidereal->setValidator(validatorDouble);
    ui->lineEditPlanetOrbitalDistance->setValidator(validatorDouble);
    ui->lineEditPlanetOrbitalPeriod->setValidator(validatorDouble);
    // Connect model to table view:
    ui->tableViewGalaxy->setModel(myGalaxyModel);
    // Make table header visible and display table:
    ui->tableViewGalaxy->horizontalHeader()->setVisible(true);
    ui->tableViewGalaxy->show();

    setWindowTitle(QApplication::applicationName());

    connect(ui->actionExit,         &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionCalculate,    &QAction::triggered, this, &MainWindow::onCalculateGalaxy);
    connect(ui->actionAbout,        &QAction::triggered, this, &MainWindow::onAbout);
    connect(ui->actionPrint,        &QAction::triggered, this, &MainWindow::onPrintGalaxyTableView);
    connect(ui->actionExportPdf,    &QAction::triggered, this, &MainWindow::onExportPdf);
    connect(ui->actionExportHTML,   &QAction::triggered, this, &MainWindow::onExportHtml);

    ui->progressBarGalaxy->hide();
    //
    connect(myGalaxyModel, &GalaxyDataTable::sendGalaxyDataTableProgress, this, &MainWindow::onProgress);
    connect(this, &MainWindow::sendInsertGalaxy, myGalaxyModel, &GalaxyDataTable::onInsertGalaxyRecord);
    //
    connect(this, &MainWindow::sendSettingComboBoxLastIndex, this, &MainWindow::onSetComboBoxSettings);
    connect(this, &MainWindow::sendPlanetComboBoxLastIndex, this, &MainWindow::onSetComboBoxPlanet);
    //
    UniverseModel = new QSqlRelationalTableModel(this);
    UniverseModel->setTable(myGalaxyModel->getSqlTableName());
    UniverseModel->select();

    ui->comboBoxSettingsGalaxy->setModelColumn(1);
    connect(ui->comboBoxSettingsGalaxy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onGalaxyChange);


    QTimer::singleShot(200, this, &MainWindow::onRunOnStartup);
}
/******************************************************************************
* \fn ~MainWindow
*******************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}
/******************************************************************************
* \fn onProgress
*******************************************************************************/
void MainWindow::onProgress()
{
    if (isDebugMessage) qDebug() << "onProgress";
    ui->progressBarGalaxy->setValue(++myCurrentProgress);
    if (!isGalaxyTableViewSize)
    {
        setGalaxyTableViewSize();
        isGalaxyTableViewSize = true;
    }
    QCoreApplication::processEvents();
}
/******************************************************************************
* \fn onRunOnStartup
*******************************************************************************/
void MainWindow::onRunOnStartup()
{
    //
    if (!checkDatabase()) close();
    setGalaxyTableViewSize();
    readSettings();
    //
    if (ui->checkBoxSettingsMemory->isChecked())
    {
        settingsButtons(false);
    }
    isMainLoaded = true;
}
/******************************************************************************
* closeEvent
*******************************************************************************/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isDebugMessage) qDebug() << "closeEvent";
    if (isSaveSettings) on_pushButtonSettingsSave_clicked();
    myGalaxySettings->setGeometry(pos(), size(), isMaximized(), isMinimized());
    QMainWindow::closeEvent(event);
    close();
} // end closeEvent
/******************************************************************************
* \fn getSymbolTable Does not get called FIXME
*******************************************************************************/
const SymbolTable &MainWindow::getSymbolTable()
{
    if (isDebugMessage) qDebug() << "getSymbolTable";
    return mySymbolTable;
}
/******************************************************************************
* \fn onSymbolTableChanged Does not get called FIXME
*******************************************************************************/
void MainWindow::onSymbolTableChanged(const SymbolTable &symbolTableArg)
{
    this->mySymbolTable = symbolTableArg;
    //symbolsEditor->setSymbols(symbolTable, settings.value(SETTING_KEY_SYMBOLS_FORMATTING_PRECISION, SETTING_DEFAULT_SYMBOLS_FORMATTING_PRECISION).toInt());
}
/******************************************************************************
* \fn doGalaxyTableViewPrint
*******************************************************************************/
void MainWindow::doGalaxyTableViewPrint(int docTypeHandler)
{
    if (isDebugMessage) qDebug() << "doGalaxyTableViewPrint";
    //
    if (!isTableLoaded) { onCalculateGalaxy(); }
    QString thisTitle = tr("Galaxy Calcultor");
    const int rowCount = myGalaxyModel->rowCount();
    const int columnCount = myGalaxyModel->columnCount();
    QString htmlOutput;
    htmlOutput.append("<!DOCTYPE html>\n<html lang='en'>\n");
    htmlOutput.append("<head>\n");
    //htmlOutput.append("<meta Content=\"Text/html; charset=Windows-1251\">\n");
    htmlOutput.append("<style> table { width:100%; } table, th, td { border: 1px solid black; border-collapse: collapse; } th, td { padding-bottom: 2px; padding-top: 2px; padding-right: 2px; text-align: right; } tr:nth-child(even) { background-color: #eeeeee; } tr:nth-child(odd) { background-color: white; } th { text-align: center; background-color: LightGray; color: black; } </style>");
    htmlOutput.append(QString("<title>%1</title>\n").arg(thisTitle));
    htmlOutput.append("</head>\n");
    htmlOutput.append("<body>\n");
    htmlOutput.append(QString("<h1 style='text-align: center;'>%1</h1>\n").arg(thisTitle));
    htmlOutput.append(QString("<h2 style='text-align: center;'>%1</h2>\n").arg(ui->lineEditSettingsGalaxyName->text()));
    htmlOutput.append(QString("<p style='text-align: center;'>Sun Diameter: %1 - Planet Diameter: %2</p>\n").arg(ui->lineEditSettingsSunSize->text(), ui->lineEditSettingsPlanetSize->text()));
    htmlOutput.append(QString("<p style='text-align: center;'>Trinary Engines: %1 - Galaxy Radius: %2 - Print Nth %3</p>\n").arg(ui->lineEditSettingsTrinaryEngines->text(), ui->lineEditSettingsGalaxyRadius->text(), ui->lineEditSettingsNthTrack->text()));
    htmlOutput.append("<table>\n");
    // headers
    htmlOutput.append("<thead>\n<tr>\n");
    for (int column = 0; column < columnCount; column++)
    {
        //if (!pPublic->tableViewGalaxy->isColumnHidden(column))
        htmlOutput.append(QString("<th>%1</th>\n").arg(myGalaxyModel->headerData(column, Qt::Horizontal).toString()));
    }
    htmlOutput.append("</tr></thead>\n");
    // data table
    for (int row = 0; row < rowCount; row++)
    {
        htmlOutput.append("<tr>\n");
        for (int column = 0; column < columnCount; column++)
        {
            //if (!GalaxyModel->isColumnHidden(column))
            //{
            QString data = myGalaxyModel->data(myGalaxyModel->index(row, column)).toString().simplified();
            htmlOutput.append(QString("<td>%1</td>\n").arg((!data.isEmpty()) ? data : QString("&nbsp;")));
            //}
        }
        htmlOutput.append("</tr>\n");
    }
    htmlOutput.append("</table>\n");
    htmlOutput.append("</body>\n");
    htmlOutput.append("</html>\n");

    //
    QTextDocument  *thisTableDocument = new QTextDocument();  //!< myTableDocument
    //thisTableDocument->setHtml(strStream);
    thisTableDocument->setHtml(htmlOutput);
    //
#ifndef QT_NO_PRINTER
    QPrinter thisPrinter;                                     //!< myPrinter
#endif
    //
    if (docTypeHandler == 1)
    {
#ifndef QT_NO_PRINTER
        QString fileName = QFileDialog::getSaveFileName(this, tr(" export PDF file "), QString("GalaxyCalculationTable.pdf"), "*.pdf");
        if (!fileName.isEmpty())
        {
            //  If the file suffix is empty, it is used by default .pdf
            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
            //  Specify the output format as pdf
            thisPrinter.setOutputFormat(QPrinter::PdfFormat);
            thisPrinter.setOutputFileName(fileName);
            thisTableDocument->print(&thisPrinter);
        }
#endif
    }
    else if (docTypeHandler == 2)
    {
#ifndef QT_NO_PRINTER
        QString fileName = QFileDialog::getSaveFileName(this, tr(" export HTML file "), QString("GalaxyCalculationTable.html"), "*.html");
        if (!fileName.isEmpty())
        {
            //  If the file suffix is empty, it is used by default .html
            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".html"); }
            // Output file
            QFile thisFile(fileName);
            // Open for write
            if (thisFile.open(QIODevice::WriteOnly))
            {
                QTextStream out(&thisFile);
                out << htmlOutput;
                thisFile.close();
            }
        }
#endif
    }
    else if(docTypeHandler == 3)
    {
#ifndef QT_NO_PRINTER

        QPrintDialog *dialog = new QPrintDialog(&thisPrinter, NULL);
        if (dialog->exec() == QDialog::Accepted)
        {
            thisTableDocument->print(&thisPrinter);
        }
#endif
    }
    delete thisTableDocument;

}
/******************************************************************************
* \fn onExportPdf
*******************************************************************************/
void MainWindow::onExportPdf()
{
    if (isDebugMessage) qDebug() << "onExportPdf";
    doGalaxyTableViewPrint(1);
}
/******************************************************************************
* \fn onExportHtml
*******************************************************************************/
void MainWindow::onExportHtml()
{
    if (isDebugMessage) qDebug() << "onExportHtml";
    doGalaxyTableViewPrint(2);
}
/******************************************************************************
* \fn onPrintGalaxyTableView
*******************************************************************************/
void MainWindow::onPrintGalaxyTableView()
{
    if (isDebugMessage) qDebug() << "onPrintGalaxyTableView";
    doGalaxyTableViewPrint(3);
}
/******************************************************************************
* \fn on_lineEditSettingsGalaxyName_textChanged
*******************************************************************************/
void MainWindow::on_lineEditSettingsGalaxyName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (isDebugMessage) qDebug() << "on_lineEditSettingsGalaxyName_textChanged";
    enableSaveButton();
}
/******************************************************************************
* \fn on_lineEditSettingsSunSize_textChanged
*******************************************************************************/
void MainWindow::on_lineEditSettingsSunSize_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (isDebugMessage) qDebug() << "on_lineEditSettingsSunSize_textChanged";
    enableSaveButton();
}
/******************************************************************************
* \fn on_lineEditSettingsPlanetSize_textChanged
*******************************************************************************/
void MainWindow::on_lineEditSettingsPlanetSize_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (isDebugMessage) qDebug() << "on_lineEditSettingsPlanetSize_textChanged";
    enableSaveButton();
}
/******************************************************************************
* \fn on_lineEditSettingsTrinaryEngines_textChanged
*******************************************************************************/
void MainWindow::on_lineEditSettingsTrinaryEngines_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (isDebugMessage) qDebug() << "on_lineEditSettingsTrinaryEngines_textChanged";
    enableSaveButton();
}
/******************************************************************************
* \fn on_lineEditSettingsGalaxyRadius_textChanged
*******************************************************************************/
void MainWindow::on_lineEditSettingsGalaxyRadius_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (isDebugMessage) qDebug() << "on_lineEditSettingsGalaxyRadius_textChanged";
    enableSaveButton();
}
/******************************************************************************
* \fn on_lineEditSettingsNthTrack_textChanged
*******************************************************************************/
void MainWindow::on_lineEditSettingsNthTrack_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (isDebugMessage) qDebug() << "on_lineEditSettingsNthTrack_textChanged";
    enableSaveButton();
}
/******************************************************************************
* \fn enableSaveButton
*******************************************************************************/
void MainWindow::enableSaveButton()
{
    if (isDebugMessage) qDebug() << "enableSaveButton";
    if (!isDbMemory)
    {
        isSaveSettings = true;
        ui->pushButtonSettingsSave->setEnabled(true);
    }
}
/******************************************************************************
* \fn setTableViewSize
*******************************************************************************/
void MainWindow::setGalaxyTableViewSize()
{
    if (isDebugMessage) qDebug() << "setTableViewSize";
    // 0             1              2          3          4            5           6
    // Track Number, Track Engines, Max Speed, Min Speed, LpFrequency, Orbit Dist, Track Freq;
    ui->tableViewGalaxy->setColumnWidth(0, 80);  //!< Track
    ui->tableViewGalaxy->setColumnWidth(1, 166); //!< Trinary Engines
    ui->tableViewGalaxy->setColumnWidth(2, 120); //!< Max
    ui->tableViewGalaxy->setColumnWidth(3, 120); //!< Min
    ui->tableViewGalaxy->setColumnWidth(4, 142); //!< Frequency
    ui->tableViewGalaxy->setColumnWidth(5, 286); //!< Distance
    ui->tableViewGalaxy->setColumnWidth(6, 160); //!< Track Frequency
    //setData(index,Qt::AlignCenter,Qt::TextAlignmentRole);
}
/******************************************************************************
* \fn settingsButtons
*******************************************************************************/
void MainWindow::settingsButtons(bool thisEnabled)
{
    if (isDebugMessage) qDebug() << "settingsButtons";
    ui->pushButtonSettingsAdd->setEnabled(thisEnabled);
    ui->pushButtonSettingsClear->setEnabled(thisEnabled);
    ui->pushButtonSettingsSave->setEnabled(thisEnabled);
    ui->pushButtonSettingsDefalut->setEnabled(thisEnabled);
    ui->pushButtonSettingsDelete->setEnabled(thisEnabled);
}
/******************************************************************************
* \fn readSettings
*******************************************************************************/
bool MainWindow::readSettings()
{
    if (isDebugMessage) qDebug() << "readSettings";

    if (myGalaxySettings->readSettingsBool(myDbMemory, true)) // true false
        ui->checkBoxSettingsMemory->setChecked(true);
    else
        ui->checkBoxSettingsMemory->setChecked(false);

    //resize(myGalaxySettings->getGeometrySize());

    //move(myGalaxySettings->getGeometryPos());

    //
    //if(myGalaxySettings->getGeometryMax()) setWindowState(windowState() | Qt::WindowMaximized);
    //if(myGalaxySettings->getGeometryMin()) setWindowState(windowState() | Qt::WindowMinimized);

    //
    ui->spinBoxCalcDecimals->setValue(myGalaxySettings->readSettingsInt(myCalcDecimal, 16));

    return true;
}
/******************************************************************************
* \fn writeSettingsCalcDecimal
*******************************************************************************/
bool MainWindow::writeSettingsCalcDecimal()
{
    if (isDebugMessage) qDebug() << "writeSettingsCalcDecimal";
    myGalaxySettings->writeSettings(myCalcDecimal, ui->spinBoxCalcDecimals->text()); // Number of Decimal Places in Calculator
    return true;
}
/******************************************************************************
* \fn writeSettingsDbMemory
*******************************************************************************/
bool MainWindow::writeSettingsDbMemory(const QString thisDbMemory)
{
    if (isDebugMessage) qDebug() << "writeSettings";
    myGalaxySettings->writeSettings(myDbMemory, thisDbMemory); // true false
    return true;
}
/******************************************************************************
* \fn on_checkBoxSettingsMemory_stateChanged
*******************************************************************************/
void MainWindow::on_checkBoxSettingsMemory_stateChanged(int arg1)
{
    if (isDebugMessage) qDebug() << "on_checkBoxSettingsMemory_stateChanged";
    if (arg1 == Qt::Checked)
    {
        settingsButtons(false); // Enabled = False
        writeSettingsDbMemory("true");  // DbMemory = true
        isDbMemory=true;
    }
    else
    {
        settingsButtons(true);   // Enabled = true
        writeSettingsDbMemory("false");  // DbMemory = False
        isDbMemory=false;
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Database Driver for Sqlite is set", "You must restart Application for change to take effect, Quit?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            qDebug() << "Yes was clicked";
            QApplication::quit();
        }
        else
        {
            qDebug() << "Yes was *not* clicked";
        }
    }
}
/******************************************************************************
* \fn on_spinBoxCalcDecimals_textChanged
*******************************************************************************/
void MainWindow::on_spinBoxCalcDecimals_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    writeSettingsCalcDecimal();
}
/******************************************************************************
* \fn onCalculateGalaxy
*******************************************************************************/
void MainWindow::onCalculateGalaxy()
{
    if (isDebugMessage) qDebug() << "onCalculateGalaxy";
    myCurrentProgress = 0;
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabWidget->findChild<QWidget*>("tabGalaxy")));
    // Read in configuration
    // Our Galaxy = Milkey Way
    //const QString thisGalaxy            = ui->lineEditGalaxyName->text();
    // in Miles in Diameter
    // Sun=864575.9
    // in Miles in Diameter
    const QString thisSunSize           = ui->lineEditSettingsSunSize->text();
    // Earth = 7926.2109;
    const QString thisLivalbePlanetSize = ui->lineEditSettingsPlanetSize->text();
    // This number is negative, Taken from Configuraton
    // Our Solar System as 333, so to test this system set this to Negative;
    QString thisTrinaryEngines          = ui->lineEditSettingsTrinaryEngines->text();
    // in Miles in Diameter, Taken from Configuraton
    // Milkey Way = 241828072282107.5071453596951;
    const QString thisGalaxyRadius      = ui->lineEditSettingsGalaxyRadius->text();
    int thisPrintNthTrack               = ui->lineEditSettingsNthTrack->text().toInt();
    //
    ui->progressBarGalaxy->show();
    ui->progressBarGalaxy->setMinimum(0);
    ui->progressBarGalaxy->setMaximum(thisPrintNthTrack / 3);

    myGalaxyModel->clearRecords();
    // Disconnect before Connect model to table view:
    ui->tableViewGalaxy->setModel(NULL);
    ui->tableViewGalaxy->setModel(myGalaxyModel);
    ui->tableViewGalaxy->setAlternatingRowColors(true);
    // Set Tab
    ui->tabWidget->setCurrentIndex(1);
    // 1 / 137.03599913 is not more accurate
    // 1/137;
    // 0.0072992700729
    // 0.0072992700729928
    // 0.007299270072992803
    // 0.00729927007299270073
    // 0.0072992700730
    QString thisTrinaryMarker = doMath("1 / 137", 13);
    /**********************************************************************
     * 42          3.141592653589793238462643383279502884197169
     * 100         3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
     * 355 / 113 = 3.14159292035398230088495575221238938053263786810735899116172564465
     * 333 / 106 = 3.14150943396226415094339622641509433962752091994680949531609664223
     * 22  / 7   = 3.1428571428571428571428571428571428571411778652131110178457589478
     **********************************************************************/
    QString thisPie = myTrinaryMath->getPI(); //  "3.14159265359";
    // PI: based on this version, to use a higher or lower Precession would require recalculate of baseline.
    // do not use Math.PI=3.141592653589793
    // this uses 11 bits which is what Newton used, the above uses 15
    // Constant Precession Rate: Constant in Newtons work.
    QString thisCpRate = "324.540503";
    // Newtons Constant for Earths Atmospheric Density based on Torr
    // I Calculated from Trinary Engines to make it generic to all Planets
    QString thisLpDensity = "73.120284";
    // Atmospheric Pressure Index acts as a Dampener for the Core Frequency causing it to expand at a known Rate based on its Size.
    // Livable Planet Ring Frequency: aP is based on Planet Earth, I do not make this an Arguments because I have no way of getting this data
    // Torr is a unit of pressure based on an absolute scale defined as 1/760
    // Newtons Constant for Earths Atmospheric Density based on Torr
    // Note: Torr came from the Torah AKA Bible
    // var aP = ( lpDensity * (1/760) );
    // 0.00131578947368421053
    // 0.001315789
    // 55571.4358457169044580856
    // 55571.435845717
    QString thisTorr = doMath("1 / 760", 9);
    QString thisAP = doMath(QString("%1 * %2").arg(thisLpDensity, thisTorr), 9);
    // aP=( lpDensity * (1/760) )=73.120284 * 0.001315789 = 0.096210865
    // Planets Trinary Engine Rings: First=.0001, Second=0.001, Third=.01
    QString thisRingPlanetSecond = "0.001";
    // Now Calculate based on Defaults from configuration
    // Liveable Planet Ring Frequency: 7926.2109 * .001 = 7.9262109 - aP = 7.830 Hz
    // 7.9262109
    // 7.926
    myLivePlanetRingFreq = doMath(QString("(%1 * %2) - %3").arg(thisLivalbePlanetSize, thisRingPlanetSecond, thisAP), 3);
    // 7926.2109 * 0.001 - 55571.435845717 = -55563.510
    // Used to iterate
    int thisCurrentNth = 0;
    // Used to iterate
    int thisPrintThis = 1;
    // Number of Printed lines
    int thisPrintedLines = 0;
    // Used for Track Engine Counter
    int thisTrackEngines = 0;
    // Precession Rate: Sun: 10,656 / 4 = 2664
    // var pRate = ( thisSunSize / cpRate );
    int thisPrecessionRate = doMath(QString("%1 / %2").arg(thisSunSize, thisCpRate), 0).toInt();
    // 2664
    // Precession: you must remove the speed required to over come it.
    int thisMaxErrorRate = thisPrecessionRate;
    int trinaryEngines = doMath(QString("%1 * %2").arg(thisTrinaryEngines, "-1"), 0).toInt();
    // To print Life Track: based on Trinary Engines
    // Tracks are based on how many Trinary Engines the Solar System has
    // Do Not Skip This Track
    int thisDoNotSkipThisTrack = doMath(QString("%1 * %2").arg(thisTrinaryEngines, "2"), 0).toInt();
    // I adjusted the date as to not need this, but its still required
    // I adjusted so each track accumalates 1 unit more of this quantity
    // The Minimum Error Rate is an Accoumalation of Errors incounterd on each track
    // As such this is just a counter of errors minimized
    // This is a Calculus Error handler, so I have a Max and Min Operator
    int thisMinErrorRate = 0;
    // Iteration Ranges
    // maxIteration: The longest an Iteration can be
    // (Diameter in miles) x 1/137 / (3 Phase) = Max Iteration in years
    //var maxIteration = (( thisSunSize * trinaryMarker ) / 3 );
    QString thisSunMarker = doMath(QString("%1 * %2").arg(thisSunSize, thisTrinaryMarker), 0);
    QString thisMaxIteration = doMath(QString("%1 / %2").arg(thisSunMarker, "3"), 16);
    //maxIteration = qFloor(maxIteration.toDouble());
    // 2103
    // aveIteration: Based on Suns Magnetic Polarity Reversals
    // Sun changes polarity 10 (0 - 9) times a Century: 100 - 9 = 91
    // var aveIteration = ( maxIteration - 91 );
    QString thisAveIteration = doMath(QString("%1 - %2").arg(thisMaxIteration, "91"), 0);
    // 2012
    // minIteration: Based on Max Min of Magnetic Fields
    // I hard coded date so I did not need Error Rate: Adds down to 6
    // Note this Number 1104 was determined from long running results done by Newton
    // This number is also found in the Torah
    // var minIteration = ( maxIteration - 1104 )
    QString thisMinIteration = doMath(QString("%1 - %2").arg(thisMaxIteration, "1104"), 0);
    // 999
    // maxSpeed: As it begins decent into Galactic Plane
    QString thisMaxSpeed = "0.0";
    // minSpeed: At its Maximum Amplitude
    QString thisMinSpeed = "0.0";
    // Note that there are two ways to get this value; below and using the Livable Planets Properties
    // Earth for example: Orbital distance in Miles around Sun = 584,000,000 / (365 Days * 24 Hours) = 66,666.666 MPH * .0001 = 6.6666666 Hz
    // So this is a Double Verification Process; proving that this Math actually works both ways which is Magic proving God Designed this.
    // Frequency: maxSpeed * ringSunFirst = Frequency of Livable Planet
    QString thisLpFrequency = "0.0";
    // This is based on the First Ring of the Sun
    // Sun: First=0.00001, Second=0.0001, Third=.001: One Magnitude different then Planets
    QString thisRingSunFirst = "0.00001";
    // Orbital Distance in Miles around the Track.
    QString thisOrbitDist = "0";
    // Track Frequency Multiplier based on Galaxy Ring of Power; 13 is Masonic Number in Bible
    QString thisTrackFreqMultiplier = "0.0000000000001"; // JavaScript=1e-13
    // Track Frequency: .0000000000001 * |minSpeed|
    QString thisTrackFreq = "0.0";
    // Track Number
    // Total number of Tracks: twice trinaryEngines ~ 666 * 2 + 1 since its 0 based: 1333
    int thisTotalTracks = 0;
    // Counter for loop
    int thisCurrentTrackNumber = 0;
    // Calculate or set all varibles
    thisTrackEngines = trinaryEngines;
    // Calculate Total Tracks: absolute value * 2, then * 2, then add 1
    // Note: I do not reply on Order of Precedence in Math
    // () forces the calculation
    // People that try to Optimize Math forget what they are doing
    // I do not want to be Cleaver I want to be Clear
    thisTotalTracks =  doMath(QString("(((%1 * 2) * 2) + 1 )").arg(thisTrinaryEngines), 0).toInt();
    QString thisMaxSpeedNoError;
    QString thisMinSpeedNoError;
    isTableLoaded = false;
    // for loop
    for ( thisCurrentTrackNumber = 0; thisCurrentTrackNumber < thisTotalTracks; thisCurrentTrackNumber++ )
    {
        // Orbital Distance
        // ((241828072282107.5071453596951 * 666) * 2) * 3.14159265359
        // echo "$(bc <<< "scale=13;((241828072282107.5071453596951 * 666) * 2) * 3.14159265359")"
        // 1011954093357316199.999999999911810770784788
        // orbitDist = ((( Number.parseFloat(thisGalaxyRadius).toPrecision(20) * currentTrackNumber) * 2) * Number.parseFloat(pIe).toPrecision(12) );
        QString orbitRadius = doMath(QString("%1 * %2").arg(thisGalaxyRadius, QString::number(thisCurrentTrackNumber)), 13);
        thisOrbitDist = doMath(QString("%1 * 2").arg(orbitRadius), 13);
        // JavaScript off by 100 Miles, C++ off by 103 miles, use boost
        // orbitDist = ((( thisGalaxyRadius * currentTrackNumber) * 2) * pIe );
        // maxSpeed
        if ( thisTrackEngines <= 0 )
        {
            thisMaxSpeedNoError = doMath(QString("%1 * %2").arg(thisAveIteration, QString::number(thisTrackEngines)), 42);
            thisMaxSpeed = doMath(QString("%1 + %2").arg(thisMaxSpeedNoError, QString::number(thisMaxErrorRate)), 0);
        }
        else
        {
            // aveIteration * trackEngines - maxErrorRate
            thisMaxSpeedNoError = doMath(QString("%1 * %2").arg(thisAveIteration, QString::number(thisTrackEngines)), 42);
            thisMaxSpeed = doMath(QString("%1 - %2").arg(thisMaxSpeedNoError, QString::number(thisMaxErrorRate)), 0);
        }
        // minSpeed
        if ( thisTrackEngines <= 0 )
        {
            thisMinSpeedNoError = doMath(QString("%1 * %2").arg(thisMinIteration, QString::number(thisTrackEngines)), 42);
            thisMinSpeed = doMath(QString("%1 - %2").arg(thisMinSpeedNoError, QString::number(thisMinErrorRate)), 13);
        }
        else
        {
            thisMinSpeedNoError = doMath(QString("%1 * %2").arg(thisMinIteration, QString::number(thisTrackEngines)), 42);
            thisMinSpeed = doMath(QString("%1 + %2").arg(thisMinSpeedNoError, QString::number(thisMinErrorRate)), 0);
        }
        // lpFrequency
        thisLpFrequency = doMath(QString("%1 * %2").arg(thisMaxSpeed, thisRingSunFirst), 4);
        //lpFrequency = lpFrequency.substring(0, lpFrequency.length - 1);
        // lpFrequency = ( maxSpeed * ringSunFirst );
        // trackFreq
        thisTrackFreq = doMath(QString("%1 * %2").arg(thisTrackFreqMultiplier, myTrinaryMath->absValue(thisMinSpeed)), 16);
        // These Calculations are meaningless
        if ( thisTrackEngines == trinaryEngines || thisTrackEngines == 0 || thisTrackEngines == 1 || thisTrackEngines == -1)
        {
            thisTrackFreq = "0";
        }
        // Now do the Math
        if ( thisTrackFreq != "0" )
        {
            thisTrackFreq = doMath(QString("%1 / %2").arg("1", thisTrackFreq), 16);
        }
        //
        thisCurrentNth++;
        if ( thisPrintNthTrack == thisCurrentNth )
        {
            thisCurrentNth = 0;
            thisPrintThis = 1;
        }
        else
        {
            thisPrintThis = 0;
        }
        // always show 666 or Life Track
        if ( thisDoNotSkipThisTrack == thisCurrentTrackNumber )
        {
            thisPrintThis = 1;
        }
        //
        if ( thisPrintThis == 1 )
        {
            // 666 | 333 | 666,666 | 333,333 | 6.66666 | 1,011,954,093,357,316,200 | 30,000,030
            // 666 | 666 |
            thisOrbitDist = myTrinaryMath->formatNumber(doMath(QString("%1 * %2").arg(thisOrbitDist, thisPie), 13), 0);
            thisTrackFreq = myTrinaryMath->formatNumber(thisTrackFreq, 0);
            thisMaxSpeed  = myTrinaryMath->formatNumber(thisMaxSpeed, 0);
            thisMinSpeed  = myTrinaryMath->formatNumber(thisMinSpeed, 0);
            // Save to Database
            emit sendInsertGalaxy(QString::number(thisCurrentTrackNumber), QString::number(thisTrackEngines), thisMaxSpeed, thisMinSpeed, thisLpFrequency, thisOrbitDist, thisTrackFreq);
            // Increament printed linies
            thisPrintedLines++;
        } // end if ( printThis == 1 )
        // Increment Variables
        thisTrackEngines++;
        thisMaxErrorRate++;
        thisMinErrorRate++;
        QCoreApplication::processEvents();
    } // end for currentTrackNumber < totalTracks
    qDebug() << "Finished";
    isTableLoaded = true;
    ui->progressBarGalaxy->hide();
    setGalaxyTableViewSize();
}
/******************************************************************************
* \fn getLivePlanetRingFreq
*******************************************************************************/
QString MainWindow::getLivePlanetRingFreq()
{
    return myLivePlanetRingFreq;
}
/******************************************************************************
* \fn on_pushButtonCalcEnter_clicked Enter
*******************************************************************************/
void MainWindow::on_pushButtonCalcEnter_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonCalcEnter_clicked";
    ui->lineEditCalcValue->setText(doMath(ui->lineEditCalcValue->text(), ui->spinBoxCalcDecimals->value()));
}
/******************************************************************************
* \fn setSqlDatabase
*******************************************************************************/
void MainWindow::setSqlDatabase(QSqlDatabase thisDatabase)
{
    if (isDebugMessage) qDebug() << "setSqlDatabase";
    myDb = thisDatabase;
}
/******************************************************************************
* \fn getSqlDatabase
*******************************************************************************/
QSqlDatabase MainWindow::getSqlDatabase()
{
    if (isDebugMessage) qDebug() << "getSqlDatabase";
    return myDb;
}
/******************************************************************************
* \fn checkDatabase
*******************************************************************************/
bool MainWindow::checkDatabase()
{
    if (isDebugMessage) { qDebug() << "checkDatabase"; }
    // Database
    if (myGalaxyModel->createDataBaseConnection())
    {
        myDb = myGalaxyModel->getSqlDatabase();
    }
    else
    {
        return false;
    }
    //
    // Galaxy Table
    if (!myGalaxyModel->isDbTable("galaxy", &myDb))
    {
        //
        if (!runQuery(QLatin1String(R"(CREATE TABLE galaxy(id integer PRIMARY KEY autoincrement, GalaxyName varchar, SunSize varchar, PlanetSize varchar, TrinaryEngines varchar, GalaxyRadius varchar, Nthtrack varchar))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  CREATE TABLE galaxy error:";
        }
        //
        const auto DEFAULT_GALAXY_SQL = QLatin1String(R"(INSERT INTO galaxy (GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack) values('Milky Way', '864575.9', '7926.2109', '333', '241828072282107.5071453596951', '66'))");
        if (!runQuery(DEFAULT_GALAXY_SQL))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT galaxy error:";
        }
    }
    setSettingsCombo();
    // Planet
    //
    if (!myGalaxyModel->isDbTable("planets", &myDb))
    {
        //
        if (!runQuery(QLatin1String(R"(CREATE TABLE planets(id integer PRIMARY KEY autoincrement, PlanetName varchar, Diameter varchar, Sidereal varchar, OrbitalDistance varchar, OrbitalPeriod varchar))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  CREATE TABLE galaxy error:";
        }
        //
        if (!insertPlanet("Sun", "864575.9", "25.379995", "1011954093357316200", "242000000"))
        {
            qDebug() << "Error INSERT Sun planets:";
        }
        if (!insertPlanet("Mercury", "3031.9186", "58.646225", "223700000", "87.97"))
        {
            qDebug() << "Error INSERT Mercury planets:";
        }
        if (!insertPlanet("Venus", "7521.0769", "243.0187", "422500000", "224.7"))
        {
            qDebug() << "Error INSERT Venus planets:";
        }
        if (!insertPlanet("Earth", "7926.2109", "0.99726968", "584000000", "365"))
        {
            qDebug() << "Error INSERT Earth planets:";
        }
        if (!insertPlanet("Moon", "2159", "27.321661", "1499070", "27.323"))
        {
            qDebug() << "Error INSERT Moon planets:";
        }
        if (!insertPlanet("Mars", "4217.246", "1.02595675", "888000000", "686.98"))
        {
            qDebug() << "Error INSERT Mars planets:";
        }
        if (!insertPlanet("Jupiter", "88731.8063", "0.41007", "3037000000", "4330.6"))
        {
            qDebug() << "Error INSERT Jupiter planets:";
        }
        if (!insertPlanet("Saturn", "74974.6481", "0.426", "5565900000", "10755.7"))
        {
            qDebug() << "Error INSERT Saturn planets:";
        }
        if (!insertPlanet("Uranus", "31763.253", "0.71833", "11201300000", "30685"))
        {
            qDebug() << "Error INSERT Uranus planets:";
        }
        if (!insertPlanet("Neptune", "30775.272", "0.67125", "17562300000", "60190"))
        {
            qDebug() << "Error INSERT Neptune planets:";
        }
    }
    setPlanetCombo();
    // Math Constant Table
    if (!myGalaxyModel->isDbTable("math", &myDb))
    {
        //
        if (!runQuery(QLatin1String(R"(CREATE TABLE math(id integer PRIMARY KEY autoincrement, Name varchar, Constant varchar))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  CREATE TABLE math error:";
        }
        // Constants
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Constants', ''))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // e, Napier's constant, or Euler's number
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('e', '2.71828182845904523536028747135266249'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Pythagoras' constant, square root of 2 √2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Pythagoras', '1.41421356237309504880168872420969807'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Theodorus' constant, square root of 3 √3
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Theodorus', '1.73205080756887729352744634150587236'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // square root of 5 √2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('SqrRoot5', '2.23606797749978969640917366873127623'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Euler–Mascheroni constant \gamma
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Euler–Mascheroni', '0.57721566490153286060651209008240243')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Golden ratio \varphi
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Golden-Ratio', '1.61803398874989484820458683436563811'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Meissel–Mertens constant M1
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Meissel–Mertens', '0.26149721284764278375542683860869585')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Bernstein's constant \beta
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Bernstein', '0.28016949902386913303'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Gauss–Kuzmin–Wirsing constant \lambda
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Gauss–Kuzmin–Wirsing', '0.30366300289873265859744812190155623')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Hafner–Sarnak–McCurley constant \sigma
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Hafner–Sarnak–McCurley', '0.35323637185499598454351655043268201')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Landau's constant L
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Landau', '0.5'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Omega constant Ω
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Omega', '0.56714329040978387299996866221035554'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Golomb–Dickman constant \lambda , μ {\displaystyle \mu } \mu
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Golomb–Dickman', '0.62432998854355087099293638310083724')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Cahen's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Cahen', '0.66016181584686957392781211001455577'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Twin prime constant C2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Twin-Prime', '0.66016181584686957392781211001455577'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Laplace limit
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Laplace', '0.66274341934918158097474209710925290'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Embree–Trefethen constant
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Embree–Trefethen', '0.70258')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Landau–Ramanujan constant K
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Landau–Ramanujan', '0.76422365358922066299069873125009232')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Brun's constant for prime quadruplets B4
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Brun-Prime-Quadruplets', '0.87058838'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Catalan's constant K
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Catalan', '0.91596559417721901505460351493238411'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Viswanath's constant K
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Viswanath', '1.13198824'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Apéry's constant \zeta (3)
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Apery', '1.20205690315959428539973816151144999'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Conway's constant \lambda
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Conway', '1.30357726903429639125709911215255189'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Mills' constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Mills', '1.30637788386308069046861449260260571'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Plastic constant p
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Plastic', '1.32471795724474602596090885447809734'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Ramanujan–Soldner constant \mu
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Ramanujan-Soldner', '1.45136923488338105028396848589202744'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Backhouse's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Backhouse', '1.45607494858268967139959535111654356'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Porter's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Porter', '1.4670780794'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Lieb's square ice constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Lieb-Square-Ice', '1.5396007178'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Erdős–Borwein constant EB
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Erdos–Borwein', '1.60669515241529176378330152319092458')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Niven's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Niven', '1.70521114010536776428855145343450816'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Brun's constant for twin primes B2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Brun-Twin-Primes', '1.902160583104'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Universal parabolic constant P2
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Universal-Parabolic', '2.29558714939263807403429804918949039'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Feigenbaum constant \alpha
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Feigenbaum', '2.50290787509589282228390287321821578'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Sierpiński's constant K
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Sierpinski', '2.58498175957925321706589358738317116'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Khinchin's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Khinchin', '2.68545200106530644530971483548179569'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Fransén–Robinson constant F
        if (!runQuery(QString("INSERT INTO math (Name, Constant) values('Fransen–Robinson', '2.80777024202851936522150118655777293')")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Lévy's constant
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Levy', '3.27582291872181115978768188245384386'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Reciprocal Fibonacci constant \psi
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Reciprocal-Fibonacci', '3.35988566624317755317201130291892717'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
        // Feigenbaum constant \delta
        if (!runQuery(QLatin1String(R"(INSERT INTO math (Name, Constant) values('Feigenbaum', '4.66920160910299067185320382046620161'))")))
        {
            qDebug() << myGalaxyModel->getSqlDriver() <<  "  INSERT math error:";
        }
    } // end if (!myGalaxyModel->isDbTable("math", &myDb))
    //
    setCalcConstantCombo();
    return true;
}
/******************************************************************************
* \fn runQuery
*******************************************************************************/
bool MainWindow::runQuery(const QString thisQuery)
{
    if (isDebugMessage) { qDebug() << "runQuery"; }
    QSqlQuery query; //!< SQL Query
    if (!query.exec(thisQuery))
    {
        qDebug() << "Error running Query: " << thisQuery << query.lastError().text() << ", SqLite error code:" << query.lastError();
        return false;
    }
    return true;
}
/******************************************************************************
* \fn runQuery
*******************************************************************************/
bool MainWindow::insertPlanet(const QString thisPlanetName, const QString thisDiameter, const QString thisSidereal, const QString thisOrbitalDistance, const QString thisOrbitalPeriod)
{
    if (isDebugMessage) { qDebug() << "insertPlanet"; }
    QString myQuery = QString("INSERT INTO planets (PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod) values('%1', '%2', '%3', '%4', '%5')").arg(thisPlanetName, thisDiameter, thisSidereal, thisOrbitalDistance, thisOrbitalPeriod);
    if (isDebugMessage) { qDebug() << "insertPlanet: " << myQuery; }

//    if (!runQuery(QLatin1String(R"(INSERT INTO planets (PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod) values('%1', '%2', '%3', '%4', '%5'))").arg(thisPlanetName, thisDiameter, thisSidereal, thisOrbitalDistance, thisOrbitalPeriod)))
    if (!runQuery(myQuery))
    {
        qDebug() << "INSERT planets error: " << myQuery;
        return false;
    }
    return true;
}
/******************************************************************************
* \fn setCalcConstantCombo
*******************************************************************************/
bool MainWindow::setCalcConstantCombo()
{
    QSqlQueryModel *modalGalaxy = new QSqlQueryModel; //!< SQL Query Model
    //
    const auto SELECTED_PLANET_SQL = QLatin1String(R"(SELECT id, Name, Constant FROM math)");
    modalGalaxy->setQuery(SELECTED_PLANET_SQL);
    if (modalGalaxy->lastError().isValid())
    {
        qDebug() << modalGalaxy->lastError();
    }
    modalGalaxy->setHeaderData(0,Qt::Horizontal, tr("ID"));
    modalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Name"));
    modalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Constant"));
    QTableView *view = new QTableView;
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->comboBoxCalcConstants->setModel(nullptr);
    ui->comboBoxCalcConstants->setModel(modalGalaxy);
    ui->comboBoxCalcConstants->setView(view);
    view->setColumnHidden(0, true);
    ui->comboBoxCalcConstants->setModelColumn(1);
    ui->comboBoxCalcConstants->setCurrentIndex(0);
    //view->setColumnWidth(1, 266);
    //view->setColumnWidth(2, 366);
    view->resizeColumnsToContents();
    return true;
}
/******************************************************************************
* \fn setPlanetCombo
*******************************************************************************/
bool MainWindow::setPlanetCombo()
{
    QSqlQueryModel *modalGalaxy = new QSqlQueryModel; //!< SQL Query Model
    //
    const auto SELECTED_PLANET_SQL = QLatin1String(R"(SELECT id, PlanetName FROM planets)");
    modalGalaxy->setQuery(SELECTED_PLANET_SQL);
    if (modalGalaxy->lastError().isValid())
    {
        qDebug() << modalGalaxy->lastError();
    }
    modalGalaxy->setHeaderData(0,Qt::Horizontal, tr("ID"));
    modalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Name"));
    QTableView *view = new QTableView;
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->comboBoxPlanet->setModel(nullptr);
    ui->comboBoxPlanet->setModel(modalGalaxy);
    ui->comboBoxPlanet->setView(view);
    view->setColumnHidden(0, true);
    ui->comboBoxPlanet->setModelColumn(1);
    ui->comboBoxPlanet->setCurrentIndex(0);
    view->setColumnWidth(1, 166);
    return true;
}
/******************************************************************************
* \fn setSettingsCombo
*******************************************************************************/
bool MainWindow::setSettingsCombo()
{
    QSqlQueryModel *modalGalaxy = new QSqlQueryModel; //!< SQL Query Model
    //
    const auto SELECTED_GALAXY_SQL = QLatin1String(R"(SELECT id, GalaxyName FROM galaxy)");
    modalGalaxy->setQuery(SELECTED_GALAXY_SQL);
    if (modalGalaxy->lastError().isValid())
    {
        qDebug() << modalGalaxy->lastError();
    }
    modalGalaxy->setHeaderData(0, Qt::Horizontal, tr("ID"));
    modalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Name"));
    QTableView *view = new QTableView;
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->comboBoxSettingsGalaxy->setModel(nullptr);
    ui->comboBoxSettingsGalaxy->setModel(modalGalaxy);
    ui->comboBoxSettingsGalaxy->setView(view);
    view->setColumnHidden(0, true);
    ui->comboBoxSettingsGalaxy->setModelColumn(1);
    ui->comboBoxSettingsGalaxy->setCurrentIndex(0);
    view->setColumnWidth(1, 166);
    return true;
}
/******************************************************************************
* \fn getGalaxyIdSelectQuery
*******************************************************************************/
QString MainWindow::getGalaxyIdSelectQuery(const QString thisWhereId)
{
    if (isDebugMessage) qDebug() << "getGalaxyIdSelectQuery";
    return QString("SELECT GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack FROM galaxy WHERE id = ").append(thisWhereId);
}
/******************************************************************************
* \fn getGalaxyNameSelectQuery
*******************************************************************************/
QString MainWindow::getGalaxyNameSelectQuery(const QString thisWhereName)
{
    if (isDebugMessage) qDebug() << "getGalaxyNameSelectQuery";
    return QString("SELECT GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack FROM galaxy WHERE GalaxyName = '").append(thisWhereName).append("'");
}
/******************************************************************************
* \fn getPlanetSelectQuery
*******************************************************************************/
QString MainWindow::getPlanetSelectQuery(const QString thisWhereId)
{
    if (isDebugMessage) qDebug() << "getPlanetSelectQuery";
    return QString("SELECT id, PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod FROM planets WHERE id = ").append(thisWhereId);
}
/******************************************************************************
* \fn getPlanetNameSelectQuery
*******************************************************************************/
QString MainWindow::getPlanetNameSelectQuery(const QString thisWhereName)
{
    if (isDebugMessage) qDebug() << "getPlanetNameSelectQuery";
    return QString("SELECT id, PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod FROM planets WHERE PlanetName = '").append(thisWhereName).append("'");;
}
/******************************************************************************
* \fn on_comboBoxPlanet_currentIndexChanged Energy Current
* Planet Combobox Changed
*******************************************************************************/
void MainWindow::on_comboBoxPlanet_currentIndexChanged(int index)
{
    if (isDebugMessage) qDebug() << "on_comboBoxPlanet_currentIndexChanged";
    calcPlanet(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(index, 0)).toString());
}
/******************************************************************************
* \fn on_pushButtonPlanetCalculate_clicked Planet Calculate
*******************************************************************************/
void MainWindow::on_pushButtonPlanetCalculate_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonPlanetCalculate_clicked";
    calcPlanet(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(ui->comboBoxPlanet->currentIndex(), 0)).toString());
}
/******************************************************************************
* \fn onGalaxyChange
*******************************************************************************/
void MainWindow::onGalaxyChange()
{
    if (isDebugMessage) qDebug() << "onGalaxyChange";
    QSqlQuery query; //!< SQL Query
    QString myGalaxySelectQuery = getGalaxyIdSelectQuery(ui->comboBoxSettingsGalaxy->model()->data(ui->comboBoxSettingsGalaxy->model()->index(ui->comboBoxSettingsGalaxy->currentIndex(), 0)).toString());
    if (query.exec(myGalaxySelectQuery))
    {
        query.first();
        ui->lineEditSettingsGalaxyName->setText(query.value("GalaxyName").toString());         // "Milky Way"
        ui->lineEditSettingsSunSize->setText(query.value("SunSize").toString());               // "864575.9"
        ui->lineEditSettingsPlanetSize->setText(query.value("PlanetSize").toString());         // "7926.2109"
        ui->lineEditSettingsGalaxyRadius->setText(query.value("GalaxyRadius").toString());     // "241828072282107.5071453596951"
        ui->lineEditSettingsTrinaryEngines->setText(query.value("TrinaryEngines").toString()); // "333"
        ui->lineEditSettingsNthTrack->setText(query.value("Nthtrack").toString());             // "66"
        isSaveSettings = false;
    }
    else
    {
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
}
/******************************************************************************
* \fn on_pushButtonSettingsSave_clicked Save
*******************************************************************************/
void MainWindow::on_pushButtonSettingsSave_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsSave_clicked";
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("UPDATE galaxy set GalaxyName = '").append(ui->lineEditSettingsGalaxyName->text()).append("', SunSize = '").append(ui->lineEditSettingsSunSize->text()).append("', PlanetSize = '").append(ui->lineEditSettingsPlanetSize->text()).append("', TrinaryEngines = '").append(ui->lineEditSettingsTrinaryEngines->text()).append("', GalaxyRadius = '").append(ui->lineEditSettingsGalaxyRadius->text()).append("', Nthtrack = '").append(ui->lineEditSettingsNthTrack->text()).append("' WHERE id = ").append(ui->comboBoxSettingsGalaxy->model()->data(ui->comboBoxSettingsGalaxy->model()->index(ui->comboBoxSettingsGalaxy->currentIndex(), 0)).toString());
    if (isDebugMessage) qDebug() << "thisQuery: " << thisQuery;
    if (!query.exec(thisQuery))
    {
        qDebug() << "SqLite error on_pushButtonSettingsSave_clicked:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
    ui->pushButtonSettingsSave->setEnabled(false);
    isSaveSettings = false;
    setSettingsCombo();
}
/******************************************************************************
* \fn on_pushButtonSettingsDelete_clicked Delete
*******************************************************************************/
void MainWindow::on_pushButtonSettingsDelete_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsDelete_clicked";
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("DELETE FROM galaxy WHERE id = ").append(ui->comboBoxSettingsGalaxy->model()->data(ui->comboBoxSettingsGalaxy->model()->index(ui->comboBoxSettingsGalaxy->currentIndex(), 0)).toString());
    qDebug() << "thisQuery: " << thisQuery;
    if (!query.exec(thisQuery))
    {
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
    setSettingsCombo();
}
/******************************************************************************
* \fn on_pushButtonSettingsAdd_clicked Add
*******************************************************************************/
void MainWindow::on_pushButtonSettingsAdd_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsAdd_clicked";
    QString newName = ui->lineEditSettingsGalaxyName->text();
    QSqlQuery query; //!< SQL Query
    QString myGalaxySelectQuery = getGalaxyNameSelectQuery(newName);
    if (isDebugMessage) qDebug() << "myGalaxySelectQuery: " << myGalaxySelectQuery;
    if (query.exec(myGalaxySelectQuery))
    {
        if (!query.first())
        {
            query.clear();
            QString thisQuery = QString("INSERT INTO galaxy (GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack) VALUES('").append(ui->lineEditSettingsGalaxyName->text()).append("', '").append(ui->lineEditSettingsSunSize->text()).append("', '").append(ui->lineEditSettingsPlanetSize->text()).append("', '").append(ui->lineEditSettingsTrinaryEngines->text()).append("', '").append(ui->lineEditSettingsGalaxyRadius->text()).append("', '").append(ui->lineEditSettingsNthTrack->text().append("')"));
            if (!query.exec(thisQuery))
            {
                qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError() << thisQuery;
            }
            else
            {
                setSettingsCombo(); // Refresh ComboBox
                myCount = ui->comboBoxSettingsGalaxy->count() - 1;
                QCoreApplication::processEvents();
                emit sendSettingComboBoxLastIndex();
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Record already exists in Database"), QObject::tr("Unable to add this record to databasen.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else
    {
        qDebug() << "SqLite error on_pushButtonSettingsAdd_clicked:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
    setSettingsCombo();
}
/******************************************************************************
* \fn on_pushButtonSettingsClear_clicked Clear
*******************************************************************************/
void MainWindow::on_pushButtonSettingsClear_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsClear_clicked";
    //
    ui->lineEditSettingsGalaxyName->setText("");     // "Milky Way"
    ui->lineEditSettingsSunSize->setText("");        // "864575.9"
    ui->lineEditSettingsPlanetSize->setText("");     // "7926.2109"
    ui->lineEditSettingsTrinaryEngines->setText(""); // "333"
    ui->lineEditSettingsGalaxyRadius->setText("");   // "241828072282107.5071453596951"
    ui->lineEditSettingsNthTrack->setText("");       // "66"
}
/******************************************************************************
* \fn on_pushButtonSettingsDefalut_clicked Defaults
*******************************************************************************/
void MainWindow::on_pushButtonSettingsDefalut_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsDefalut_clicked";
    //
    ui->lineEditSettingsGalaxyName->setText("Milky Way");                       // "Milky Way"
    ui->lineEditSettingsSunSize->setText("864575.9");                           // "864575.9"
    ui->lineEditSettingsPlanetSize->setText("7926.2109");                       // "7926.2109"
    ui->lineEditSettingsTrinaryEngines->setText("333");                         // "333"
    ui->lineEditSettingsGalaxyRadius->setText("241828072282107.5071453596951"); // "241828072282107.5071453596951"
    ui->lineEditSettingsNthTrack->setText("66");                                // "66"
}
/******************************************************************************
* \fn on_pushButtonPlanetClear_clicked
*******************************************************************************/
void MainWindow::on_pushButtonPlanetClear_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsClear_clicked";
    //
    ui->lineEditPlanetPlanetName->setText("");      // Planet Name
    ui->lineEditPlanetSize->setText("");            // Planet Size
    ui->lineEditPlanetSidereal->setText("");        // Sidereal Period
    ui->lineEditPlanetOrbitalDistance->setText(""); // Orbital Distance
    ui->lineEditPlanetOrbitalPeriod->setText("");   // Orbital Period
    ui->lineEditPlanetAOS->setText("");
    ui->lineEditPlanetRotational->setText("");
}
/******************************************************************************
* \fn on_pushButtonPlanetAdd_clicked
* PlanetName varchar, Diameter varchar, Sidereal varchar, OrbitalDistance varchar, OrbitalPeriod varchar
*******************************************************************************/
void MainWindow::on_pushButtonPlanetAdd_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonPlanetAdd_clicked";
    QString newName = ui->lineEditPlanetPlanetName->text();
    QSqlQuery query; //!< SQL Query
    QString myPlanetSelectQuery = getPlanetNameSelectQuery(newName);
    if (isDebugMessage) qDebug() << "myPlanetSelectQuery: " << myPlanetSelectQuery;
    if (query.exec(myPlanetSelectQuery))
    {
        if (!query.first())
        {
            query.clear();
            QString thisQuery = QString("INSERT INTO planets (PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod) VALUES('").append(ui->lineEditPlanetPlanetName->text()).append("', '").append(ui->lineEditPlanetSize->text()).append("', '").append(ui->lineEditPlanetSidereal->text()).append("', '").append(ui->lineEditPlanetOrbitalDistance->text()).append("', '").append(ui->lineEditPlanetOrbitalPeriod->text()).append("')");
            qDebug() << "SthisQuery:" << thisQuery;
            if (!query.exec(thisQuery))
            {
                qDebug() << "SqLite error on_pushButtonPlanetAdd_clicked:" << query.lastError().text() << ", SqLite error code:" << query.lastError() << thisQuery;
            }
            else
            {
                setPlanetCombo(); // Refresh ComboBox
                myCount = ui->comboBoxPlanet->count() - 1;
                QCoreApplication::processEvents();
                emit sendPlanetComboBoxLastIndex();
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Record already exists in Database"), QObject::tr("Unable to add this record to databasen.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else
    {
        qDebug() << "SqLite error on_pushButtonPlanetAdd_clicked:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
    setPlanetCombo();
}
/******************************************************************************
* \fn on_pushButtonPlanetSave_clicked
*******************************************************************************/
void MainWindow::on_pushButtonPlanetSave_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsSave_clicked";
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("UPDATE planets set PlanetName = '").append(ui->lineEditPlanetPlanetName->text()).append("', Diameter = '").append(ui->lineEditPlanetSize->text()).append("', Sidereal = '").append(ui->lineEditPlanetSidereal->text()).append("', OrbitalDistance = '").append(ui->lineEditPlanetOrbitalDistance->text()).append("', OrbitalPeriod = '").append(ui->lineEditPlanetOrbitalPeriod->text()).append("' WHERE id = ").append(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(ui->comboBoxPlanet->currentIndex(), 0)).toString());
    if (isDebugMessage) qDebug() << "thisQuery: " << thisQuery;
    if (!query.exec(thisQuery))
    {
        qDebug() << "SqLite error on_pushButtonSettingsSave_clicked:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
    ui->pushButtonSettingsSave->setEnabled(false);
    isSaveSettings = false;
    setPlanetCombo();
}
/******************************************************************************
* \fn on_pushButtonPlanetDelete_clicked
*******************************************************************************/
void MainWindow::on_pushButtonPlanetDelete_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonSettingsDelete_clicked";
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("DELETE FROM planets WHERE id = ").append(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(ui->comboBoxPlanet->currentIndex(), 0)).toString());
    qDebug() << "thisQuery: " << thisQuery;
    if (!query.exec(thisQuery))
    {
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
    setPlanetCombo();
}
/******************************************************************************
* \fn onSetComboBoxPlanet
*******************************************************************************/
void MainWindow::onSetComboBoxPlanet()
{
    ui->comboBoxPlanet->setCurrentIndex(myCount);
}
/******************************************************************************
* \fn onSetComboBoxSettings
*******************************************************************************/
void MainWindow::onSetComboBoxSettings()
{
    ui->comboBoxSettingsGalaxy->setCurrentIndex(myCount);
}
/******************************************************************************
* \fn on_pushButtonCalc0_clicked 0
*******************************************************************************/
void MainWindow::on_pushButtonCalc0_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("0"));
}
/******************************************************************************
* \fn on_pushButtonCalc1_clicked 1
*******************************************************************************/
void MainWindow::on_pushButtonCalc1_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("1"));
}
/******************************************************************************
* \fn on_pushButtonCalc2_clicked 2
*******************************************************************************/
void MainWindow::on_pushButtonCalc2_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("2"));
}
/******************************************************************************
* \fn on_pushButtonCalc3_clicked 3
*******************************************************************************/
void MainWindow::on_pushButtonCalc3_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("3"));
}
/******************************************************************************
* \fn on_pushButtonCalc4_clicked 4
*******************************************************************************/
void MainWindow::on_pushButtonCalc4_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("4"));
}
/******************************************************************************
* \fn on_pushButtonCalc5_clicked 5
*******************************************************************************/
void MainWindow::on_pushButtonCalc5_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("5"));
}
/******************************************************************************
* \fn on_pushButtonCalc6_clicked 6
*******************************************************************************/
void MainWindow::on_pushButtonCalc6_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("6"));
}
/******************************************************************************
* \fn on_pushButtonCalc7_clicked 7
*******************************************************************************/
void MainWindow::on_pushButtonCalc7_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("7"));
}
/******************************************************************************
* \fn on_pushButtonCalc8_clicked 8
*******************************************************************************/
void MainWindow::on_pushButtonCalc8_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("8"));
}
/******************************************************************************
* \fn on_pushButtonCalc9_clicked 9
*******************************************************************************/
void MainWindow::on_pushButtonCalc9_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("9"));
}
/******************************************************************************
* \fn on_pushButtonCalcClear_clicked Clear
*******************************************************************************/
void MainWindow::on_pushButtonCalcClear_clicked()
{
    ui->lineEditCalcValue->setText("");
}
/******************************************************************************
* \fn on_pushButtonCalcPlus_clicked Plus
*******************************************************************************/
void MainWindow::on_pushButtonCalcPlus_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" + "));
}
/******************************************************************************
* \fn on_pushButtonCalcDivide_clicked Divide
*******************************************************************************/
void MainWindow::on_pushButtonCalcDivide_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" / "));
}
/******************************************************************************
* \fn on_pushButtonCalcMultily_clicked Multiply
*******************************************************************************/
void MainWindow::on_pushButtonCalcMultiply_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" * "));
}
/******************************************************************************
* \fn on_pushButtonCalcPeriod_clicked Period
*******************************************************************************/
void MainWindow::on_pushButtonCalcPeriod_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("."));
}
/******************************************************************************
* \fn on_pushButtonCalcSquare_clicked Square
*******************************************************************************/
void MainWindow::on_pushButtonCalcSquare_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ^ "));
}
/******************************************************************************
* \fn on_pushButtonCalcPerentesisOpen_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcPerentesisOpen_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ( "));
}
/******************************************************************************
* \fn on_pushButtonCalcPerentesisClose_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcPerentesisClose_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ) "));
}
/******************************************************************************
* \fn on_pushButtonCalcPlusMinus_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcPlusMinus_clicked()
{
    if (ui->lineEditCalcValue->text().indexOf("-") == -1)
    {
        ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).prepend("-"));
    }
    else
    {
        ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).remove("-"));
    }
}
/******************************************************************************
* \fn on_pushButtonCalcPercentage_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcPercentage_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" % "));
}
/******************************************************************************
* \fn on_pushButtonCalcPi_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcPi_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(myTrinaryMath->getPiDecimalPlace(ui->spinBoxCalcDecimals->value()).append(" ")));
}
/******************************************************************************
* \fn on_pushButtonCalcAND_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcAND_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" && "));
}
/******************************************************************************
* \fn on_pushButtonCalcOR_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcOR_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" || "));
}
/******************************************************************************
* \fn on_pushButtonCalcXOR_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcXOR_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" % "));
}
/******************************************************************************
* \fn on_pushButtonCalcSin_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcSin_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" sin( "));
}
/******************************************************************************
* \fn on_pushButtonCalcCos_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcCos_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" cos( "));
}
/******************************************************************************
* \fn on_pushButtonCalcTan_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcTan_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" tan( "));
}
/******************************************************************************
* \fn on_pushButtonCalcStore1_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcStore1_clicked()
{
    if (ui->pushButtonCalcStore1->text().indexOf("Store") == -1)
    {
        ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(myCalcMemory1).append(" "));
    }
    else
    {
        ui->pushButtonCalcStore1->setText(tr("Recall"));
        myCalcMemory1 = ui->lineEditCalcValue->text();
    }
}
/******************************************************************************
* \fn on_pushButtonCalcStore2_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcStore2_clicked()
{
    if (ui->pushButtonCalcStore2->text().indexOf("Store") == -1)
    {
        ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(myCalcMemory2).append(" "));
    }
    else
    {
        ui->pushButtonCalcStore2->setText(tr("Recall"));
        myCalcMemory2 = ui->lineEditCalcValue->text();
    }
}
/******************************************************************************
* \fn on_pushButtonCalcStore3_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcStore3_clicked()
{
    if (ui->pushButtonCalcStore3->text().indexOf("Store") == -1)
    {
        ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(myCalcMemory3).append(" "));
    }
    else
    {
        ui->pushButtonCalcStore3->setText(tr("Recall"));
        myCalcMemory3 = ui->lineEditCalcValue->text();
    }
}
/******************************************************************************
* \fn on_pushButtonCalcLN_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcLN_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ln( "));
}
/******************************************************************************
* \fn on_pushButtonCalcPOW_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcPOW_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" pow( "));
}
/******************************************************************************
* \fn on_pushButtonCalcLOG_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcLOG_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" log( "));
}
/******************************************************************************
* \fn on_pushButtonCalcExp_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcExp_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" exp( "));
}
/******************************************************************************
* \fn on_pushButtonCalcShiftLeft_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcShiftLeft_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" << "));
}
/******************************************************************************
* \fn on_pushButtonCalcShiftRight_clicked
*******************************************************************************/

void MainWindow::on_pushButtonCalcShiftRight_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" >> "));
}
/******************************************************************************
* \fn on_pushButtonCalcBitOr_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcBitOr_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" | "));
}
/******************************************************************************
* \fn on_pushButtonCalcBitTildie_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcBitTildie_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ~ "));
}
/******************************************************************************
* \fn on_pushButtonCalc_A_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalc_A_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" A "));
}
/******************************************************************************
* \fn on_pushButtonCalc_B_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalc_B_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" B "));
}
/******************************************************************************
* \fn on_pushButtonCalc_C_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalc_C_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" C "));
}
/******************************************************************************
* \fn on_pushButtonCalc_D_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalc_D_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" D "));
}
/******************************************************************************
* \fn on_pushButtonCalc_E_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalc_E_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" E "));
}
/******************************************************************************
* \fn on_pushButtonCalc_F_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalc_F_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" F "));
}
/******************************************************************************
* \fn on_pushButtonCalcBitAmp_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcBitAmp_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" & "));
}
/******************************************************************************
* \fn on_pushButtonCalcBitX_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcBitX_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" x "));
}
/******************************************************************************
* \fn on_pushButtonCalcDoubleDivision_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcDoubleDivision_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" // "));
}
/******************************************************************************
* \fn on_comboBoxCalcConstants_currentIndexChanged
*******************************************************************************/
void MainWindow::on_comboBoxCalcConstants_currentIndexChanged(int index)
{
    if (isDebugMessage) qDebug() << "on_comboBoxCalcConstants_currentIndexChanged";
    if (!isMainLoaded) return;
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(ui->comboBoxCalcConstants->model()->data(ui->comboBoxCalcConstants->model()->index(index, 2)).toString()).append(" "));
}
/******************************************************************************
* \fn on_pushButtonCalcHelp_clicked
*******************************************************************************/
void MainWindow::on_pushButtonCalcHelp_clicked()
{
    if (isDebugMessage) qDebug() << "on_pushButtonCalcHelp_clicked";
    HelpDialog *myHelp = new HelpDialog();
    myHelp->show();
}
/******************************************************************************
* \fn printMadnessSanity
*******************************************************************************/
void MainWindow::printMadnessSanity()
{
    if (myMadnessScience == 2 && myMadnessBelief == 2)
    {
        ui->labelMadnessAnswer->setText(tr("You are Sane!"));
    }
    else if (myMadnessScience == 0 || myMadnessBelief == 0)
    {
        ui->labelMadnessAnswer->setText(tr("Answer both Questions"));
    }
    else
    {
        ui->labelMadnessAnswer->setText(tr("You are Insane!"));
    }
}
/******************************************************************************
* \fn onAbout
*******************************************************************************/
void MainWindow::onAbout()
{
    if (isDebugMessage) qDebug() << "onAbout";
    AboutDialog *myAbout = new AboutDialog();
    myAbout->show();
} // end onAbout
/******************************************************************************
* \fn on_radioButtonMadnessEinstein_clicked Einstein
* myMadnessScience: 0 = not set, 1 = insane, 2 = sane
*******************************************************************************/
void MainWindow::on_radioButtonMadnessEinstein_clicked()
{
    myMadnessScience = 1;
    printMadnessSanity();
}
/******************************************************************************
* \fn on_radioButtonMadnessNewtonian_clicked Newtonian
*******************************************************************************/
void MainWindow::on_radioButtonMadnessNewtonian_clicked()
{
    myMadnessScience = 2;
    printMadnessSanity();
}
/******************************************************************************
* \fn on_radioButtonMadnessTrinary_clicked Trinary
*******************************************************************************/
void MainWindow::on_radioButtonMadnessTrinary_clicked()
{
    myMadnessScience = 2;
    printMadnessSanity();
}
/******************************************************************************
* \fn on_radioButtonMadnessDeityGod_clicked Deity-God
* myMadnessBelief: 0 = not set, 1 = insane, 2 = sane
*******************************************************************************/
void MainWindow::on_radioButtonMadnessDeityGod_clicked()
{
    myMadnessBelief = 1;
    printMadnessSanity();
}
/******************************************************************************
* \fn on_radioButtonMadnessNoGod_clicked No God
*******************************************************************************/
void MainWindow::on_radioButtonMadnessNoGod_clicked()
{
    myMadnessBelief = 1;
    printMadnessSanity();
}
/******************************************************************************
* \fn on_radioButtonMadnessLight_clicked Light
*******************************************************************************/
void MainWindow::on_radioButtonMadnessLight_clicked()
{
    myMadnessBelief = 2;
    printMadnessSanity();
}
/******************************************************************************
* \fn on_horizontalSliderEnergyEnergy_valueChanged Energy
*******************************************************************************/
void MainWindow::on_horizontalSliderEnergyEnergy_valueChanged(int value)
{
    myEnergyEnergy = value;
    if (myEnergyCurrent > value)
    {
        myEnergyEnergy = myEnergyCurrent;
        ui->horizontalSliderEnergyEnergy->setValue(myEnergyEnergy);
    }
    ui->lineEditEnergyEnergy->setText(QString::number(myEnergyEnergy));
    getCalcSlider();
}
/******************************************************************************
* \fn on_horizontalSliderEnergyCurrent_valueChanged Energy Current Change
*******************************************************************************/
void MainWindow::on_horizontalSliderEnergyCurrent_valueChanged(int value)
{
    myEnergyCurrent = value;
    if (myEnergyEnergy < value)
    {
        myEnergyCurrent = myEnergyEnergy;
        ui->horizontalSliderEnergyCurrent->setValue(myEnergyCurrent);
    }
    ui->lineEditEnergyCurrent->setText(QString::number(myEnergyCurrent));
    getCalcSlider();
}
/******************************************************************************
* \fn on_pushButtonEnergyCalc_clicked Energy Calculate
*******************************************************************************/
void MainWindow::getCalcSlider()
{
    int thisTotalEnergy = ui->horizontalSliderEnergyEnergy->value();
    int thisCurentEnergy = ui->horizontalSliderEnergyCurrent->value();
    ui->lineEditEnergyAnswer->setText(QString("%1 %2").arg(tr("Answer"), doMath(QString("%1 - (%1 - %2)").arg(QString::number(thisTotalEnergy), QString::number(thisCurentEnergy)), 3)));
    ui->lineEditEnergyFormula->setText(QString("%1: E = F - (F - x) ~ E =  %2  - ( %2 - %3 )").arg(tr("Formula"), QString::number(thisTotalEnergy), QString::number(thisCurentEnergy)));
}
/******************************************************************************
* \fn on_pushButtonEnergyCalc_clicked Energy Calculate
*******************************************************************************/
void MainWindow::on_pushButtonEnergyCalc_clicked()
{
    if (ui->lineEditEnergyEnergy->text().length() == 0 ||  ui->lineEditEnergyEnergy->text().length() == 0)
    {
        getCalcSlider();
    }
    else
    {
        float thisEnergy = ui->lineEditEnergyEnergy->text().toFloat();
        float thisCurrentEnergy = ui->lineEditEnergyCurrent->text().toFloat();
        QString thisEnergyString = QString::number(thisCurrentEnergy);
        QString thisCurrentString = QString::number(thisCurrentEnergy);
        if (thisEnergyString.indexOf(".") != -1)
        {
            thisEnergyString = myTrinaryMath->getNumberBase(thisEnergyString);
        }
        if (thisCurrentString.indexOf(".") != -1)
        {
            thisCurrentString = myTrinaryMath->getNumberBase(thisCurrentString);
        }
        if (thisEnergyString.length() == 0 ||  thisCurrentString.length() == 0)
        {
            getCalcSlider();
        }
        else
        {
            ui->lineEditEnergyAnswer->setText(QString("%1 %2").arg(tr("Answer"), doMath(QString("%1 - (%1 - %2)").arg( QString::number(thisEnergy), thisEnergyString), 3)));
            ui->lineEditEnergyFormula->setText(QString("%1: E = F - (F - x) ~ E =  %2  - ( %2 - %3 )").arg(tr("Formula"), QString::number(thisEnergy), thisCurrentString));
        }
    }
}
/******************************************************************************
* \fn doMath
*******************************************************************************/
QString MainWindow::doMath(const QString thisEquation, int thisDecimalPlaces)
{
    if (isDebugMessage) qDebug() << "doMath";
//    MPFR_RNDN=0,  /* round to nearest, with ties to even */ 29,970,089
//    MPFR_RNDZ,    /* round toward zero */ 30,000,030
//    MPFR_RNDU,    /* round toward +Inf */
//    MPFR_RNDD,    /* round toward -Inf */
//    MPFR_RNDA,    /* round away from zero */
//    MPFR_RNDF,    /* faithful rounding */
//    MPFR_RNDNA=-1 /* round to nearest, with ties away from zero (mpfr_round) */
    mySymbolTable.clear();
    ArithmeticType thisAnswer = ExpressionParser::evaluate(thisEquation.toStdString(), mySymbolTable);
    std::string resultText = NumberFormat::toDecimal(thisAnswer, mySettings.value(SETTING_KEY_FORMATTING_PRECISION, thisDecimalPlaces).toInt(), Serializer::deserializeRoundingMode(mySettings.value(SETTING_KEY_FORMATTING_ROUNDING, MPFR_RNDZ).toInt()));
//    if (thisDecimalPlaces > 0)
//    {
//        QString thisResult = resultText.c_str();
//        QString thisFloat = getNumberFloat(thisEquation);
//        qDebug() << "thisResult: " << thisResult << " - thisDecimalPlaces: " << thisDecimalPlaces << "  - Length: " << thisFloat.length();
//    }
    return resultText.c_str();
}
/******************************************************************************
* \fn calcPlanet
*******************************************************************************/
void MainWindow::calcPlanet(const QString  thisPlanetId)
{
    if (isDebugMessage) qDebug() << "calcPlanet";
    QSqlQuery query; //!< SQL Query

    QString myGalaxySelectQuery = getPlanetSelectQuery(QString("%1").arg(thisPlanetId));

    if (query.exec(myGalaxySelectQuery))
    {
        query.first();
        if (isDebugMessage) qDebug() << "PlanetName: " << query.value("PlanetName").toString() << " - Diameter: " << query.value("Diameter").toString() << " - Sidereal: " << query.value("Sidereal").toString() << " - OrbitalDistance: " << query.value("OrbitalDistance").toString() << " - OrbitalPeriod: " << query.value("OrbitalPeriod").toString();
        ui->lineEditPlanetPlanetName->setText(query.value("PlanetName").toString());
        ui->lineEditPlanetSize->setText(query.value("Diameter").toString());
        ui->lineEditPlanetSidereal->setText(query.value("Sidereal").toString());
        ui->lineEditPlanetOrbitalDistance->setText(query.value("OrbitalDistance").toString());
        ui->lineEditPlanetOrbitalPeriod->setText(query.value("OrbitalPeriod").toString());


        QString tempResultA = doMath(QString("%1 * %2").arg(ui->lineEditPlanetSize->text(), myTrinaryMath->getPiLong()), 32);
        QString tempResultB = doMath(QString("%1 * %2").arg(ui->lineEditPlanetSidereal->text(), "24"), 32);
        QString rotation_result = doMath(QString("%1 / %2").arg(tempResultA, tempResultB), 32);


        QString tempResultC = doMath(QString("%1 * %2").arg(ui->lineEditPlanetOrbitalPeriod->text(), "24"), 32);

        QString thisDistance = doMath( QString("%1 / %2").arg(ui->lineEditPlanetOrbitalDistance->text(), tempResultC), 32);

        ui->lineEditPlanetAOS->setText(myTrinaryMath->formatNumber(thisDistance, 3));

        ui->lineEditPlanetRotational->setText(myTrinaryMath->formatNumber(rotation_result, 3));
        // query.value("PlanetName").toString()
    }
    else
    {
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
    }
}
/*** ************************* End of File ***********************************/
