/************************************************
* @file MainWindow.cpp
* @brief MainWindow.
* @author Jeffrey Scott Flesher <Jeffrey.Scott.Flesher@>
* @version 1.0
* @section LICENSE
* Unlicenced, Free, CopyLeft.
* @section DESCRIPTION
* Main Window of GUI
* @mainpage
* Galaxy Calculator can calulate where life can exist in a Galaxy,
* it is based on the work of Henrietta Swan Leavitt,
* who was the real genius behind Hubble.
* There are a few things the Application needs to know to make this calculation,
* it has to know the size of the Sun and Liveable Planet,
* the radious of the Galaxy itself,
* and then it can plot how many Trinary Engines are required,
* and will give a table of values like minimum and maxium speed,
* and frequency, as well as distance.
 ***********************************************/
#include "MainWindow.h"
/************************************************
 * @brief MainWindow Constructor.
 * MainWindow
 ***********************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // App Icon
    QApplication::setWindowIcon(QIcon(":/images/logo32.png"));
    //
    ui->setupUi(this);
    // TrinaryMath
    myTrinaryMath  = new TrinaryMath(this);
    // Create table model:
    mySqlModel     = new MySqlDbtModel(this);
    myLocalization = new MyLocalization(this, mySqlModel->mySetting);
    // Set to defaults
    myLocalization->setTransFilePrefix("GalaxyCalculator2"); //!< Prefix of Translation files
    myLocalization->setTranslationSource("translations");     //!< Relative Folder for Translation files
    myLocalization->setHelpSource("help");                  //!< Relative Folder for Help files
    // Read in Settings First
    readSettingsFirst();
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
    ui->tableViewGalaxy->setModel(mySqlModel);
    // Make table header visible and display table:
    ui->tableViewGalaxy->horizontalHeader()->setVisible(true);
    ui->tableViewGalaxy->show();
    // SQL Database Types
    ui->comboBoxSqlDatabaseType->addItem(":memory:");
    ui->comboBoxSqlDatabaseType->addItem("QSQLITE");
    ui->comboBoxSqlDatabaseType->addItem("QSQLITE2");
    ui->comboBoxSqlDatabaseType->addItem("QDB2");
    ui->comboBoxSqlDatabaseType->addItem("QIBASE");
    ui->comboBoxSqlDatabaseType->addItem("QMYSQL");
    ui->comboBoxSqlDatabaseType->addItem("MARIADB");
    ui->comboBoxSqlDatabaseType->addItem("QOCI");
    ui->comboBoxSqlDatabaseType->addItem("QPSQL");
    ui->comboBoxSqlDatabaseType->addItem("QTDS");
    // Set Window Title to Application Name
    setWindowTitle(QApplication::applicationName());
    // Connections and Triggers
    connect(ui->actionExit,         &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionCalculate,    &QAction::triggered, this, &MainWindow::onCalculateGalaxy);
    connect(ui->actionAbout,        &QAction::triggered, this, &MainWindow::onAbout);
    connect(ui->actionAuthor,       &QAction::triggered, this, &MainWindow::onAuthor);
    connect(ui->actionHelp,         &QAction::triggered, this, &MainWindow::onHelp);
    connect(ui->actionPrint,        &QAction::triggered, this, &MainWindow::onPrintGalaxyTableView);
    connect(ui->actionExportPdf,    &QAction::triggered, this, &MainWindow::onExportPdf);
    connect(ui->actionExportHTML,   &QAction::triggered, this, &MainWindow::onExportHtml);
    //
    connect(mySqlModel, &MySqlDbtModel::sendGalaxyDataTableProgress, this, &MainWindow::onProgress);
    connect(this, &MainWindow::sendInsertGalaxy, mySqlModel, &MySqlDbtModel::onInsertGalaxyRecord);
    //
    connect(this, &MainWindow::sendSettingComboBoxLastIndex, this, &MainWindow::onSetComboBoxSettings);
    connect(this, &MainWindow::sendPlanetComboBoxLastIndex, this, &MainWindow::onSetComboBoxPlanet);
    // hide progress bar
    ui->progressBarGalaxy->hide();
    //
    myUniverseModel = new QSqlRelationalTableModel(this);
    myUniverseModel->setTable(mySqlModel->getSqlTableName());
    myUniverseModel->select();
    //
    ui->comboBoxSettingsGalaxy->setModelColumn(1);
    connect(ui->comboBoxSettingsGalaxy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onGalaxyChange);
    // Do a one time Single Shot call to onRunOnStartup to allow the GUI to load before calling what is in that call
    QTimer::singleShot(200, this, &MainWindow::onRunOnStartup);
}
/************************************************
 * @brief MainWindow Deconstructor.
 * ~MainWindow
 ***********************************************/
MainWindow::~MainWindow()
{
    delete ui;
}
/************************************************
 * @brief close Event.
 * closeEvent
 ***********************************************/
void MainWindow::closeEvent(QCloseEvent *event)
{
    setMessage("closeEvent", Debug);
    if (isSaveSettings) on_pushButtonSettingsSave_clicked();
    mySqlModel->mySetting->setGeometry(pos(), size(), isMaximized(), isMinimized());
    writeAllSettings();
    QMainWindow::closeEvent(event);
    close();
} // end closeEvent
/************************************************
 * @brief change Event.
 * changeEvent
 ***********************************************/
void MainWindow::changeEvent(QEvent *event)
{
    setMessage("changeEvent", Debug);
    if (event ->type() == QEvent::LanguageChange && isMainLoaded)
    {
        // retranslate designer form (single inheritance approach)
        ui->retranslateUi(this);
        // retranslate other widgets which weren't added in designer
        retranslate();
    }
    // remember to call base class implementation
    QMainWindow::changeEvent(event);
}
/************************************************
 * @brief retranslate.
 * retranslate
 ***********************************************/
void MainWindow::retranslate()
{
    setMessage("retranslate", Debug);
    // FIXME
    loadLanguageComboBox();
}
/************************************************
 * @brief load Language ComboBox.
 * loadLanguageComboBox
 ***********************************************/
void MainWindow::loadLanguageComboBox()
{
    setMessage("loadLanguageComboBox", Debug);
    bool lastIsMainLoaded = isMainLoaded;
    myLocalization->setMainLoaded(false);
    isMainLoaded = false;
    int theCurrentIndex = ui->comboBoxSettingsLanguage->currentIndex();
    if (theCurrentIndex < 0) { theCurrentIndex = myLanguageCombBoxIndex; }
    ui->comboBoxSettingsLanguage->clear();
    const QStringList theQmFiles =  myLocalization->findQmFiles(myLocalization->getTranslationSource());
    QStandardItemModel *theLangModel = new QStandardItemModel(this);
    theLangModel->setColumnCount(2);
    for (int i = 0; i < theQmFiles.size(); ++i)
    {
        QString theLanguageName = myLocalization->getLanguageFromFile(myLocalization->getTransFilePrefix(), theQmFiles.at(i));
        QStandardItem* theCol0 = new QStandardItem(theLanguageName);
        QStandardItem* theCol1 = new QStandardItem(tr(theLanguageName.toLocal8Bit()));
        theLangModel->setItem(i, 0, theCol0);
        theLangModel->setItem(i, 1, theCol1);
    } // end for
    QTableView* theTableView = new QTableView(this);
    theTableView->setModel(theLangModel);
    theTableView->verticalHeader()->setVisible(false);
    theTableView->horizontalHeader()->setVisible(false);
    theTableView->setColumnWidth (0, 196);
    theTableView->setColumnWidth (1, 196);
    theTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    theTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    theTableView->setAutoScroll(false);
    // Set comboBox
    ui->comboBoxSettingsLanguage->setMinimumWidth(400);
    ui->comboBoxSettingsLanguage->setModel(theLangModel);
    ui->comboBoxSettingsLanguage->setView(theTableView);
    ui->comboBoxSettingsLanguage->setCurrentIndex(theCurrentIndex);
    isMainLoaded = lastIsMainLoaded;
    myLocalization->setMainLoaded(lastIsMainLoaded);
}
/************************************************
 * @brief on checkBox Settigns Messaging state Changed.
 * on_checkBoxSettignsMessaging_stateChanged
 ***********************************************/
void MainWindow::on_checkBoxSettignsMessaging_stateChanged(int thisCheckState)
{
    if (!isMainLoaded) { return; }
    setMessage("on_checkBoxSettignsMessaging_stateChanged", Debug);
    if (thisCheckState == Qt::Checked)
        { setMessagingStates(true); }
    else
        { setMessagingStates(false); }
}
/************************************************
 * @brief set Messaging States.
 * setMessagingStates
 ***********************************************/
void MainWindow::setMessagingStates(bool thisMessageState)
{
    if (thisMessageState)
    {
        mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_IS_DEBUG_MESSAGE, "true");
        isDebugMessage = true;
        setDebugMessage(true);
        mySqlModel->setDebugMessage(true);
        mySqlModel->mySetting->setDebugMessage(true);
        myLocalization->setDebugMessage(true);
        mySqlModel->mySetting->myCrypto->setDebugMessage(true);
    }
    else
    {
        mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_IS_DEBUG_MESSAGE, "false");
        isDebugMessage = false;
        setDebugMessage(false);
        mySqlModel->setDebugMessage(false);
        mySqlModel->mySetting->setDebugMessage(false);
        myLocalization->setDebugMessage(false);
        mySqlModel->mySetting->myCrypto->setDebugMessage(false);
    }
}
/************************************************
 * @brief on Run On Startup.
 * onRunOnStartup
 ***********************************************/
void MainWindow::onRunOnStartup()
{
    isMainLoaded = false;
    myLocalization->setMainLoaded(false);
    // Go to Tab
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabWidget->findChild<QWidget*>("tabSettings")));
    // Read Settings First
    readAllSettings();
    // Read Saved Language
    myLocalization->readLanguage();
    // Get Language File
    QString theQmLanguageFile = myLocalization->getLanguageFile(myLocalization->getLanguageCode(), myLocalization->getTranslationSource(), myLocalization->getTransFilePrefix());
    // Load Language
    myLocalization->loadLanguage(theQmLanguageFile);
    QString theLastLanguage = myLocalization->getLanguageFromFile(myLocalization->getTransFilePrefix(), theQmLanguageFile);
    loadLanguageComboBox();
    ui->comboBoxSettingsLanguage->setCurrentIndex(ui->comboBoxSettingsLanguage->findText(theLastLanguage));
    //
    setMessage("onRunFirstOnStartup", Debug);
    //
    if (!mySqlModel->checkDatabase()) close();
    setSettingsCombo();
    setPlanetCombo();
    setCalcConstantCombo();

    setGalaxyTableViewSize();
    //
//    if (ui->checkBoxSettingsMemory->isChecked())
//    {
//        settingsButtons(false); // FIXME
//    }
    isMainLoaded = true;
    myLocalization->setMainLoaded(true);
    onGalaxyChange();
}
/************************************************
 * @brief read Settings First.
 * readSettingsFirst
 ***********************************************/
void MainWindow::readSettingsFirst()
{
    isDebugMessage = mySqlModel->mySetting->readSettingsBool(mySqlModel->mySetting->myConstants->MY_IS_DEBUG_MESSAGE, isDebugMessage);
    if (isDebugMessage)
        { ui->checkBoxSettignsMessaging->setCheckState(Qt::CheckState::Checked); }
    else
        { ui->checkBoxSettignsMessaging->setCheckState(Qt::CheckState::Unchecked); }
    setMessagingStates(isDebugMessage);
}
/************************************************
 * @brief read Settings.
 * readAllSettings
 ***********************************************/
void MainWindow::readAllSettings()
{
    setMessage("readAllSettings", Debug);
    //resize(myMySettings->getGeometrySize());
    //move(myMySettings->getGeometryPos());
    //
    //if(myMySettings->getGeometryMax()) setWindowState(windowState() | Qt::WindowMaximized);
    //if(myMySettings->getGeometryMin()) setWindowState(windowState() | Qt::WindowMinimized);
    //
    //
    readStatesChanges();
    readSqlDatabaseInfo();
}
/************************************************
 * @brief Write All Settings.
 * writeAllSettings
 ***********************************************/
void MainWindow::writeAllSettings()
{
    setMessage("writeAllSettings", Debug);
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_IS_DEBUG_MESSAGE, isDebugMessage ? "true" : "false");
    //
    writeStateChanges();
    writeSqlDatabaseInfo();
}
/************************************************
 * @brief read SQL Database States.
 * readSqlDatabaseStates
 ***********************************************/
void MainWindow::readStatesChanges()
{
    setMessage("readStatesChanges", Debug);
    // SQL Memory option Chech
    // default set to myProjectID="-1"
    QString theProjectID = mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_PROJECT_ID, mySqlModel->getProjectID());
    // We cannot read from the database yet, we are only getting the last states we know of
    if (theProjectID != "-1") { mySqlModel->setProjectID(theProjectID); } else { mySqlModel->setProjectID("1"); }
    mySqlModel->setProjectName(mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_PROJECT_NAME, mySqlModel->getProjectName()));
    // Project ID
    ui->labelRecordIdSettings->setText(mySqlModel->getProjectID());

    // Calc Decimals
    ui->spinBoxCalcDecimals->setValue(mySqlModel->mySetting->readSettingsInt(MY_CALC_DECIMALS, 16));
}
/************************************************
 * @brief write States Changes.
 * writeStateChanges
 ***********************************************/
void MainWindow::writeStateChanges()
{
    setMessage("writeStateChanges", Debug);
    // Project ID
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_PROJECT_ID, ui->labelRecordIdSettings->text());
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_PROJECT_NAME, ui->comboBoxSettingsGalaxy->currentText());
    // Language ComboBox
    myLocalization->setLanguageCode(myLocalization->languageNameToCode(ui->comboBoxSettingsLanguage->currentText()));
    myLocalization->writeLanguage(myLocalization->getLanguageCode());

    // Calc Decimals
    ui->spinBoxCalcDecimals->setValue(mySqlModel->mySetting->readSettingsInt(MY_CALC_DECIMALS, 16));

}
/************************************************
 * @brief write SQL Database Info Uses SimpleCrypt to encrypt and decrypt Password.
 * writeSqlDatabaseInfo
 ***********************************************/
void MainWindow::writeSqlDatabaseInfo()
{
    setMessage("writeSqlDatabaseInfo", Debug);
    // SQL Database Type Index
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_COMBO_STATE, QString::number(ui->comboBoxSqlDatabaseType->currentIndex()));
    // SQL Database Type Value
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_TYPE, ui->comboBoxSqlDatabaseType->currentText());
    // SQL Database Name
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_NAME,  ui->lineEditSqlDatabaseName->text());
    // SQL Database Type Host
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_HOST,  ui->lineEditSqlHostName->text());
    // SQL Database Type User
    mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_USER,  ui->lineEditSqlUserName->text());
    // SQL Encrypted Password, it is saved in Ini file
    if (!ui->lineEditSqlPassword->text().isEmpty())
        { mySqlModel->mySetting->writeSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_PASS, mySqlModel->mySetting->encryptThis(ui->lineEditSqlPassword->text())); }
}
/************************************************
 * @brief read SQL Database Info Uses SimpleCrypt to encrypt and decrypt Password.
 * readSqlDatabaseInfo
 ***********************************************/
void MainWindow::readSqlDatabaseInfo()
{
    setMessage("readSqlDatabaseInfo", Debug);
    QString theDb = QString("%1%2%3.db").arg(mySqlModel->mySetting->getAppDataLocation(), QDir::separator(), mySqlModel->getSqlDatabaseName());
    // SQL Database Name
    ui->lineEditSqlDatabaseName->setText(mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_NAME, theDb));
    // Set ComboBox for SQL
    ui->comboBoxSqlDatabaseType->setCurrentIndex(mySqlModel->mySetting->readSettingsInt(mySqlModel->mySetting->myConstants->MY_SQL_COMBO_STATE, 1));
    // SQL Type Value
    mySqlModel->setComboBoxSqlValue(mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_TYPE, mySqlModel->mySetting->myConstants->MY_SQL_DEFAULT));
    // SQL Host
    ui->lineEditSqlHostName->setText(mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_HOST, "")); // No Default
    // SQL User
    ui->lineEditSqlUserName->setText(mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_USER, "")); // No Default
    // SQL Decrypt Password, it is saved in Ini file
    QString thePassword = mySqlModel->mySetting->decryptThis(mySqlModel->mySetting->readSettings(mySqlModel->mySetting->myConstants->MY_SQL_DB_PASS, ""));
    if (!thePassword.isEmpty())
        { ui->lineEditSqlPassword->setText(thePassword); }
    else
        { ui->lineEditSqlPassword->setText(""); }
}
/************************************************
 * @brief set Debug Message.
 * setDebugMessage
 ***********************************************/
void MainWindow::setDebugMessage(bool thisState)
{
    isDebugMessage = thisState;
}
/************************************************
 * @brief get Debug Message.
 * getDebugMessage
 ***********************************************/
bool MainWindow::getDebugMessage()
{
    return isDebugMessage;
}
/************************************************
 * @brief on Progress.
 * onProgress
 ***********************************************/
void MainWindow::onProgress()
{
    setMessage("onProgress", Debug);
    ui->progressBarGalaxy->setValue(++myCurrentProgress);
    if (!isGalaxyTableViewSize)
    {
        setGalaxyTableViewSize();
        isGalaxyTableViewSize = true;
    }
    QCoreApplication::processEvents();
}
/************************************************
 * @brief getSymbolTable Does not get called FIXME.
 * getSymbolTable
 ***********************************************/
const SymbolTable &MainWindow::getSymbolTable()
{
    setMessage("getSymbolTable", Debug);
    return mySymbolTable;
}
/************************************************
 * @brief onSymbolTableChanged Does not get called FIXME.
 * onSymbolTableChanged
 ***********************************************/
void MainWindow::onSymbolTableChanged(const SymbolTable &symbolTableArg)
{
    this->mySymbolTable = symbolTableArg;
    //symbolsEditor->setSymbols(symbolTable, settings.value(SETTING_KEY_SYMBOLS_FORMATTING_PRECISION, SETTING_DEFAULT_SYMBOLS_FORMATTING_PRECISION).toInt());
}
/************************************************
 * @brief do Galaxy TableView Print.
 * doGalaxyTableViewPrint
 ***********************************************/
void MainWindow::doGalaxyTableViewPrint(int docTypeHandler)
{
    setMessage("doGalaxyTableViewPrint", Debug);
    if (!isTableLoaded) { onCalculateGalaxy(); }
    QString thisTitle = tr("Galaxy Calcultor");
    const int rowCount = mySqlModel->rowCount();
    const int columnCount = mySqlModel->columnCount();
    QString htmlOutput;
    htmlOutput.append(QString("<!DOCTYPE html>\n<html lang='%1'>\n").arg(myLocalization->getLanguageCode()));
    htmlOutput.append("<head>\n");
    //htmlOutput.append("<meta Content=\"Text/html; charset=Windows-1251\">\n");
    htmlOutput.append("<style> table { width:100%; } table, th, td { border: 1px solid black; border-collapse: collapse; } th, td { padding-bottom: 2px; padding-top: 2px; padding-right: 2px; text-align: right; } tr:nth-child(even) { background-color: #eeeeee; } tr:nth-child(odd) { background-color: white; } th { text-align: center; background-color: LightGray; color: black; } </style>");
    htmlOutput.append(QString("<title>%1</title>\n").arg(thisTitle));
    htmlOutput.append("</head>\n");
    htmlOutput.append("<body>\n");
    htmlOutput.append(QString("<h1 style='text-align: center;'>%1</h1>\n").arg(thisTitle));
    htmlOutput.append(QString("<h2 style='text-align: center;'>%1</h2>\n").arg(ui->lineEditSettingsGalaxyName->text()));
    htmlOutput.append(QString("<p style='text-align: center;'>%1: %2 - %3: %4</p>\n").arg(tr("Sun Diameter"), ui->lineEditSettingsSunSize->text(), tr("Planet Diameter"), ui->lineEditSettingsPlanetSize->text()));
    htmlOutput.append(QString("<p style='text-align: center;'>%1: %2 - %3: %4 - %5 %6 %7</p>\n").arg(tr("Trinary Engines"), ui->lineEditSettingsTrinaryEngines->text(), tr("Galaxy Radius"), ui->lineEditSettingsGalaxyRadius->text(), tr("Print"), "N<sup>th</sup>", ui->lineEditSettingsNthTrack->text()));
    htmlOutput.append("<table>\n");
    // headers
    htmlOutput.append("<thead>\n<tr>\n");
    for (int column = 0; column < columnCount; column++)
    {
        //if (!pPublic->tableViewGalaxy->isColumnHidden(column))
        htmlOutput.append(QString("<th>%1</th>\n").arg(mySqlModel->headerData(column, Qt::Horizontal).toString()));
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
            QString data = mySqlModel->data(mySqlModel->index(row, column)).toString().simplified();
            htmlOutput.append(QString("<td>%1</td>\n").arg((!data.isEmpty()) ? data : QString("&nbsp;")));
            //}
        }
        htmlOutput.append("</tr>\n");
    }
    htmlOutput.append("</table>\n");
    htmlOutput.append("</body>\n");
    htmlOutput.append("</html>\n");
    //
    QTextDocument  *thisTableDocument = new QTextDocument();  //!< Table Document
    //thisTableDocument->setHtml(strStream);
    thisTableDocument->setHtml(htmlOutput);
    //
    #ifndef QT_NO_PRINTER
    QPrinter thisPrinter;  //!< Printer
    #endif
    //

    switch (docTypeHandler)
    {
        case ExportPdf:
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
            break;
        }
        case ExportHtml:
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
            break;
        }
        case PrintTable:
        {
            #ifndef QT_NO_PRINTER
            QPrintDialog *dialog = new QPrintDialog(&thisPrinter, NULL);
            if (dialog->exec() == QDialog::Accepted)
            {
                thisTableDocument->print(&thisPrinter);
            }
            #endif
            break;
        }
    }
    delete thisTableDocument;
} // end doGalaxyTableViewPrint
/************************************************
 * @brief on Export Pdf.
 * onExportPdf
 ***********************************************/
void MainWindow::onExportPdf()
{
    setMessage("onExportPdf", Debug);
    doGalaxyTableViewPrint(ExportPdf);
}
/************************************************
 * @brief on Export Html.
 * onExportHtml
 ***********************************************/
void MainWindow::onExportHtml()
{
    setMessage("onExportHtml", Debug);
    doGalaxyTableViewPrint(ExportHtml);
}
/************************************************
 * @brief on Print Galaxy TableView.
 * onPrintGalaxyTableView
 ***********************************************/
void MainWindow::onPrintGalaxyTableView()
{
    setMessage("onPrintGalaxyTableView", Debug);
    doGalaxyTableViewPrint(PrintTable);
}
/************************************************
 * @brief on lineEdit Settings Galaxy Name text Changed.
 * on_lineEditSettingsGalaxyName_textChanged
 ***********************************************/
void MainWindow::on_lineEditSettingsGalaxyName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    setMessage("on_lineEditSettingsGalaxyName_textChanged", Debug);
    enableSaveButton();
}
/************************************************
 * @brief on lineEdit Settings Sun Size text Changed.
 * on_lineEditSettingsSunSize_textChanged
 ***********************************************/
void MainWindow::on_lineEditSettingsSunSize_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    setMessage("on_lineEditSettingsSunSize_textChanged", Debug);
    enableSaveButton();
}
/************************************************
 * @brief on lineEdit Settings Planet Size text Changed.
 * on_lineEditSettingsPlanetSize_textChanged
 ***********************************************/
void MainWindow::on_lineEditSettingsPlanetSize_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    setMessage("on_lineEditSettingsPlanetSize_textChanged", Debug);
    enableSaveButton();
}
/************************************************
 * @brief on lineEdit Settings Trinary Engines text Changed.
 * on_lineEditSettingsTrinaryEngines_textChanged
 ***********************************************/
void MainWindow::on_lineEditSettingsTrinaryEngines_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    setMessage("on_lineEditSettingsTrinaryEngines_textChanged", Debug);
    enableSaveButton();
}
/************************************************
 * @brief on lineEdit Settings Galaxy Radius text Changed.
 * on_lineEditSettingsGalaxyRadius_textChanged
 ***********************************************/
void MainWindow::on_lineEditSettingsGalaxyRadius_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    setMessage("on_lineEditSettingsGalaxyRadius_textChanged", Debug);
    enableSaveButton();
}
/************************************************
 * @brief on lineEdit Settings Nth Track text Changed.
 * on_lineEditSettingsNthTrack_textChanged
 ***********************************************/
void MainWindow::on_lineEditSettingsNthTrack_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    setMessage("on_lineEditSettingsNthTrack_textChanged", Debug);
    enableSaveButton();
}
/************************************************
 * @brief enable Save Button.
 * enableSaveButton
 ***********************************************/
void MainWindow::enableSaveButton()
{
    setMessage("enableSaveButton", Debug);
    // FIXME base on combobox
    isSaveSettings = true;
    ui->pushButtonSettingsSave->setEnabled(true);
}
/************************************************
 * @brief set Galaxy TableView Size.
 * setGalaxyTableViewSize
 ***********************************************/
void MainWindow::setGalaxyTableViewSize()
{
    setMessage("setTableViewSize", Debug);
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
/************************************************
 * @brief settings Buttons.
 * settingsButtons
 ***********************************************/
void MainWindow::settingsButtons(bool thisEnabled)
{
    setMessage("settingsButtons", Debug);
    ui->pushButtonSettingsAdd->setEnabled(thisEnabled);
    ui->pushButtonSettingsClear->setEnabled(thisEnabled);
    ui->pushButtonSettingsSave->setEnabled(thisEnabled);
    ui->pushButtonSettingsDefalut->setEnabled(thisEnabled);
    ui->pushButtonSettingsDelete->setEnabled(thisEnabled);
}
/************************************************
 * @brief write Settings Calc Decimal.
 * writeSettingsCalcDecimal
 ***********************************************/
bool MainWindow::writeSettingsCalcDecimal()
{
    setMessage("writeSettingsCalcDecimal", Debug);
    mySqlModel->mySetting->writeSettings(MY_CALC_DECIMALS, ui->spinBoxCalcDecimals->text()); // Number of Decimal Places in Calculator
    return true;
}
/************************************************
 * @brief on spinBox Calc Decimals text Changed.
 * on_spinBoxCalcDecimals_textChanged
 ***********************************************/
void MainWindow::on_spinBoxCalcDecimals_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    writeSettingsCalcDecimal();
}
/************************************************
 * @brief on Calculate Galaxy.
 * onCalculateGalaxy
 ***********************************************/
void MainWindow::onCalculateGalaxy()
{
    setMessage("onCalculateGalaxy", Debug);
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

    mySqlModel->clearRecords();
    // Disconnect before Connect model to table view:
    ui->tableViewGalaxy->setModel(NULL);
    ui->tableViewGalaxy->setModel(mySqlModel);
    ui->tableViewGalaxy->setAlternatingRowColors(true);
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
    int thisPrintThis;
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
    QString thisMaxSpeed;
    // minSpeed: At its Maximum Amplitude
    QString thisMinSpeed;
    // Note that there are two ways to get this value; below and using the Livable Planets Properties
    // Earth for example: Orbital distance in Miles around Sun = 584,000,000 / (365 Days * 24 Hours) = 66,666.666 MPH * .0001 = 6.6666666 Hz
    // So this is a Double Verification Process; proving that this Math actually works both ways which is Magic proving God Designed this.
    // Frequency: maxSpeed * ringSunFirst = Frequency of Livable Planet
    QString thisLpFrequency;
    // This is based on the First Ring of the Sun
    // Sun: First=0.00001, Second=0.0001, Third=.001: One Magnitude different then Planets
    QString thisRingSunFirst = "0.00001";
    // Orbital Distance in Miles around the Track.
    QString thisOrbitDist;
    // Track Frequency Multiplier based on Galaxy Ring of Power; 13 is Masonic Number in Bible
    QString thisTrackFreqMultiplier = "0.0000000000001"; // JavaScript=1e-13
    // Track Frequency: .0000000000001 * |minSpeed|
    QString thisTrackFreq;
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
    setMessage("Finished", Debug);
    isTableLoaded = true;
    ui->progressBarGalaxy->hide();
    setGalaxyTableViewSize();
}
/************************************************
 * @brief get Live Planet Ring Freq.
 * getLivePlanetRingFreq
 ***********************************************/
QString MainWindow::getLivePlanetRingFreq()
{
    return myLivePlanetRingFreq;
}
/************************************************
 * @brief on pushButton Calc Enter clicked.
 * on_pushButtonCalcEnter_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcEnter_clicked()
{
    setMessage("on_pushButtonCalcEnter_clicked", Debug);
    ui->lineEditCalcValue->setText(doMath(ui->lineEditCalcValue->text(), ui->spinBoxCalcDecimals->value()));
}
/************************************************
 * @brief set Calc Constant Combo.
 * setCalcConstantCombo
 ***********************************************/
void MainWindow::setCalcConstantCombo()
{
    QSqlQueryModel *theModalGalaxy = new QSqlQueryModel; //!< SQL Query Model
    ui->comboBoxCalcConstants->clear();
    //
    const auto SELECTED_PLANET_SQL = QLatin1String(R"(SELECT id, Name, Constant FROM math)");
    theModalGalaxy->setQuery(SELECTED_PLANET_SQL);
    if (theModalGalaxy->lastError().isValid())
    {
        setMessage(theModalGalaxy->lastError().text(), Critical);
    }
    theModalGalaxy->setHeaderData(0,Qt::Horizontal, tr("ID"));
    theModalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Name"));
    theModalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Constant"));
    QTableView *theTableView = new QTableView;
    theTableView->setModel(theModalGalaxy);
    theTableView->verticalHeader()->setVisible(false);
    theTableView->horizontalHeader()->setVisible(false);
    theTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    theTableView->setAutoScroll(false);
    theTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    theTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    theTableView->setColumnHidden(0, true);
    //view->setColumnWidth(1, 266);
    //view->setColumnWidth(2, 366);
    theTableView->resizeColumnsToContents();
    ui->comboBoxCalcConstants->setModel(nullptr);
    ui->comboBoxCalcConstants->setModel(theModalGalaxy);
    ui->comboBoxCalcConstants->setView(theTableView);
    ui->comboBoxCalcConstants->setModelColumn(1);
    ui->comboBoxCalcConstants->setCurrentIndex(0);
    // Set comboBox
    ui->comboBoxCalcConstants->setMinimumWidth(200);
}
/************************************************
 * @brief set Planet Combo.
 * setPlanetCombo
 ***********************************************/
void MainWindow::setPlanetCombo()
{
    QSqlQueryModel *theModalGalaxy = new QSqlQueryModel; //!< SQL Query Model
    ui->comboBoxPlanet->clear();
    //
    const auto SELECTED_PLANET_SQL = QLatin1String(R"(SELECT id, PlanetName FROM planets)");
    theModalGalaxy->setQuery(SELECTED_PLANET_SQL);
    if (theModalGalaxy->lastError().isValid())
    {
        setMessage(theModalGalaxy->lastError().text(), Critical);
    }
    theModalGalaxy->setHeaderData(0,Qt::Horizontal, tr("ID"));
    theModalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Name"));
    QTableView *theTableView = new QTableView;
    theTableView->setModel(theModalGalaxy);
    theTableView->verticalHeader()->setVisible(false);
    theTableView->horizontalHeader()->setVisible(false);
    theTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    theTableView->setAutoScroll(false);
    theTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    theTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    theTableView->setColumnHidden(0, true);
    theTableView->setColumnWidth(1, 166);
    //ui->comboBoxPlanet->setModel(nullptr);
    ui->comboBoxPlanet->setModel(theModalGalaxy);
    ui->comboBoxPlanet->setView(theTableView);
    ui->comboBoxPlanet->setModelColumn(1);
    ui->comboBoxPlanet->setCurrentIndex(0);
    // Set comboBox
    ui->comboBoxPlanet->setMinimumWidth(200);
}
/************************************************
 * @brief set Settings Combo.
 * setSettingsCombo
 ***********************************************/
void MainWindow::setSettingsCombo()
{
    QSqlQueryModel *theModalGalaxy = new QSqlQueryModel; //!< SQL Query Model
    ui->comboBoxSettingsGalaxy->clear();
    //
    const auto SELECTED_GALAXY_SQL = QLatin1String(R"(SELECT id, GalaxyName FROM galaxy)");
    theModalGalaxy->setQuery(SELECTED_GALAXY_SQL);
    if (theModalGalaxy->lastError().isValid())
    {
        setMessage(theModalGalaxy->lastError().text(), Critical);
    }
    theModalGalaxy->setHeaderData(0, Qt::Horizontal, tr("ID"));
    theModalGalaxy->setHeaderData(1, Qt::Horizontal, tr("Name"));
    QTableView *theTableView = new QTableView;
    theTableView->setModel(theModalGalaxy);
    theTableView->verticalHeader()->setVisible(false);
    theTableView->horizontalHeader()->setVisible(false);
    theTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    theTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    theTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    theTableView->setAutoScroll(false);
    theTableView->setColumnHidden(0, true);
    theTableView->setColumnWidth(1, 166);
    //ui->comboBoxSettingsGalaxy->setModel(nullptr);
    ui->comboBoxSettingsGalaxy->setModel(theModalGalaxy);
    ui->comboBoxSettingsGalaxy->setView(theTableView);
    ui->comboBoxSettingsGalaxy->setModelColumn(1);
    ui->comboBoxSettingsGalaxy->setCurrentIndex(0);
    // Set comboBox
    ui->comboBoxSettingsGalaxy->setMinimumWidth(200);
}
/************************************************
 * @brief get Galaxy Id Select Query.
 * getGalaxyIdSelectQuery
 ***********************************************/
QString MainWindow::getGalaxyIdSelectQuery(const QString &thisWhereId)
{
    setMessage("getGalaxyIdSelectQuery", Debug);
    return QString("SELECT GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack FROM galaxy WHERE id = ").append(thisWhereId);
}
/************************************************
 * @brief get Galaxy Name Select Query.
 * getGalaxyNameSelectQuery
 ***********************************************/
QString MainWindow::getGalaxyNameSelectQuery(const QString &thisWhereName)
{
    setMessage("getGalaxyNameSelectQuery", Debug);
    return QString("SELECT GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack FROM galaxy WHERE GalaxyName = '").append(thisWhereName).append("'");
}
/************************************************
 * @brief get Planet Select Query.
 * getPlanetSelectQuery
 ***********************************************/
QString MainWindow::getPlanetSelectQuery(const QString &thisWhereId)
{
    setMessage("getPlanetSelectQuery", Debug);
    return QString("SELECT id, PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod FROM planets WHERE id = ").append(thisWhereId);
}
/************************************************
 * @brief get Planet Name Select Query.
 * getPlanetNameSelectQuery
 ***********************************************/
QString MainWindow::getPlanetNameSelectQuery(const QString &thisWhereName)
{
    setMessage("getPlanetNameSelectQuery", Debug);
    return QString("SELECT id, PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod FROM planets WHERE PlanetName = '").append(thisWhereName).append("'");;
}
/************************************************
 * @brief on comboBox Planet current Index Changed.
 * on_comboBoxPlanet_currentIndexChanged
 ***********************************************/
void MainWindow::on_comboBoxPlanet_currentIndexChanged(int index)
{
    setMessage("on_comboBoxPlanet_currentIndexChanged", Debug);
    if (isMainLoaded) { calcPlanet(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(index, 0)).toString()); }
}
/************************************************
 * @brief on pushButton Planet Calculate clicked.
 * on_pushButtonPlanetCalculate_clicked
 ***********************************************/
void MainWindow::on_pushButtonPlanetCalculate_clicked()
{
    setMessage("on_pushButtonPlanetCalculate_clicked", Debug);
    calcPlanet(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(ui->comboBoxPlanet->currentIndex(), 0)).toString());
}
/************************************************
 * @brief on Galaxy Change.
 * onGalaxyChange
 ***********************************************/
void MainWindow::onGalaxyChange()
{
    setMessage("onGalaxyChange", Debug);
    QSqlQuery query; //!< SQL Query
    QString myGalaxySelectQuery = getGalaxyIdSelectQuery(ui->comboBoxSettingsGalaxy->model()->data(ui->comboBoxSettingsGalaxy->model()->index(ui->comboBoxSettingsGalaxy->currentIndex(), 0)).toString());
    if (query.exec(myGalaxySelectQuery))
    {
        if (query.first())
        {
            ui->lineEditSettingsGalaxyName->setText(query.value("GalaxyName").toString());         // "Milky Way"
            ui->lineEditSettingsSunSize->setText(query.value("SunSize").toString());               // "864575.9"
            ui->lineEditSettingsPlanetSize->setText(query.value("PlanetSize").toString());         // "7926.2109"
            ui->lineEditSettingsGalaxyRadius->setText(query.value("GalaxyRadius").toString());     // "241828072282107.5071453596951"
            ui->lineEditSettingsTrinaryEngines->setText(query.value("TrinaryEngines").toString()); // "333"
            ui->lineEditSettingsNthTrack->setText(query.value("Nthtrack").toString());             // "66"
        }
        else
        {
            setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
        }
    }
    else
    {
        setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    isSaveSettings = false;
}
/************************************************
 * @brief on pushButton Settings Save clicked.
 * on_pushButtonSettingsSave_clicked
 ***********************************************/
void MainWindow::on_pushButtonSettingsSave_clicked()
{
    setMessage("on_pushButtonSettingsSave_clicked", Debug);
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("UPDATE galaxy set GalaxyName = '").append(ui->lineEditSettingsGalaxyName->text()).append("', SunSize = '").append(ui->lineEditSettingsSunSize->text()).append("', PlanetSize = '").append(ui->lineEditSettingsPlanetSize->text()).append("', TrinaryEngines = '").append(ui->lineEditSettingsTrinaryEngines->text()).append("', GalaxyRadius = '").append(ui->lineEditSettingsGalaxyRadius->text()).append("', Nthtrack = '").append(ui->lineEditSettingsNthTrack->text()).append("' WHERE id = ").append(ui->comboBoxSettingsGalaxy->model()->data(ui->comboBoxSettingsGalaxy->model()->index(ui->comboBoxSettingsGalaxy->currentIndex(), 0)).toString());
    setMessage("thisQuery: " + thisQuery, Debug);
    if (!query.exec(thisQuery))
    {
        setMessage("SqLite error on_pushButtonSettingsSave_clicked:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    ui->pushButtonSettingsSave->setEnabled(false);
    isSaveSettings = false;
    setSettingsCombo();
}
/************************************************
 * @brief on pushButton Settings Delete clicked.
 * on_pushButtonSettingsDelete_clicked
 ***********************************************/
void MainWindow::on_pushButtonSettingsDelete_clicked()
{
    setMessage("on_pushButtonSettingsDelete_clicked", Debug);
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("DELETE FROM galaxy WHERE id = ").append(ui->comboBoxSettingsGalaxy->model()->data(ui->comboBoxSettingsGalaxy->model()->index(ui->comboBoxSettingsGalaxy->currentIndex(), 0)).toString());
    setMessage("thisQuery: " + thisQuery, Debug);
    if (!query.exec(thisQuery))
    {
        setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    setSettingsCombo();
}
/************************************************
 * @brief on pushButton Settings Add clicked.
 * on_pushButtonSettingsAdd_clicked
 ***********************************************/
void MainWindow::on_pushButtonSettingsAdd_clicked()
{
    setMessage("on_pushButtonSettingsAdd_clicked", Debug);
    QString newName = ui->lineEditSettingsGalaxyName->text();
    QSqlQuery query; //!< SQL Query
    QString myGalaxySelectQuery = getGalaxyNameSelectQuery(newName);
    setMessage("myGalaxySelectQuery: " + myGalaxySelectQuery, Debug);
    if (query.exec(myGalaxySelectQuery))
    {
        if (!query.first())
        {
            query.clear();
            QString thisQuery = QString("INSERT INTO galaxy (GalaxyName, SunSize, PlanetSize, TrinaryEngines, GalaxyRadius, Nthtrack) VALUES('").append(ui->lineEditSettingsGalaxyName->text()).append("', '").append(ui->lineEditSettingsSunSize->text()).append("', '").append(ui->lineEditSettingsPlanetSize->text()).append("', '").append(ui->lineEditSettingsTrinaryEngines->text()).append("', '").append(ui->lineEditSettingsGalaxyRadius->text()).append("', '").append(ui->lineEditSettingsNthTrack->text().append("')"));
            if (!query.exec(thisQuery))
            {
                setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text() + thisQuery, Critical);
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
            QMessageBox::critical(nullptr, QObject::tr("Record already exists in Database"), QObject::tr("Unable to add this record to databasen. Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else
    {
        setMessage("SqLite error on_pushButtonSettingsAdd_clicked:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    setSettingsCombo();
}
/************************************************
 * @brief on pushButton Settings Clear clicked.
 * on_pushButtonSettingsClear_clicked
 ***********************************************/
void MainWindow::on_pushButtonSettingsClear_clicked()
{
    setMessage("on_pushButtonSettingsClear_clicked", Debug);
    //
    ui->lineEditSettingsGalaxyName->setText("");     // "Milky Way"
    ui->lineEditSettingsSunSize->setText("");        // "864575.9"
    ui->lineEditSettingsPlanetSize->setText("");     // "7926.2109"
    ui->lineEditSettingsTrinaryEngines->setText(""); // "333"
    ui->lineEditSettingsGalaxyRadius->setText("");   // "241828072282107.5071453596951"
    ui->lineEditSettingsNthTrack->setText("");       // "66"
}
/************************************************
 * @brief on pushButton Settings Defalut clicked.
 * on_pushButtonSettingsDefalut_clicked
 ***********************************************/
void MainWindow::on_pushButtonSettingsDefalut_clicked()
{
    setMessage("on_pushButtonSettingsDefalut_clicked", Debug);
    //
    ui->lineEditSettingsGalaxyName->setText("Milky Way");                       // "Milky Way"
    ui->lineEditSettingsSunSize->setText("864575.9");                           // "864575.9"
    ui->lineEditSettingsPlanetSize->setText("7926.2109");                       // "7926.2109"
    ui->lineEditSettingsTrinaryEngines->setText("333");                         // "333"
    ui->lineEditSettingsGalaxyRadius->setText("241828072282107.5071453596951"); // "241828072282107.5071453596951"
    ui->lineEditSettingsNthTrack->setText("66");                                // "66"
}
/************************************************
 * @brief on pushButton Planet Clear clicked.
 * on_pushButtonPlanetClear_clicked
 ***********************************************/
void MainWindow::on_pushButtonPlanetClear_clicked()
{
    setMessage("on_pushButtonSettingsClear_clicked", Debug);
    //
    ui->lineEditPlanetPlanetName->setText("");      // Planet Name
    ui->lineEditPlanetSize->setText("");            // Planet Size
    ui->lineEditPlanetSidereal->setText("");        // Sidereal Period
    ui->lineEditPlanetOrbitalDistance->setText(""); // Orbital Distance
    ui->lineEditPlanetOrbitalPeriod->setText("");   // Orbital Period
    ui->lineEditPlanetAOS->setText("");
    ui->lineEditPlanetRotational->setText("");
}
/************************************************
 * @brief on pushButton Planet Add clicked.
 * on_pushButtonPlanetAdd_clicked
 ***********************************************/
void MainWindow::on_pushButtonPlanetAdd_clicked()
{
    setMessage("on_pushButtonPlanetAdd_clicked", Debug);
    QString newName = ui->lineEditPlanetPlanetName->text();
    QSqlQuery query; //!< SQL Query
    QString myPlanetSelectQuery = getPlanetNameSelectQuery(newName);
    setMessage("myPlanetSelectQuery: " + myPlanetSelectQuery, Debug);
    if (query.exec(myPlanetSelectQuery))
    {
        if (!query.first())
        {
            query.clear();
            QString thisQuery = QString("INSERT INTO planets (PlanetName, Diameter, Sidereal, OrbitalDistance, OrbitalPeriod) VALUES('").append(ui->lineEditPlanetPlanetName->text()).append("', '").append(ui->lineEditPlanetSize->text()).append("', '").append(ui->lineEditPlanetSidereal->text()).append("', '").append(ui->lineEditPlanetOrbitalDistance->text()).append("', '").append(ui->lineEditPlanetOrbitalPeriod->text()).append("')");
            setMessage("thisQuery:" + thisQuery, Debug);
            if (!query.exec(thisQuery))
            {
                setMessage("SqLite error on_pushButtonPlanetAdd_clicked:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text() + thisQuery, Critical);
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
            QMessageBox::critical(nullptr, QObject::tr("Record already exists in Database"), QObject::tr("Unable to add this record to databasen. Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else
    {
        setMessage("SqLite error on_pushButtonPlanetAdd_clicked:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    setPlanetCombo();
}
/************************************************
 * @brief on pushButton Planet Save clicked.
 * on_pushButtonPlanetSave_clicked
 ***********************************************/
void MainWindow::on_pushButtonPlanetSave_clicked()
{
    setMessage("on_pushButtonSettingsSave_clicked", Debug);
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("UPDATE planets set PlanetName = '").append(ui->lineEditPlanetPlanetName->text()).append("', Diameter = '").append(ui->lineEditPlanetSize->text()).append("', Sidereal = '").append(ui->lineEditPlanetSidereal->text()).append("', OrbitalDistance = '").append(ui->lineEditPlanetOrbitalDistance->text()).append("', OrbitalPeriod = '").append(ui->lineEditPlanetOrbitalPeriod->text()).append("' WHERE id = ").append(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(ui->comboBoxPlanet->currentIndex(), 0)).toString());
    setMessage("thisQuery: " + thisQuery, Debug);
    if (!query.exec(thisQuery))
    {
        setMessage("SqLite error on_pushButtonSettingsSave_clicked:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    ui->pushButtonSettingsSave->setEnabled(false);
    isSaveSettings = false;
    setPlanetCombo();
}
/************************************************
 * @brief on pushButton Planet Delete clicked.
 * on_pushButtonPlanetDelete_clicked
 ***********************************************/
void MainWindow::on_pushButtonPlanetDelete_clicked()
{
    setMessage("on_pushButtonSettingsDelete_clicked", Debug);
    QSqlQuery query; //!< SQL Query
    QString thisQuery = QString("DELETE FROM planets WHERE id = ").append(ui->comboBoxPlanet->model()->data(ui->comboBoxPlanet->model()->index(ui->comboBoxPlanet->currentIndex(), 0)).toString());
    setMessage("thisQuery: " + thisQuery, Debug);
    if (!query.exec(thisQuery))
    {
        setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
    setPlanetCombo();
}
/************************************************
 * @brief on Set ComboBox Planet.
 * onSetComboBoxPlanet
 ***********************************************/
void MainWindow::onSetComboBoxPlanet()
{
    ui->comboBoxPlanet->setCurrentIndex(myCount);
}
/************************************************
 * @brief on Set ComboBox Settings.
 * onSetComboBoxSettings
 ***********************************************/
void MainWindow::onSetComboBoxSettings()
{
    ui->comboBoxSettingsGalaxy->setCurrentIndex(myCount);
}
/************************************************
 * @brief on pushButton Calc 0 clicked.
 * on_pushButtonCalc0_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc0_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("0"));
}
/************************************************
 * @brief on pushButton Calc 1 clicked.
 * on_pushButtonCalc1_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc1_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("1"));
}
/************************************************
 * @brief on pushButton Calc 2 clicked.
 * on_pushButtonCalc2_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc2_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("2"));
}
/************************************************
 * @brief on pushButton Calc 3 clicked.
 * on_pushButtonCalc3_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc3_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("3"));
}
/************************************************
 * @brief on pushButton Calc 4 clicked.
 * on_pushButtonCalc4_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc4_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("4"));
}
/************************************************
 * @brief on pushButton Calc 5 clicked.
 * on_pushButtonCalc5_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc5_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("5"));
}
/************************************************
 * @brief on pushButton Calc 6 clicked.
 * on_pushButtonCalc6_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc6_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("6"));
}
/************************************************
 * @brief on pushButton Calc 7 clicked.
 * on_pushButtonCalc7_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc7_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("7"));
}
/************************************************
 * @brief on pushButton Calc 8 clicked.
 * on_pushButtonCalc8_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc8_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("8"));
}
/************************************************
 * @brief on pushButton Calc 9 clicked.
 * on_pushButtonCalc9_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc9_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("9"));
}
/************************************************
 * @brief on pushButton Calc Clear clicked.
 * on_pushButtonCalcClear_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcClear_clicked()
{
    ui->lineEditCalcValue->setText("");
}
/************************************************
 * @brief on pushButton Calc Plus clicked.
 * on_pushButtonCalcPlus_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcPlus_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" + "));
}
/************************************************
 * @brief on pushButton Calc Divide clicked.
 * on_pushButtonCalcDivide_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcDivide_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" / "));
}
/************************************************
 * @brief on pushButton Calc Multiply clicked.
 * on_pushButtonCalcMultiply_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcMultiply_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" * "));
}
/************************************************
 * @brief doGalaxyTableViewPrint.
 * doGalaxyTableViewPrint
 ***********************************************/
void MainWindow::on_pushButtonCalcPeriod_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append("."));
}
/************************************************
 * @brief on pushButton Calc Square clicked.
 * on_pushButtonCalcSquare_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcSquare_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ^ "));
}
/************************************************
 * @brief doGalaxyTableViewPrint.
 * doGalaxyTableViewPrint
 ***********************************************/
void MainWindow::on_pushButtonCalcPerentesisOpen_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ( "));
}
/************************************************
 * @brief on pushButton Calc Perentesis Close clicked.
 * on_pushButtonCalcPerentesisClose_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcPerentesisClose_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ) "));
}
/************************************************
 * @brief on pushButton Calc Plus Minus clicked.
 * on_pushButtonCalcPlusMinus_clicked
 ***********************************************/
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
/************************************************
 * @brief on pushButton Calc Percentage clicked.
 * on_pushButtonCalcPercentage_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcPercentage_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" % "));
}
/************************************************
 * @brief on pushButton Calc Pi clicked.
 * on_pushButtonCalcPi_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcPi_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(myTrinaryMath->getPiDecimalPlace(ui->spinBoxCalcDecimals->value()).append(" ")));
}
/************************************************
 * @brief on pushButton Calc AND clicked.
 * on_pushButtonCalcAND_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcAND_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" && "));
}
/************************************************
 * @brief on pushButton Calc OR clicked.
 * on_pushButtonCalcOR_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcOR_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" || "));
}
/************************************************
 * @brief on pushButton Calc XOR clicked.
 * on_pushButtonCalcXOR_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcXOR_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" % "));
}
/************************************************
 * @brief on pushButton Calc Sin clicked.
 * on_pushButtonCalcSin_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcSin_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" sin( "));
}
/************************************************
 * @brief on pushButton Calc Cos clicked.
 * on_pushButtonCalcCos_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcCos_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" cos( "));
}
/************************************************
 * @brief on pushButton Calc Tan clicked.
 * on_pushButtonCalcTan_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcTan_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" tan( "));
}
/************************************************
 * @brief on pushButton Calc Store 1 clicked.
 * on_pushButtonCalcStore1_clicked
 ***********************************************/
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
/************************************************
 * @brief on pushButton Calc Store 2 clicked.
 * on_pushButtonCalcStore2_clicked
 ***********************************************/
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
/************************************************
 * @brief on pushButton Calc Store 3 clicked.
 * on_pushButtonCalcStore3_clicked
 ***********************************************/
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
/************************************************
 * @brief on pushButton Calc LN clicked.
 * on_pushButtonCalcLN_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcLN_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ln( "));
}
/************************************************
 * @brief on pushButton Calc POW clicked.
 * on_pushButtonCalcPOW_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcPOW_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" pow( "));
}
/************************************************
 * @brief on pushButton Calc LOG clicked.
 * on_pushButtonCalcLOG_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcLOG_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" log( "));
}
/************************************************
 * @brief on pushButton Calc Exp clicked.
 * on_pushButtonCalcExp_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcExp_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" exp( "));
}
/************************************************
 * @brief on pushButton Calc Shift Left clicked.
 * on_pushButtonCalcShiftLeft_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcShiftLeft_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" << "));
}
/************************************************
 * @brief on pushButton Calc Shift Right clicked.
 * on_pushButtonCalcShiftRight_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcShiftRight_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" >> "));
}
/************************************************
 * @brief on pushButton Calc Bit Or clicked.
 * on_pushButtonCalcBitOr_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcBitOr_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" | "));
}
/************************************************
 * @brief on pushButton Calc Bit Tildie clicked.
 * on_pushButtonCalcBitTildie_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcBitTildie_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ~ "));
}
/************************************************
 * @brief on push Button Calc A clicked.
 * on_pushButtonCalc_A_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc_A_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" A "));
}
/************************************************
 * @brief on pushButton Calc B clicked.
 * on_pushButtonCalc_B_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc_B_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" B "));
}
/************************************************
 * @brief on pushButton Calc C clicked.
 * on_pushButtonCalc_C_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc_C_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" C "));
}
/************************************************
 * @brief on pushButton Calc D clicked.
 * on_pushButtonCalc_D_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc_D_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" D "));
}
/************************************************
 * @brief on pushButton Calc E clicked.
 * on_pushButtonCalc_E_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc_E_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" E "));
}
/************************************************
 * @brief on pushButton Calc F clicked.
 * on_pushButtonCalc_F_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalc_F_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" F "));
}
/************************************************
 * @brief on pushButton Calc Bit Amp clicked.
 * on_pushButtonCalcBitAmp_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcBitAmp_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" & "));
}
/************************************************
 * @brief on pushButton Calc Bit X clicked.
 * on_pushButtonCalcBitX_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcBitX_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" x "));
}
/************************************************
 * @brief on pushButton Calc Double Division clicked.
 * on_pushButtonCalcDoubleDivision_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcDoubleDivision_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" // "));
}
/************************************************
 * @brief on pushButton Calc Minus clicked.
 * on_pushButtonCalcMinus_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcMinus_clicked()
{
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" - "));
}
/************************************************
 * @brief on comboBox Calc Constants current Index Changed.
 * on_comboBoxCalcConstants_currentIndexChanged
 ***********************************************/
void MainWindow::on_comboBoxCalcConstants_currentIndexChanged(int index)
{
    setMessage("on_comboBoxCalcConstants_currentIndexChanged", Debug);
    ui->lineEditCalcValue->setText(QString(ui->lineEditCalcValue->text()).append(" ").append(ui->comboBoxCalcConstants->model()->data(ui->comboBoxCalcConstants->model()->index(index, 2)).toString()).append(" "));
}
/************************************************
 * @brief doGalaxyTableViewPrint.
 * doGalaxyTableViewPrint
 ***********************************************/
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
/************************************************
 * @brief on pushButton Calc Help clicked.
 * on_pushButtonCalcHelp_clicked
 ***********************************************/
void MainWindow::on_pushButtonCalcHelp_clicked()
{
    onHelp();
}
/************************************************
 * @brief Help.
 * onHelp
 ***********************************************/
void MainWindow::onHelp()
{
    setMessage("onHelp", Debug);
    // Go to Tab
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabWidget->findChild<QWidget*>("tabHelp")));
    //
    QString theFileName = QString(":help/Help_%1.md").arg(myLocalization->getLanguageCode());
    if (!mySqlModel->mySetting->isFileExists(theFileName))
        { theFileName = QString(":help/Help_%1.md").arg(mySqlModel->mySetting->myConstants->MY_DEFAULT_LANGUAGE_CODE); }
    QString theFileContent = mySqlModel->mySetting->readFile(theFileName);
    ui->textEditHelp->setMarkdown(theFileContent);
}
/************************************************
 * @brief on About.
 * onAbout
 ***********************************************/
void MainWindow::onAbout()
{
    setMessage("onAbout", Debug);
    // Go to Tab
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabWidget->findChild<QWidget*>("tabHelp")));
    //
    QString theFileName = QString(":help/About_%1.md").arg(myLocalization->getLanguageCode());
    if (!mySqlModel->mySetting->isFileExists(theFileName))
        { theFileName = QString(":help/About_%1.md").arg(mySqlModel->mySetting->myConstants->MY_DEFAULT_LANGUAGE_CODE); }
    ui->textEditHelp->setMarkdown(mySqlModel->mySetting->readFile(theFileName));
} // end onAbout
/************************************************
 * @brief on Author.
 * onAuthor
 ***********************************************/
void MainWindow::onAuthor()
{
    setMessage("onAuthor", Debug);
    // Go to Tab
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabWidget->findChild<QWidget*>("tabHelp")));
    //
    QString theFileName = QString(":help/About-Author_%1.md").arg(myLocalization->getLanguageCode());
    if (!mySqlModel->mySetting->isFileExists(theFileName))
        { theFileName = QString(":help/About-Author_%1.md").arg(mySqlModel->mySetting->myConstants->MY_DEFAULT_LANGUAGE_CODE); }
    ui->textEditHelp->setMarkdown(mySqlModel->mySetting->readFile(theFileName));
}
/************************************************
 * @brief on radioButton Madness Einstein clicked.
 * myMadnessScience: 0 = not set, 1 = insane, 2 = sane
 * on_radioButtonMadnessEinstein_clicked
 ***********************************************/
void MainWindow::on_radioButtonMadnessEinstein_clicked()
{
    myMadnessScience = 1;
    printMadnessSanity();
}
/************************************************
 * @brief on radioButton Madness Newtonian clicked.
 * on_radioButtonMadnessNewtonian_clicked
 ***********************************************/
void MainWindow::on_radioButtonMadnessNewtonian_clicked()
{
    myMadnessScience = 2;
    printMadnessSanity();
}
/************************************************
 * @brief on radioButton Madness Trinary clicked.
 * on_radioButtonMadnessTrinary_clicked
 ***********************************************/
void MainWindow::on_radioButtonMadnessTrinary_clicked()
{
    myMadnessScience = 2;
    printMadnessSanity();
}
/************************************************
 * @brief on radioButton Madness Deity God clicked.
 * on_radioButtonMadnessDeityGod_clicked
 ***********************************************/
void MainWindow::on_radioButtonMadnessDeityGod_clicked()
{
    myMadnessBelief = 1;
    printMadnessSanity();
}
/************************************************
 * @brief on radioButton Madness No God clicked.
 * on_radioButtonMadnessNoGod_clicked
 ***********************************************/
void MainWindow::on_radioButtonMadnessNoGod_clicked()
{
    myMadnessBelief = 1;
    printMadnessSanity();
}
/************************************************
 * @brief on radioButton Madness Light clicked.
 * on_radioButtonMadnessLight_clicked
 ***********************************************/
void MainWindow::on_radioButtonMadnessLight_clicked()
{
    myMadnessBelief = 2;
    printMadnessSanity();
}
/************************************************
 * @brief on horizontalSlider Energy Energy value Changed.
 * on_horizontalSliderEnergyEnergy_valueChanged
 ***********************************************/
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
/************************************************
 * @brief on horizontalSlider Energy Current value Changed.
 * on_horizontalSliderEnergyCurrent_valueChanged
 ***********************************************/
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
/************************************************
 * @brief get Calc Slider.
 * getCalcSlider
 ***********************************************/
void MainWindow::getCalcSlider()
{
    int thisTotalEnergy = ui->horizontalSliderEnergyEnergy->value();
    int thisCurentEnergy = ui->horizontalSliderEnergyCurrent->value();
    //
    ui->lineEditEnergyAnswer->setText(QString("%1 %2").arg(tr("Answer"), doMath(QString("%1 - (%1 - %2)").arg(QString::number(thisTotalEnergy), QString::number(thisCurentEnergy)), 3)));
    ui->lineEditEnergyFormula->setText(QString("%1: E = F - (F - x) ~ E =  %2  - ( %2 - %3 )").arg(tr("Formula"), QString::number(thisTotalEnergy), QString::number(thisCurentEnergy)));
}
/************************************************
 * @brief on pushButton Energy Calc clicked.
 * on_pushButtonEnergyCalc_clicked
 ***********************************************/
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
/************************************************
 * @brief do Math.
 * doMath
 ***********************************************/
QString MainWindow::doMath(const QString &thisEquation, int thisDecimalPlaces)
{
    setMessage("doMath", Debug);
    QString theEquation = thisEquation.trimmed();
//    MPFR_RNDN=0,  /* round to nearest, with ties to even */ 29,970,089
//    MPFR_RNDZ,    /* round toward zero */ 30,000,030
//    MPFR_RNDU,    /* round toward +Inf */
//    MPFR_RNDD,    /* round toward -Inf */
//    MPFR_RNDA,    /* round away from zero */
//    MPFR_RNDF,    /* faithful rounding */
//    MPFR_RNDNA=-1 /* round to nearest, with ties away from zero (mpfr_round) */
    mySymbolTable.clear();

    ArithmeticType thisAnswer = ExpressionParser::evaluate(theEquation.toStdString(), mySymbolTable);
    std::string resultText = NumberFormat::toDecimal(thisAnswer, mySetting.value(SETTING_KEY_FORMATTING_PRECISION, thisDecimalPlaces).toInt(), Serializer::deserializeRoundingMode(mySetting.value(SETTING_KEY_FORMATTING_ROUNDING, MPFR_RNDZ).toInt()));

//    if (thisDecimalPlaces > 0)
//    {
//        QString thisResult = resultText.c_str();
//        QString thisFloat = getNumberFloat(thisEquation);
//        setMessage("thisResult: " + thisResult + " - thisDecimalPlaces: " + thisDecimalPlaces + "  - Length: " + thisFloat.length(), Critical);
//    }
    return resultText.c_str();
}
/************************************************
 * @brief calc Planet.
 * calcPlanet
 ***********************************************/
void MainWindow::calcPlanet(const QString &thisPlanetId)
{
    setMessage("calcPlanet", Debug);
    QSqlQuery query; //!< SQL Query

    QString myGalaxySelectQuery = getPlanetSelectQuery(QString("%1").arg(thisPlanetId));

    if (query.exec(myGalaxySelectQuery))
    {
        if (query.first())
        {
            setMessage("PlanetName: " + query.value("PlanetName").toString() + " - Diameter: " + query.value("Diameter").toString() + " - Sidereal: " + query.value("Sidereal").toString() + " - OrbitalDistance: " + query.value("OrbitalDistance").toString() + " - OrbitalPeriod: " + query.value("OrbitalPeriod").toString(), Debug);
            ui->lineEditPlanetPlanetName->setText(query.value("PlanetName").toString());
            ui->lineEditPlanetSize->setText(query.value("Diameter").toString());
            ui->lineEditPlanetSidereal->setText(query.value("Sidereal").toString());
            ui->lineEditPlanetOrbitalDistance->setText(query.value("OrbitalDistance").toString());
            ui->lineEditPlanetOrbitalPeriod->setText(query.value("OrbitalPeriod").toString());
        }
        else
        {
            setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
        }
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
        setMessage("SqLite error:" + query.lastError().text() + ", SqLite error code:" + query.lastError().text(), Critical);
    }
}
/************************************************
 * on_pushButtonSqlSave_clicked
 * @brief on pushButton SQL Save clicked.
 ***********************************************/
void MainWindow::on_pushButtonSqlSave_clicked()
{
    setMessage("on_pushButtonSqlSave_clicked", Debug);
    writeStateChanges();
}
/************************************************
 * @brief on pushButton SQL Password Show clicked.
 * on_pushButtonSqlPasswordShow_clicked
 ***********************************************/
void MainWindow::on_pushButtonSqlPasswordShow_clicked()
{
    setMessage("on_pushButtonSqlPasswordShow_clicked", Debug);
    mySqlModel->mySetting->showMessageBox(QObject::tr("Password Revieled").toLocal8Bit(), ui->lineEditSqlPassword->text().toLocal8Bit(), mySqlModel->mySetting->Information);
}
/************************************************
 * @brief SQL Database Name Browse clicked.
 * on_pushButtonSqlDatabaseNameBrowse_clicked
 ***********************************************/
void MainWindow::on_pushButtonSqlDatabaseNameBrowse_clicked()
{
    setMessage("on_pushButtonSqlDatabaseNameBrowse_clicked", Debug);
    QFileDialog dialogSqlDbFolder;
    dialogSqlDbFolder.setFileMode(QFileDialog::Directory);
    dialogSqlDbFolder.setOption(QFileDialog::ShowDirsOnly);
    dialogSqlDbFolder.setOption(QFileDialog::DontResolveSymlinks);
    //
    QString theSqlFolder = dialogSqlDbFolder.getExistingDirectory(this, tr("Sqlite Folder Location"), mySqlModel->mySetting->getAppDataLocation());
    if (!theSqlFolder.isEmpty())
    {
        QString theDbLocation = ui->lineEditSqlDatabaseName->text();
        QString theDbNewLocation = QString("%1/%2.db").arg(theSqlFolder, mySqlModel->getSqlDatabaseName());
        if (theDbLocation != theDbNewLocation)
        {
            //
            if (mySqlModel->mySetting->getFileInfo(MyOrgSettings::IsFile, ui->lineEditSqlDatabaseName->text()) == "true")
            {
                QString thePath = mySqlModel->mySetting->getFileInfo(MyOrgSettings::CanonicalFilePath, ui->lineEditSqlDatabaseName->text());
                // moveDb
                if (mySqlModel->moveDb(theDbNewLocation, thePath, theDbNewLocation))
                { ui->lineEditSqlDatabaseName->setText(theDbNewLocation); }
                else
                { mySqlModel->mySetting->showMessageBox(QObject::tr("Database Move Failed").toLocal8Bit(), QString("%1: %2").arg(tr("Failed to move Database"), ui->lineEditSqlDatabaseName->text()).toLocal8Bit(), mySqlModel->mySetting->Critical); }
            }
        }
    }
}
/************************************************
 * @brief set SQL Browse Button.
 * setSqlBrowseButton
 ***********************************************/
void MainWindow::setSqlBrowseButton()
{
    setMessage("settingsButtons", Debug);
    ui->pushButtonSqlDatabaseNameBrowse->setEnabled(ui->comboBoxSqlDatabaseType->currentText() == mySqlModel->mySetting->myConstants->MY_SQL_DEFAULT || ui->comboBoxSqlDatabaseType->currentText() == ":memory:");
}
/************************************************
 * @brief on comboBox SQL Database Type current Index Changed.
 * on_comboBoxSqlDatabaseType_currentIndexChanged
 ***********************************************/
void MainWindow::on_comboBoxSqlDatabaseType_currentIndexChanged(const QString &thisSqlType)
{
    if (!isMainLoaded) { return; }
    setMessage("on_comboBoxSqlDatabaseType_currentIndexChanged=" + thisSqlType, Debug);
    mySqlModel->setSqlDriver(thisSqlType);
    writeStateChanges();
    setSqlBrowseButton();
}
/************************************************
 * @brief on comboBox Settings Language current Index Changed.
 * on_comboBoxSettingsLanguage_currentIndexChanged
 ***********************************************/
void MainWindow::on_comboBoxSettingsLanguage_currentIndexChanged(const QString &thisLanguage)
{
    if (!isMainLoaded) { return; }
    setMessage("on_comboBoxSettingsLanguage_currentIndexChanged", Debug);
    myLocalization->writeLanguage(myLocalization->languageNameToCode(thisLanguage));
    myLocalization->loadLanguage(myLocalization->getLanguageFile(myLocalization->languageNameToCode(thisLanguage), myLocalization->getTranslationSource(), myLocalization->getTransFilePrefix()));
}
/************************************************
 * @brief set Message.
 * setMessage
 ***********************************************/
void MainWindow::setMessage(const QString &thisMessage, MainWindow::MyMessageTypes thisMessageType)
{
    if (isDebugMessage && isMainLoaded) { return; }
    switch (thisMessageType)
    {
        case Information:
            mySqlModel->mySetting->showMessageBox(thisMessage, thisMessage, mySqlModel->mySetting->Information);
            break;
        case Warning:
            mySqlModel->mySetting->showMessageBox(thisMessage, thisMessage, mySqlModel->mySetting->Warning);
            break;
        case Critical:
            mySqlModel->mySetting->showMessageBox(thisMessage, thisMessage, mySqlModel->mySetting->Critical);
            break;
        case Debug:
            qDebug() << thisMessage;
            std::cout << thisMessage.toStdString() << std::endl;
            break;
    }
}
/*** ************************* End of File ***********************************/
