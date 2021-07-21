# GalaxyCalculator2.pro
# https://github.com/python/cpython
# Specifies the name of the template to use when generating the project.
# The allowed values are: app, lib, subdirs, aux, vcapp or vclib
TEMPLATE     = "app"
# Specifies the name of the target file. Contains the base name of the project file by default.
# Do not use Spaces in Target Name
# This pro(ject) file is based on a pattern
TARGET           = "GalaxyCalculator2"
qtHaveModule(printsupport): QT *= printsupport
#unix:QT *= printsupport
#QT              *= printsupport
QT              += gui core widgets sql
unix:QT         += webenginewidgets
#win32:QT        += webkit
CONFIG          *= qt
CONFIG         *= "c++11"
#CONFIG          *= "c++14"
#CONFIG         *= "c++1z"
#CONFIG          *= "c++17"
#CONFIG         *= "c++2a"
#CONFIG          *= "c++latest"
win32:CONFIG -= x86_64
win32:CONFIG += x86
TRANSLATIONS    += GalaxyCalculator2_en_US.ts
CONFIG          *= warn_on utf8_source executable
CONFIG          += release debug
win32 {
    contains(QT_ARCH, x86_64) {
        QMAKE_CXXFLAGS  += -Wa,-mbig-obj -O2
    } else {
        QMAKE_CXXFLAGS  += -flto -Wl,-allow-multiple-definition -fuse-linker-plugin
    }
}

#
win32:CONFIG   *= windeployqt
win32:CONFIG   *= windows
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
    3rdparty/gmp/include/gmp.h \
    3rdparty/gmp/include/mpf2mpfr.h \
    3rdparty/gmp/include/mpfr.h \
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
    3rdparty/gmp/README \
    3rdparty/gmp/gmp.COPYING \
    3rdparty/gmp/gmp.COPYING.LIB \
    3rdparty/gmp/gmp.README \
    3rdparty/gmp/lib/libgmp-10.dll \
    3rdparty/gmp/lib/libgmp.a \
    3rdparty/gmp/lib/libgmp.lai \
    3rdparty/gmp/lib/libgmp.so \
    3rdparty/gmp/lib/libmpfr-4.dll \
    3rdparty/gmp/lib/libmpfr.a \
    3rdparty/gmp/lib/libmpfr.lai \
    3rdparty/gmp/lib/libmpfr.so \
    3rdparty/gmp/mpfr.COPYING \
    3rdparty/gmp/mpfr.COPYING.LESSER \
    3rdparty/gmp/mpfr.README \
    CODE_OF_CONDUCT.md \
    GalaxyCalculator_en_US.ts \
    Help-en.html \
    README.md      \
    config/config.xml \
    desktop/CMakeLists.txt \
    desktop/GalaxyCalculator2.desktop \
    desktop/GalaxyCalculator2.ico \
    desktop/GalaxyCalculator2.png \
    desktop/GalaxyCalculator2.svg \
    scripts/build_script.cmd \
    scripts/build_script.sh \
    scripts/install.cmd \
    scripts/install.sh \
    scripts/upload.sh \
    usr/bin/README.md \
    usr/share/applications/GalaxyCalculator2.desktop \
    usr/share/icons/Papirus-Dark/16x16/apps/GalaxyCalculator2.svg \
    usr/share/icons/Papirus-Dark/22x22/apps/GalaxyCalculator2.svg \
    usr/share/icons/Papirus-Dark/24x24/apps/GalaxyCalculator2.svg \
    usr/share/icons/Papirus-Dark/32x32/categories/GalaxyCalculator2.svg \
    usr/share/icons/Papirus-Dark/48x48/categories/GalaxyCalculator2.svg \
    usr/share/icons/Papirus-Dark/64x64/categories/GalaxyCalculator2.svg \
    usr/share/icons/hicolor/48x48/apps/GalaxyCalculator2.png \
    usr/share/icons/hicolor/scalable/apps/GalaxyCalculator2.svg
# Ui Form(s)
FORMS       += MainWindow.ui HelpDialog.ui AboutDialog.ui
# Resources
RESOURCES   += GalaxyCalculator2.qrc
#
# gmp Unix
unix:LIBS           += -L$$PWD/3rdparty/gmp/lib/ -lgmp
unix:INCLUDEPATH    += $$PWD/3rdparty/gmp/include
unix:DEPENDPATH     += $$PWD/3rdparty/gmp/include
unix:PRE_TARGETDEPS += $$PWD/3rdparty/gmp/lib/libgmp.a
# mpfr Unix
unix: LIBS          += -L$$PWD/3rdparty/gmp/lib/ -lmpfr
unix:INCLUDEPATH    += $$PWD/3rdparty/gmp/include
unix:DEPENDPATH     += $$PWD/3rdparty/gmp/include
unix:PRE_TARGETDEPS += $$PWD/3rdparty/gmp/lib/libmpfr.a
# gmp Windows
win32:INCLUDEPATH += $$PWD/3rdparty/gmp/lib
win32:INCLUDEPATH += $$PWD/3rdparty/gmp/include
win32:DEPENDPATH  += $$PWD/3rdparty/gmp/include
#win32:LIBS        += $$PWD/3rdparty/gmp/lib/libgmp-10.lib
# C:/projects/GalaxyCalculator2/3rdparty/gmp/lib/libgmp-10.dll
win32:LIBS        += $$PWD/3rdparty/gmp/lib/libgmp-10.dll
#win32:LIBS        += -L$$PWD/3rdparty/gmp/lib/ -llibgmp-10
# mpfr Windows
win32:INCLUDEPATH += $$PWD/3rdparty/gmp/include
win32:DEPENDPATH  += $$PWD/3rdparty/gmp/include
#win32:LIBS        += $$PWD/3rdparty/gmp/lib/libmpfr-4.lib
win32:LIBS        += $$PWD/3rdparty/gmp/lib/libmpfr-4.dll
#win32:LIBS        += -L$$PWD/3rdparty/gmp/lib/ -llibmpfr-4
#
# Python Unix
PYTHON_VERSION_LINUX="3.9"
unix:INCLUDEPATH  += /usr/include/python$${PYTHON_VERSION_LINUX}
unix:DEPENDPATH   += /usr/include/python$${PYTHON_VERSION_LINUX}
unix:LIBS         += -L /usr/local/lib/python$${PYTHON_VERSION_LINUX} -lpython$${PYTHON_VERSION_LINUX}
# Python Windows
# https://python.org/downloads/windows/
win32:INCLUDEPATH += C:/Python38/include
win32:DEPENDPATH  += C:/Python38/include
#win32:LIBS        += -LC:/Python38/libs/ -lpython38
win32:LIBS        += C:/Python38/libs/python38.lib
#win32:INCLUDEPATH += $$PWD/python/windows/include
#win32:INCLUDEPATH += $$PWD/python/windows/libs
#win32:DEPENDPATH  += $$PWD/python/windows/include
#win32:LIBS        += $$PWD/python/windows/libs/python38.lib
#win32:LIBS        += -L$$PWD/python/windows/libs/ -lpython38
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
