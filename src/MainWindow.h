#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//
#include <QMainWindow>
#include <QtWidgets>
#include <QTabWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtDebug>
#include <QProgressDialog>
#include <QtSql>
#include <QCloseEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QtMath>
#include <QAbstractItemView>
//
#include "ui_MainWindow.h"

#include "TrinaryMath.h"

#include "MySqlDbtModel.h"
#include "MyLocalization.h"

//
#include "3rdparty/math/symboltable.hpp"
#include "3rdparty/io/settings.hpp"
#include "3rdparty/math/numberformat.hpp"
#include "3rdparty/math/expressionparser.hpp"
#include "3rdparty/io/serializer.hpp"
#include "3rdparty/settingconstants.hpp"
//
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QComboBox;
class QFile;
class QLabel;
class QSqlRelationalTableModel;
class QTableView;
QT_END_NAMESPACE
/************************************************
 * @brief Main Window Constructor.
 * /class MainWindow
 * @author Jeffrey Scott Flesher
 ***********************************************/
class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);                              //!< MainWindow
        ~MainWindow();                                                      //!< MainWindow Destructor
        //
        enum MyDocumentType
        {
            ExportPdf   = 100, //!< \c ExportPdf  @brief Export Pdf
            ExportHtml  = 101, //!< \c ExportHtml @brief Export Html
            PrintTable  = 102, //!< \c PrintTable @brief Print Table
        }; // end enum MyFileinfo
        // Makes getting file Info easier
        Q_ENUM(MyDocumentType)
        //
        const QString MY_CALC_DECIMALS = "CalcDecimal";                     //!< \c myCalcDecimal @brief Sql Driver CalcDecimal
        //
        void readAllSettings();                                             //!< Read Settings
        void writeAllSettings();                                            //!< Write Settings

        void readGalaxyData();                                              //!< readGalaxyData
        bool writeSettingsCalcDecimal();                                    //!< writeSettingsCalcDecimal
        void settingsButtons(bool thisEnabled);                             //!< SettingsButtons
        void setGalaxyTableViewSize();                                      //!< setGalaxyTableViewSize
        void setSettingsCombo();                                            //!< setSettingsCombo
        void setPlanetCombo();                                              //!< setPlanetCombo
        void doGalaxyTableViewPrint(int isExportPdf);                       //!< geTablePrint
        QString getLivePlanetRingFreq();                                    //!< getLivePlanetRingFreq
        QString getGalaxyIdSelectQuery(const QString &thisWhereId);         //!< getGalaxySelectQuery
        QString getPlanetSelectQuery(const QString &thisWhereId);           //!< getPlanetSelectQuery
        QString getGalaxyNameSelectQuery(const QString &thisWhereName);     //!< getGalaxyNameSelectQuery
        void calcPlanet(const QString &thisPlanetId);                       //!< calcPlanet
        QString doMath(const QString &thisEquation, int thisDecimalPlaces); //!< doMath
        void printMadnessSanity();                                          //!< printMadnessSanity
        void setCalcConstantCombo();                                        //!< setCalcConstantCombo
        void getCalcSlider();                                               //!< getCalcSlider
        QString getPlanetNameSelectQuery(const QString &thisWhereName);     //!< getPlanetNameSelectQuery

        QSqlDatabase getSqlDatabase();                                      //!< get Sql Database
        void setSqlDatabase(const QSqlDatabase &thisDatabase);              //!< set Sql Database

        void retranslate();                                                 //!< retranslate
        void loadLanguageComboBox();                                        //!< load Language ComboBox
        void readSettingsFirst();                                           //!< read Settings First
        void setMessagingStates(bool thisMessageState);                     //!< set Messaging States

        void setDebugMessage(bool thisState);                               //!< set Debug Message
        bool getDebugMessage();                                             //!< get Debug Message
        void readSqlDatabaseInfo();                                         //!< read Sql Database Info
        void writeSqlDatabaseInfo();                                        //!< write Sql Database Info
        void writeStateChanges();                                           //!< write State Changes
        void readStatesChanges();                                           //!< read States Changes
        void setSqlBrowseButton();                                          //!< set Sql Browse Button

    public slots:
        void onProgress();                                                  //!< From DataTable
        void onAbout();                                                     //!< ui->actionAbout
        void onAuthor();                                                    //!< on About
        void onHelp();                                                      //!< on Help
        void onGalaxyChange();                                              //!< ui->comboBoxGalaxy
        void enableSaveButton();                                            //!< enableSaveButton
        void onCalculateGalaxy();                                           //!< onCalculateGalaxy
        void onRunOnStartup();                                              //!< onRunOnStartup
        void onSetComboBoxSettings();                                       //!< onSetComboBoxSettings
        void onSetComboBoxPlanet();                                         //!< onSetComboBoxPlanet
        // Part of Math
        const SymbolTable &getSymbolTable();                                //!< getSymbolTable
        void onSymbolTableChanged(const SymbolTable &symbolTable);          //!< onSymbolTableChanged
        void on_checkBoxSettignsMessaging_stateChanged(int thisCheckState); //!< on checkBox Settigns Messaging state Changed
        void on_comboBoxSettingsLanguage_currentIndexChanged(const QString &thisLanguage); //!< on comboBox Settings Language current Index Changed

    private slots:
        void onPrintGalaxyTableView();                                              //!< printTable
        void onExportPdf();                                                         //!< onExportPdf
        void onExportHtml();                                                        //!< onExportHtml
        // ComboBox
        void on_comboBoxSqlDatabaseType_currentIndexChanged(const QString &arg1);   //!< on comboBox Sql Database Type current Index Changed
        void on_comboBoxPlanet_currentIndexChanged(int index);                      //!< on_comboBoxPlanet_currentIndexChanged
        void on_comboBoxCalcConstants_currentIndexChanged(int index);               //!< on_comboBoxCalcConstants_currentIndexChanged
        // PushButton
        void on_pushButtonSettingsSave_clicked();                                   //!< Save
        void on_pushButtonSettingsDelete_clicked();                                 //!< Delete
        void on_pushButtonSettingsAdd_clicked();                                    //!< Add
        void on_pushButtonSettingsClear_clicked();                                  //!< Clear
        void on_pushButtonSettingsDefalut_clicked();                                //!< Defaults
        void on_pushButtonCalc0_clicked();                                          //!< 0
        void on_pushButtonCalc1_clicked();                                          //!< 1
        void on_pushButtonCalc2_clicked();                                          //!< 2
        void on_pushButtonCalc3_clicked();                                          //!< 3
        void on_pushButtonCalc4_clicked();                                          //!< 4
        void on_pushButtonCalc5_clicked();                                          //!< 5
        void on_pushButtonCalc6_clicked();                                          //!< 6
        void on_pushButtonCalc7_clicked();                                          //!< 7
        void on_pushButtonCalc8_clicked();                                          //!< 8
        void on_pushButtonCalc9_clicked();                                          //!< 9
        void on_pushButtonCalcClear_clicked();                                      //!< Clear
        void on_pushButtonCalcPlus_clicked();                                       //!< Plus
        void on_pushButtonCalcDivide_clicked();                                     //!< Divide
        void on_pushButtonCalcSquare_clicked();                                     //!< Square
        void on_pushButtonCalcEnter_clicked();                                      //!< Enter
        void on_pushButtonCalcMultiply_clicked();                                   //!< Multiply
        void on_pushButtonCalcPeriod_clicked();                                     //!< .
        void on_pushButtonCalcMinus_clicked();                                      //!< on_pushButtonCalcMinus_clicked
        void on_pushButtonPlanetCalculate_clicked();                                //!< on_pushButtonPlanetCalculate_clicked
        void on_pushButtonEnergyCalc_clicked();                                     //!< on_pushButtonEnergyCalc_clicked
        void on_pushButtonPlanetSave_clicked();                                     //!< on_pushButtonPlanetSave_clicked
        void on_pushButtonPlanetClear_clicked();                                    //!< on_pushButtonPlanetClear_clicked
        void on_pushButtonPlanetAdd_clicked();                                      //!< on_pushButtonPlanetAdd_clicked
        void on_pushButtonPlanetDelete_clicked();                                   //!< on_pushButtonPlanetDelete_clicked
        void on_pushButtonCalcPerentesisClose_clicked();                            //!< on_pushButtonCalcPerentesisClose_clicked
        void on_pushButtonCalcPerentesisOpen_clicked();                             //!< on_pushButtonCalcPerentesisOpen_clicked
        void on_pushButtonCalcPlusMinus_clicked();                                  //!< on_pushButtonCalcPlusMinus_clicked
        void on_pushButtonCalcPercentage_clicked();                                 //!< on_pushButtonCalcPercentage_clicked
        void on_pushButtonCalcPi_clicked();                                         //!< on_pushButtonCalcPi_clicked
        void on_pushButtonCalcAND_clicked();                                        //!< on_pushButtonCalcAND_clicked
        void on_pushButtonCalcOR_clicked();                                         //!< on_pushButtonCalcOR_clicked
        void on_pushButtonCalcXOR_clicked();                                        //!< on_pushButtonCalcXOR_clicked
        void on_pushButtonCalcSin_clicked();                                        //!< on_pushButtonCalcSin_clicked
        void on_pushButtonCalcCos_clicked();                                        //!< on_pushButtonCalcCos_clicked
        void on_pushButtonCalcTan_clicked();                                        //!< on_pushButtonCalcTan_clicked
        void on_pushButtonCalcStore1_clicked();                                     //!< on_pushButtonCalcStore_clicked
        void on_pushButtonCalcStore2_clicked();                                     //!< on_pushButtonCalcMemory_clicked
        void on_pushButtonCalcStore3_clicked();                                     //!< on_pushButtonCalcStore3_clicked
        void on_pushButtonCalcLN_clicked();                                         //!< on_pushButtonCalcLN_clicked
        void on_pushButtonCalcPOW_clicked();                                        //!< on_pushButtonCalcPOW_clicked
        void on_pushButtonCalcLOG_clicked();                                        //!< on_pushButtonCalcLOG_clicked
        void on_pushButtonCalcHelp_clicked();                                       //!< on_pushButtonCalcHelp_clicked
        void on_pushButtonCalcExp_clicked();                                        //!< on_pushButtonCalcExp_clicked
        void on_pushButtonCalcShiftLeft_clicked();                                  //!< on_pushButtonCalcShiftLeft_clicked
        void on_pushButtonCalcShiftRight_clicked();                                 //!< on_pushButtonCalcShiftRight_clicked
        void on_pushButtonCalcBitOr_clicked();                                      //!< on_pushButtonCalcBitOr_clicked
        void on_pushButtonCalcBitTildie_clicked();                                  //!< on_pushButtonCalcBitTildie_clicked
        void on_pushButtonCalc_A_clicked();                                         //!< on_pushButtonCalc_A_clicked
        void on_pushButtonCalc_B_clicked();                                         //!< on_pushButtonCalc_B_clicked
        void on_pushButtonCalc_C_clicked();                                         //!< on_pushButtonCalc_C_clicked
        void on_pushButtonCalc_D_clicked();                                         //!< on_pushButtonCalc_D_clicked
        void on_pushButtonCalc_E_clicked();                                         //!< on_pushButtonCalc_E_clicked
        void on_pushButtonCalc_F_clicked();                                         //!< on_pushButtonCalc_F_clicked
        void on_pushButtonCalcBitAmp_clicked();                                     //!< on_pushButtonCalcBitAmp_clicked
        void on_pushButtonCalcBitX_clicked();                                       //!< on_pushButtonCalcBitX_clicked
        void on_pushButtonCalcDoubleDivision_clicked();                             //!< on_pushButtonCalcDoubleDivision_clicked
        void on_pushButtonSqlSave_clicked();                                        //!< on pushButton Sql Save clicked
        void on_pushButtonSqlPasswordShow_clicked();                                //!< on push Button Sql Password Show clicked
        void on_pushButtonSqlDatabaseNameBrowse_clicked();                          //!< on pushButton Sql Database Name Browse clicked
        // QLineEdit
        void on_lineEditSettingsGalaxyName_textChanged(const QString &arg1);        //!< GalaxyName_textChanged
        void on_lineEditSettingsSunSize_textChanged(const QString &arg1);           //!< SunSize_textChanged
        void on_lineEditSettingsPlanetSize_textChanged(const QString &arg1);        //!< PlanetSize_textChanged
        void on_lineEditSettingsTrinaryEngines_textChanged(const QString &arg1);    //!< TrinaryEngines_textChanged
        void on_lineEditSettingsGalaxyRadius_textChanged(const QString &arg1);      //!< GalaxyRadius_textChanged
        void on_lineEditSettingsNthTrack_textChanged(const QString &arg1);          //!< NthTrack_textChanged
        // radioButton
        void on_radioButtonMadnessEinstein_clicked();                               //!< on_radioButtonMadnessEinstein_clicked
        void on_radioButtonMadnessNewtonian_clicked();                              //!< on_radioButtonMadnessNewtonian_clicked
        void on_radioButtonMadnessTrinary_clicked();                                //!< on_radioButtonMadnessTrinary_clicked
        void on_radioButtonMadnessDeityGod_clicked();                               //!< on_radioButtonMadnessDeityGod_clicked
        void on_radioButtonMadnessLight_clicked();                                  //!< on_radioButtonMadnessLight_clicked
        void on_radioButtonMadnessNoGod_clicked();                                  //!< on_radioButtonMadnessNoGod_clicked
        // horizontalSlider
        void on_horizontalSliderEnergyEnergy_valueChanged(int value);               //!< on_horizontalSliderEnergyEnergy_valueChanged
        void on_horizontalSliderEnergyCurrent_valueChanged(int value);              //!< on_horizontalSliderEnergyCurrent_valueChanged
        // spinBox
        void on_spinBoxCalcDecimals_textChanged(const QString &arg1);               //!< on_spinBoxCalcDecimals_textChanged

    protected:
        void closeEvent(QCloseEvent *event) override;           //!< close Event

    protected slots:
        virtual void changeEvent(QEvent * event) override;      //!< change Event

    signals:
        void sendInsertGalaxy(const QString &thisCurrentTrackNumber,const QString &thistrackEngines,const QString &thisMaxSpeed,const QString &thisMinSpeed,const QString &thisLpFrequency,const QString &thisOrbitDist,const QString &thisNthTrack); //!< insert record
        void sendSettingComboBoxLastIndex(); //!< sendSettingComboBoxLastIndex
        void sendPlanetComboBoxLastIndex();  //!< sendPlanetComboBoxLastIndex

    private:
        Ui::MainWindow           *ui = nullptr;                     //!< \c ui                      @brief Pointer to mainwindow.ui
        Settings                  mySetting;                        //!< \c mySetting               @brief settings
        TrinaryMath              *myTrinaryMath;                    //!< \c myMySettings            @brief Trinary Math
        MyLocalization           *myLocalization;                   //!< \c myLocalization          @brief Localization.
        MySqlDbtModel            *mySqlModel;                       //!< \c myGalaxyModel           @brief Pointer to DataTable GalaxyModel
        QSqlRelationalTableModel *myUniverseModel;                  //!< \c myUniverseModel         @brief Universe Model
        // Part of Math
        SymbolTable               mySymbolTable;                    //!< \c mySymbolTable           @brief Symbol Table
        QString                   myComboBoxSqlValue;               //!< \c myComboBoxSqlValue      @brief ComboBox Sql Value
        QString                   myLivePlanetRingFreq;             //!< \c myLivePlanetRingFreq    @brief Live Planet Ring Freq
        QString                   myCalcMemory1;                    //!< \c myCalcMemory1           @brief Calc Memory 1
        QString                   myCalcMemory2;                    //!< \c myCalcMemory2           @brief Calc Memory 2
        QString                   myCalcMemory3;                    //!< \c myCalcMemory3           @brief Calc Memory 3
        bool                      isDebugMessage        = true;     //!< \c isDebugMessage          @brief is Debug Message true of false
        bool                      isMainLoaded          = false;    //!< \c isMainLoaded            @brief is Main Loaded true of false
        bool                      isSaveSettings        = false;    //!< \c isSaveSettings          @brief Save Settings
        bool                      isTableLoaded         = false;    //!< \c isTableLoaded           @brief is Table Loaded
        bool                      isGalaxyTableViewSize = false;    //!< \c isGalaxyTableViewSize   @brief is Galaxy TableView Size
        int                       myCurrentProgress;                //!< \c myCurrentProgress       @brief Pointer to currentProgress
        int                       myCount;                          //!< \c myCount                 @brief Count
        int                       myMadnessScience       = 0;       //!< \c myMadnessScience        @brief 0 = not set, 1 = insane, 2 = sane
        int                       myMadnessBelief        = 0;       //!< \c myMadnessBelief         @brief 0 = not set, 1 = insane, 2 = sane
        int                       myEnergyEnergy         = 100;     //!< \c myEnergyEnergy          @brief Energy
        int                       myEnergyCurrent        = 66;      //!< \c myEnergyCurrent         @brief Energy Current
        int                       myLanguageCombBoxIndex = -1;      //!< \c myLanguageCombBoxIndex  @brief Language CombBox Index.
};
#endif // MAINWINDOW_H
/*** ************************* End of File ***********************************/
