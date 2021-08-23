#include "TrinaryMath.h"
/************************************************
 * @brief Trinary Math Constructor.
 ***********************************************/
TrinaryMath::TrinaryMath(QObject *parent) : QObject(parent)
{
    testFunctions();
}
/************************************************
 * @brief Trinary Math Deconstructor.
 ***********************************************/
TrinaryMath::~TrinaryMath()
{

}
/************************************************
 * @brief test Functions.
 ***********************************************/
bool TrinaryMath::testFunctions()
{
    bool testPassed = true;
    QString thisValue = getPI();
    if (thisValue != "3.14159265359")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("getPI"), QMessageBox::Cancel);
    }
    thisValue = getPiLong();
    if (thisValue != "3.141592653589793238462643383279502884")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("getPiLong"), QMessageBox::Cancel);
    }
    thisValue = getPiDecimalPlace(42);
    if (thisValue != "3.141592653589793238462643383279502884197169")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("getPiDecimalPlace"), QMessageBox::Cancel);
    }
    thisValue = humanize("123456");
    if (thisValue != "123,456")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("humanize"), QMessageBox::Cancel);
    }
    thisValue = formatNumber("123456.1234567", 3);
    if (thisValue != "123,456.123")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("formatNumber"), QMessageBox::Cancel);
    }
    thisValue = absValue("-1");
    if (thisValue != "1")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("absValue -1"), QMessageBox::Cancel);
    }
    thisValue = absValue("1");
    if (thisValue != "1")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("absValue 1"), QMessageBox::Cancel);
    }
    thisValue = getNumberBase("123456.1234567");
    if (thisValue != "123456")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("getNumberBase"), QMessageBox::Cancel);
    }
    thisValue = getNumberFloat("123456.1234567");
    if (thisValue != "1234567")
    {
        testPassed = false;
        QMessageBox::critical(nullptr, QObject::tr("TrinaryMath Function Failure"), QObject::tr("getNumberFloat"), QMessageBox::Cancel);
    }
    return testPassed;
}
/************************************************
 * @brief getPI.
 * 42          3.141592653589793238462643383279502884197169
 * 100         3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
 * 355 / 113 = 3.14159292035398230088495575221238938053263786810735899116172564465
 * 333 / 106 = 3.14150943396226415094339622641509433962752091994680949531609664223
 * 22  / 7   = 3.1428571428571428571428571428571428571411778652131110178457589478
 * PI: based on this version, to use a higher or lower Precession would require recalculate of baseline.
 * do not use Math.PI=3.141592653589793
 * this uses 11 bits which is what Newton used, the above uses 15
 * Constant Precession Rate: Constant in Newtons work.
 ***********************************************/
QString TrinaryMath::getPI()
{
    return myPI;
}
/************************************************
 * @brief getPiLong.
 ***********************************************/
QString TrinaryMath::getPiLong()
{
    return myPiLong;
}
/************************************************
 * @brief get Pi Decimal Place 100 places max.
 ***********************************************/
QString TrinaryMath::getPiDecimalPlace(int thisPiDecimalPlace)
{
    return QString("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679").mid(0, thisPiDecimalPlace + 2);
}
/************************************************
 * @brief absValue.
 ***********************************************/
QString TrinaryMath::absValue(const QString &thisNumber)
{
    QString thisReturn = thisNumber;
    if (thisReturn.indexOf('-') != -1) { thisReturn = thisReturn.remove("-"); }
    return thisReturn;
}
/************************************************
 * @brief humanize.
 ***********************************************/
QString TrinaryMath::humanize(const QString &thisNumber)
{
    QString theNumber = thisNumber;
    int thisNewNumber = theNumber.length();
    thisNewNumber -= 3;
    while(thisNewNumber > 0)
    {
        theNumber.insert(thisNewNumber, ',');
        thisNewNumber -= 3;
    }
    return theNumber;
}
/************************************************
 * @brief get Number Base.
 ***********************************************/
QString TrinaryMath::getNumberBase(const QString &thisNumber)
{
    return thisNumber.mid(0, thisNumber.indexOf('.'));
}
/************************************************
 * @brief get Number Float.
 ***********************************************/
QString TrinaryMath::getNumberFloat(const QString &thisNumber)
{
    return thisNumber.mid(thisNumber.indexOf('.') + 1);
}
/************************************************
 * @brief format Number.
 ***********************************************/
QString TrinaryMath::formatNumber(const QString &thisNumber, int thisPlaces)
{
    QString theNumber = thisNumber;
    int isFloat = theNumber.indexOf('.');
    if (isFloat > 0)
    {
        QString thisBaseNumber = getNumberBase(thisNumber);
        QString thisFloatNumber = getNumberFloat(thisNumber);
        theNumber = humanize(thisBaseNumber);
        if (thisPlaces == 0)
        {
            return theNumber;
        }
        else
        {

            if (thisFloatNumber.length() > thisPlaces)
            {
                thisFloatNumber = thisFloatNumber.mid(0, thisPlaces);
            }

            thisBaseNumber = theNumber.append(".");
            thisBaseNumber = thisBaseNumber.append(thisFloatNumber);

            return thisBaseNumber;
        }
    }
    else
    {
        return humanize(theNumber);
    }
    return theNumber;
}
/************************************************
 * @brief set Debug Message.
 * setDebugMessage
 ***********************************************/
void TrinaryMath::setDebugMessage(bool thisState)
{
    isDebugMessage = thisState;
}
/************************************************
 * @brief get Debug Message.
 * getDebugMessage
 ***********************************************/
bool TrinaryMath::getDebugMessage()
{
    return isDebugMessage;
}
/************************************************
 * @brief set Message.
 * setMessage
 ***********************************************/
void TrinaryMath::setMessage(const QString &thisMessage)
{
    if (isDebugMessage)
    {
        qDebug() << thisMessage;
        std::cout << thisMessage.toStdString() << std::endl;
    }
}
/*** ************************* End of File ***********************************/
