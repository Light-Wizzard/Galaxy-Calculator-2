#ifndef MYTRINARYMATH_H
#define MYTRINARYMATH_H

#include <QObject>
#include <QMessageBox>
#include <QtMath>
#include <QtDebug>
//
// STD
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
/************************************************
 * @brief Trinary Math.
 * \class TrinaryMath
 ***********************************************/
class MyTrinaryMath : public QObject
{
        Q_OBJECT

    public:
        MyTrinaryMath(QObject *parent = nullptr); //!< TrinaryMath
        ~MyTrinaryMath();                         //!< MainWindow Destructor
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
        // Is Debug Message
        void setDebugMessage(bool thisState);        //!< set Debug Message
        bool getDebugMessage();                      //!< get Debug Message
        void setMessage(const QString &thisMessage); //!< set Message

    public slots:

    private:
        QString     myPI           = "3.14159265359";                          //!< \c PI Constant do not change value
        QString     myPiLong       = "3.141592653589793238462643383279502884"; //!< \c PI Long
        bool        isDebugMessage = true;                                     //!< \c isDebugMessage true of false
};
#endif // MYTRINARYMATH_H
/*** ************************* End of File ***********************************/
