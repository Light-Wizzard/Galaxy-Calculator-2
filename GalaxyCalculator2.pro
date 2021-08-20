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
QT              += core gui widgets sql network
#
CONFIG          *= qt
CONFIG          *= "c++11"
#CONFIG          *= "c++14"
#CONFIG         *= "c++1z"
#CONFIG          *= "c++17"
#CONFIG         *= "c++2a"
#CONFIG          *= "c++latest"
win32:CONFIG -= x86_64
win32:CONFIG += x86
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
#CONFIG += static
#DEFINES+= STATIC
#QMAKE_LFLAGS += -static
#
win32:CONFIG   *= windeployqt
win32:CONFIG   *= windows
#
# Headers files
HEADERS     *= \
    src/MainWindow.h \
    src/MyConstants.h \
    src/MyLocalization.h \
    src/MyOrgSettings.h \
    src/MySqlDbtModel.h \
    src/SimpleCrypt.h \
    src/TrinaryMath.h \
    src/3rdparty/cpython/modules/exprtkmodule.hpp \
    src/3rdparty/cpython/modules/modulecommon.hpp \
    src/3rdparty/cpython/pythoninclude.hpp \
    src/3rdparty/cpython/pyutil.hpp \
    src/3rdparty/cpython/symboltableconverter.hpp \
    src/3rdparty/cpython/types/pympreal.hpp \
    src/3rdparty/extern/exprtk.hpp \
    src/3rdparty/extern/exprtk_mpfr_adaptor.hpp \
    src/3rdparty/extern/json.hpp \
    src/3rdparty/extern/mpreal.h \
    src/3rdparty/gmp/include/gmp.h \
    src/3rdparty/gmp/include/mpf2mpfr.h \
    src/3rdparty/gmp/include/mpfr.h \
    src/3rdparty/io/serializer.hpp \
    src/3rdparty/math/arithmetictype.hpp \
    src/3rdparty/math/expressionparser.hpp \
    src/3rdparty/math/fractiontest.hpp \
    src/3rdparty/math/function.hpp \
    src/3rdparty/math/numberformat.hpp \
    src/3rdparty/math/script.hpp \
    src/3rdparty/math/scriptfunction.hpp \
    src/3rdparty/math/scripthandler.hpp \
    src/3rdparty/math/scriptvarargfunction.hpp \
    src/3rdparty/settingconstants.hpp \
    src/3rdparty/util/observable.hpp \
    src/3rdparty/util/uid.hpp \
    src/3rdparty/util/uidgenerator.hpp \
    src/3rdparty/math/symboltable.hpp \
    src/3rdparty/io/settings.hpp
    
# Source files
SOURCES     *= \
    src/MainWindow.cpp \
    src/MyLocalization.cpp \
    src/MyOrgSettings.cpp \
    src/MySqlDbtModel.cpp \
    src/SimpleCrypt.cpp \
    src/TrinaryMath.cpp \
    src/main.cpp \
    src/3rdparty/cpython/modules/exprtkmodule.cpp \
    src/3rdparty/cpython/pyutil.cpp \
    src/3rdparty/cpython/symboltableconverter.cpp \
    src/3rdparty/cpython/types/pympreal.cpp \
    src/3rdparty/io/serializer.cpp \
    src/3rdparty/math/expressionparser.cpp \
    src/3rdparty/math/fractiontest.cpp \
    src/3rdparty/math/numberformat.cpp \
    src/3rdparty/math/scripthandler.cpp \
    src/3rdparty/math/symboltable.cpp
#    
CONFIG += localize_deployment
SYMBIAN_SUPPORTED_LANGUAGES += zh_CN
SYMBIAN_LANG.zh_CN = 31
CONFIG += lrelease
CONFIG += embed_translations
LRELEASE_DIR=./translations
QM_FILES_RESOURCE_PREFIX=./translations
# ar,de,en,es,fr,it,ja,no,ru,sv,zh-CN
TRANSLATIONS += translations/GalaxyCalculator2_ar.ts \
                translations/GalaxyCalculator2_de.ts \
                translations/GalaxyCalculator2_en.ts \
                translations/GalaxyCalculator2_es.ts \
                translations/GalaxyCalculator2_fr.ts \
                translations/GalaxyCalculator2_it.ts \
                translations/GalaxyCalculator2_ja.ts \
                translations/GalaxyCalculator2_no.ts \
                translations/GalaxyCalculator2_ru.ts \
                translations/GalaxyCalculator2_sv.ts \
                translations/GalaxyCalculator2_zh-CN.ts
#
DISTFILES += \
    .appveyor.yml \
    help/About-Author_en.md \
    help/About_en.md \
    help/Help_en.md \
    src/3rdparty/gmp/README \
    src/3rdparty/gmp/gmp.COPYING \
    src/3rdparty/gmp/gmp.COPYING.LIB \
    src/3rdparty/gmp/gmp.README \
    src/3rdparty/gmp/mpfr.COPYING \
    src/3rdparty/gmp/mpfr.COPYING.LESSER \
    src/3rdparty/gmp/mpfr.README \
    CODE_OF_CONDUCT.md \
    README.md      \
    config/config.xml \
    desktop/CMakeLists.txt \
    desktop/GalaxyCalculator2.desktop \
    packages/com.lightwizzard.galaxycalculator2/data/README.md \
    packages/com.lightwizzard.galaxycalculator2/meta/installscript.qs \
    packages/com.lightwizzard.galaxycalculator2/meta/package.xml \
    scripts/build_script.cmd \
    scripts/build_script.sh \
    scripts/install.sh \
    scripts/upload.sh \
    usr/bin/README.md \
    usr/share/applications/GalaxyCalculator2.desktop \
    .github/workflows/main.yml \
    Doxyfile

# Ui Form(s)
FORMS       += src/MainWindow.ui
# Resources
RESOURCES   += GalaxyCalculator2.qrc
#
# gmp Unix
unix:LIBS           += -L$$PWD/src/3rdparty/gmp/lib/ -lgmp
unix:INCLUDEPATH    += $$PWD/src/3rdparty/gmp/include
unix:DEPENDPATH     += $$PWD/src/3rdparty/gmp/include
unix:PRE_TARGETDEPS += $$PWD/src/3rdparty/gmp/lib/libgmp.a
# mpfr Unix
unix: LIBS          += -L$$PWD/src/3rdparty/gmp/lib/ -lmpfr
unix:INCLUDEPATH    += $$PWD/src/3rdparty/gmp/include
unix:DEPENDPATH     += $$PWD/src/3rdparty/gmp/include
unix:PRE_TARGETDEPS += $$PWD/src/3rdparty/gmp/lib/libmpfr.a
# gmp Windows
win32:INCLUDEPATH += $$PWD/src/3rdparty/gmp/lib
win32:INCLUDEPATH += $$PWD/src/3rdparty/gmp/include
win32:DEPENDPATH  += $$PWD/src/3rdparty/gmp/include
#win32:LIBS        += $$PWD/src/3rdparty/gmp/lib/libgmp-10.lib
# C:/projects/GalaxyCalculator2/src/3rdparty/gmp/lib/libgmp-10.dll
win32:LIBS        += $$PWD/src/3rdparty/gmp/lib/libgmp-10.dll
#win32:LIBS        += -L$$PWD/src/3rdparty/gmp/lib/ -llibgmp-10
# mpfr Windows
win32:INCLUDEPATH += $$PWD/src/3rdparty/gmp/include
win32:DEPENDPATH  += $$PWD/src/3rdparty/gmp/include
#win32:LIBS        += $$PWD/src/3rdparty/gmp/lib/libmpfr-4.lib
win32:LIBS        += $$PWD/src/3rdparty/gmp/lib/libmpfr-4.dll
#win32:LIBS        += -L$$PWD/src/3rdparty/gmp/lib/ -llibmpfr-4
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
###############################################################################
message("*******************************************************************************")
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Qt resources can be found in the following locations:)
message(Documentation: $$[QT_INSTALL_DOCS])
message(Header files: $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary files (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Data files: $$[QT_INSTALL_DATA])
message(Translation files: $$[QT_INSTALL_TRANSLATIONS])
message(Settings: $$[QT_INSTALL_SETTINGS])
message(Examples: $$[QT_INSTALL_EXAMPLES])
message(Demonstrations: $$[QT_INSTALL_DEMOS])
message(Demonstrations: $$[QT_INSTALL_DEMOS])
message(OUT_PWD: $${OUT_PWD})
message(DESTDIR: $${DESTDIR})
message(OBJECTS_DIR: $${OBJECTS_DIR})
message(MOC_DIR: $${MOC_DIR})
message(UI_DIR: $${UI_DIR})
message(RCC_DIR: $${RCC_DIR})
message(INSTALLS: $${INSTALLS})
message(RC_FILE: $${RC_FILE})
message(DEFINES: $${DEFINES})
message(QMAKE_CXXFLAGS: $${QMAKE_CXXFLAGS})
message("*******************************************************************************")
################################ End of File ##################################
