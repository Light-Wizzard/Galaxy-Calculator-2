# GalaxyCalculator2.pro
# Specifies the name of the template to use when generating the project.
# The allowed values are: app, lib, subdirs, aux, vcapp or vclib
TEMPLATE     = "app"
# Specifies the name of the target file. Contains the base name of the project file by default.
# Do not use Spaces in Target Name
# This pro(ject) file is based on a pattern
TARGET           = "GalaxyCalculator2"
qtHaveModule(printsupport): QT *= printsupport
#unix:QT *= printsupport
QT              *= printsupport
QT              += gui core widgets sql
unix:QT         += webenginewidgets
#win32:QT        += webkit
CONFIG          *= qt
#CONFIG         *= "c++11"
#CONFIG          *= "c++14"
#CONFIG         *= "c++1z"
#CONFIG          *= "c++17"
#CONFIG         *= "c++2a"
CONFIG          *= "c++latest"
TRANSLATIONS    += GalaxyCalculator2_en_US.ts
CONFIG          *= warn_on utf8_source executable

win32 
{
    QMAKE_CXXFLAGS  += -Wa,-mbig-obj -O2
}

QMAKE_CXXFLAGS  += -Wa,-mbig-obj -O2

#
#win32:LIBS     *= -static
# Causes issues in Python
#win32:QMAKE_LFLAGS   += -static
#win32:CONFIG   *= windeployqt
#win32:CONFIG   *= windows
# Version Numver Controls
win32:VERSION   = 0.1.0.0 # major.minor.patch.build
else:VERSION    = 0.1.0   # major.minor.patch
DEFINES         = APP_VERSION=\\\"$${VERSION}\\\"
#
# Headers files
HEADERS     *= AboutDialog.h \
    3rdparty/cpython/modules/exprtkmodule.hpp \
    3rdparty/cpython/modules/modulecommon.hpp \
    3rdparty/cpython/pythoninclude.hpp \
    3rdparty/cpython/pyutil.hpp \
    3rdparty/cpython/symboltableconverter.hpp \
    3rdparty/cpython/types/pympreal.hpp \
    3rdparty/extern/exprtk.hpp \
    3rdparty/extern/exprtk_mpfr_adaptor.hpp \
    3rdparty/extern/json.hpp \
    3rdparty/extern/mpreal.h \
    3rdparty/io/serializer.hpp \
    3rdparty/math/arithmetictype.hpp \
    3rdparty/math/expressionparser.hpp \
    3rdparty/math/fractiontest.hpp \
    3rdparty/math/function.hpp \
    3rdparty/math/numberformat.hpp \
    3rdparty/math/script.hpp \
    3rdparty/math/scriptfunction.hpp \
    3rdparty/math/scripthandler.hpp \
    3rdparty/math/scriptvarargfunction.hpp \
    3rdparty/settingconstants.hpp \
    3rdparty/util/observable.hpp \
    3rdparty/util/uid.hpp \
    3rdparty/util/uidgenerator.hpp \
    3rdparty/math/symboltable.hpp \
    3rdparty/io/settings.hpp \
    GalaxyDataTable.h \
    GalaxySettings.h \
    HelpDialog.h \
    MainWindow.h \
    TrinaryMath.h
# Source files
SOURCES     *= AboutDialog.cpp \
    3rdparty/cpython/modules/exprtkmodule.cpp \
    3rdparty/cpython/pyutil.cpp \
    3rdparty/cpython/symboltableconverter.cpp \
    3rdparty/cpython/types/pympreal.cpp \
    3rdparty/io/serializer.cpp \
    3rdparty/math/expressionparser.cpp \
    3rdparty/math/fractiontest.cpp \
    3rdparty/math/numberformat.cpp \
    3rdparty/math/scripthandler.cpp \
    3rdparty/math/symboltable.cpp \
    GalaxyDataTable.cpp \
    GalaxySettings.cpp \
    HelpDialog.cpp \
    MainWindow.cpp \
    TrinaryMath.cpp \
    main.cpp
#    
DISTFILES += \
    .appveyor.yml \
    CODE_OF_CONDUCT.md \
    GalaxyCalculator_en_US.ts \
    Help-en.html \
    README.md    
# Ui Form(s)
FORMS       += MainWindow.ui HelpDialog.ui AboutDialog.ui
RESOURCES   += GalaxyCalculator2.qrc
# Unix
# gmp
unix:LIBS           += -L$$PWD/lib/gmp/linux/lib/ -lgmp
unix:INCLUDEPATH    += $$PWD/lib/gmp/linux/include
unix:DEPENDPATH     += $$PWD/lib/gmp/linux/include
unix:PRE_TARGETDEPS += $$PWD/lib/gmp/linux/lib/libgmp.a
# mpfr
unix: LIBS          += -L$$PWD/lib/gmp/linux/lib/ -lmpfr
unix:INCLUDEPATH    += $$PWD/lib/gmp/linux/include
unix:DEPENDPATH     += $$PWD/lib/gmp/linux/include
unix:PRE_TARGETDEPS += $$PWD/lib/gmp/linux/lib/libmpfr.a
# gmp Windows
win32:INCLUDEPATH += $$PWD/lib/gmp/windows/lib
win32:INCLUDEPATH += $$PWD/lib/gmp/windows/include
win32:DEPENDPATH  += $$PWD/lib/gmp/windows/include
win32:LIBS        += $$PWD/lib/gmp/windows/lib/libgmp-10.lib
#win32:LIBS       += -L$$PWD/lib/gmp/windows/lib/ -llibgmp-10
# mpfr Windows
win32:INCLUDEPATH += $$PWD/lib/gmp/windows/include
win32:DEPENDPATH  += $$PWD/lib/gmp/windows/include
win32:LIBS        += $$PWD/lib/gmp/windows/lib/libmpfr-4.lib
#win32:LIBS       += -L$$PWD/lib/gmp/windows/lib/ -llibmpfr-4
#
# Python Unix
PYTHON_VERSION_LINUX="3.9"
unix:INCLUDEPATH  += /usr/include/python$${PYTHON_VERSION_LINUX}
unix:DEPENDPATH   += /usr/include/python$${PYTHON_VERSION_LINUX}
unix:LIBS         += -L /usr/local/lib/python$${PYTHON_VERSION_LINUX} -lpython$${PYTHON_VERSION_LINUX}
# Python Windows
win32:INCLUDEPATH += C:/Python39/include
win32:DEPENDPATH  += C:/Python39/include
win32:LIBS        += -LC:/Python39/libs/ -lpython39
###############################################################################
#
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS
#
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#
macos:QMAKE_INFO_PLIST = macos/Info.plist
ios:QMAKE_INFO_PLIST   = ios/Info.plist
#
#DESTDIR = "$${OUT_PWD}"
#release: DESTDIR = "$${OUT_PWD}/build/release"
#debug:   DESTDIR = "$${OUT_PWD}/build/debug"

#OBJECTS_DIR = "$${DESTDIR}/obj"
#MOC_DIR     = "$${DESTDIR}/moc"
#RCC_DIR     = "$${DESTDIR}/qrc"
#UI_DIR      = "$${DESTDIR}/ui"
#
unix {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    target.path         = "$${PREFIX}/bin"
    shortcutfiles.files = "usr/share/applications/$${TARGET}.desktop"
    shortcutfiles.path  = usr/share/applications
    data.files         += "usr/share/icons/hicolor/48x48/apps/$${TARGET}.png"
    data.path           = usr/share/pixmaps
    INSTALLS           += shortcutfiles
    INSTALLS           += data
    INSTALLS           += target
    macx {
        RC_FILE = macos/Icon.icns
    }
} else {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    target.path         = "$${PREFIX}/bin"
    shortcutfiles.files = "usr/share/applications/$${TARGET}.desktop"
    shortcutfiles.path  = usr/share/applications
    data.files         += "usr/share/icons/hicolor/48x48/apps/$${TARGET}.png"
    data.path           = usr/share/pixmaps
    INSTALLS           += shortcutfiles
    INSTALLS           += data
    INSTALLS           += target
}

################################ End of File ##################################
