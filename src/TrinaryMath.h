#ifndef TRINARYMATH_H
#define TRINARYMATH_H

#include <QObject>
#include <QtMath>
#include <QMessageBox>

//

#include <QtDebug>
/************************************************
 * @brief Trinary Math.
 * \class TrinaryMath
 ***********************************************/
class TrinaryMath : public QObject
{
        Q_OBJECT

    public:
        TrinaryMath(QObject *parent = nullptr); //!< TrinaryMath
        ~TrinaryMath();                         //!< MainWindow Destructor
        //
        QString getPI();                                                     //!< getPI
        QString getPiLong();                                                 //!< getPiLong
        QString getPiDecimalPlace(int thisPiDecimalPlace);                   //!< getPiDecimalPlace
        QString formatNumber(const QString &thisNumber, int thisPlaces);     //!< formatNumber
        QString absValue(const QString &thisNumber);                         //!< absValue
        QString humanize(const QString &thisNumber);                         //!< humanize
        QString getNumberBase(const QString &thisNumber);                    //!< getNumberBase
        QString getNumberFloat(const QString &thisNumber);                   //!< getNumberFloat
        bool testFunctions();                                                //!< testFunctions

    public slots:

    private:
        QString     myPI           = "3.14159265359";                          //!< \c PI Constant do not change value
        QString     myPiLong       = "3.141592653589793238462643383279502884"; //!< \c PI Long
        bool        isDebugMessage = true;                                     //!< \c isDebugMessage true of false
};
#endif // TRINARYMATH_H
/*** ************************* End of File ***********************************/
