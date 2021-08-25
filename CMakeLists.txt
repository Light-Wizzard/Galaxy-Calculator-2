cmake_minimum_required(VERSION 3.1.3)

project(GalaxyCalculator2)
#
set(TARGET ${CMAKE_PROJECT_NAME})
#
# Include GNUInstallDirs to get canonical paths
include(GNUInstallDirs)
#
set(APP_VERSION "0.1.0")
# [Using CMake with Qt 5](http://www.kdab.com/using-cmake-with-qt-5/)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#
# Specify where to find Qt
# If Qt5 is not installed on a system known location,
# or you want to use a specific version,
# or you are on Windows, QT_PREFIX_PATH should be specified
if(QT_PREFIX_PATH)
  list(APPEND CMAKE_PREFIX_PATH "${QT_PREFIX_PATH}")
endif()
#
if(WIN32)
    set(Python_ADDITIONAL_VERSIONS 3.8)
    set(PYTHON_INCLUDE_DIR C:/Python38/include)
    # src/3rdparty/gmp/lib
    #set(GMP_LIBRARIES /src/3rdparty/gmp/lib/libmpfr-4.dll src/3rdparty/gmp/lib/libgmp-10.dll)
    # Set path to our custom CMAKE scripts
    #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
    # Include Qt deployment helper function
    #include(windeployqt)
endif()

if(UNIX)
    set(Python_ADDITIONAL_VERSIONS 3.9)
    set(PYTHON_INCLUDE_DIR /usr/include/python3.9)
    # src/3rdparty/gmp/lib
    #set(GMP_LIBRARIES -L src/3rdparty/gmp/lib/ -lmpfr -lgmp)
endif()
#
find_package(Python3 COMPONENTS Interpreter Development)
find_package(PythonLibs REQUIRED)
#
set(GMP_INCLUDE_DIR src/3rdparty/gmp/include)
link_directories(src/3rdparty/gmp/lib)
#
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets
    Sql PrintSupport Network LinguistTools LinguistTools Concurrent)
#3DAnimation             Help                    QuickWidgets
#3DCore                  LinguistTools           RemoteObjects
#3DExtras                Location                RepParser
#3DInput                 Multimedia              Scxml
#3DLogic                 MultimediaWidgets       Sensors
#3DQuick                 Network                 SerialPort
#3DQuickAnimation        Nfc                     Sql
#3DQuickExtras           OpenGL                  Svg
#3DQuickInput            OpenGLExtensions        Test
#3DQuickRender           Positioning             TextToSpeech
#3DQuickScene2D          PositioningQuick        UiPlugin
#3DRender                PrintSupport            UiTools
#AndroidExtras           Qml                     WebChannel
#Bluetooth               Quick                   WebSockets
#Concurrent              QuickCompiler           WebView
#Core                    QuickControls2          Widgets
#Gamepad                 QuickTemplates2         Xml
#Gui                     QuickTest               XmlPatterns
# Libraries
set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets
    Qt5::Sql Qt5::PrintSupport Qt5::Network)
# Source
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/MyLocalization.cpp
    src/MyOrgSettings.cpp
    src/MySqlDbtModel.cpp
    src/MyTrinaryMath.cpp
    src/SimpleCrypt.cpp
    src/3rdparty/cpython/modules/exprtkmodule.cpp
    src/3rdparty/cpython/pyutil.cpp
    src/3rdparty/cpython/symboltableconverter.cpp
    src/3rdparty/cpython/types/pympreal.cpp
    src/3rdparty/io/serializer.cpp
    src/3rdparty/math/expressionparser.cpp
    src/3rdparty/math/fractiontest.cpp
    src/3rdparty/math/numberformat.cpp
    src/3rdparty/math/scripthandler.cpp
    src/3rdparty/math/symboltable.cpp
)
# UI
set(UI_SOURCES src/MainWindow.ui)
#
qt5_add_resources(SOURCES GalaxyCalculator2.qrc)
# https://github.com/pedrolcl/qt5-i18n
# not sure if I need to add en since it is the default
set(TS_FILES
    translations/GalaxyCalculator2_ar.ts
    translations/GalaxyCalculator2_de.ts
    translations/GalaxyCalculator2_en.ts
    translations/GalaxyCalculator2_es.ts
    translations/GalaxyCalculator2_fr.ts
    translations/GalaxyCalculator2_it.ts
    translations/GalaxyCalculator2_ja.ts
    translations/GalaxyCalculator2_no.ts
    translations/GalaxyCalculator2_ru.ts
    translations/GalaxyCalculator2_sv.ts
    translations/GalaxyCalculator2_zh_CN.ts
)
set(TRANSLATION_QM
    translations/GalaxyCalculator2_ar.qm
    translations/GalaxyCalculator2_de.qm
    translations/GalaxyCalculator2_en.qm
    translations/GalaxyCalculator2_es.qm
    translations/GalaxyCalculator2_fr.qm
    translations/GalaxyCalculator2_it.qm
    translations/GalaxyCalculator2_ja.qm
    translations/GalaxyCalculator2_no.qm
    translations/GalaxyCalculator2_ru.qm
    translations/GalaxyCalculator2_sv.qm
    translations/GalaxyCalculator2_zh_CN.qm
)#
if(QT_VERSION VERSION_LESS 5.15.0)
    qt5_add_translation(QM_FILES ${TS_FILES})
else()
    qt_add_translation(QM_FILES ${TS_FILES})
endif()
#
if(UNIX AND NOT APPLE)
    install(FILES ${TRANSLATION_QM} DESTINATION
        ${CMAKE_SOURCE_DIR}/translations)
endif()
#
#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} GalaxyCalculator2_en_US.ts)
# The qm files are generated in the build tree, but the qrc file is inside the
# source directory and the path to resources are relative to the location of
# the qrc file. We use configure_file() to copy the qrc file in the build
# directory such that it can find the qm translations files. The qrc file is
# copied if it doesn't exist in the destination or if it is modified.
#configure_file(GalaxyCalculator2.qrc ${CMAKE_BINARY_DIR} COPYONLY)
# Set CFLAGS for C/C++
set(CMAKE_C_FLAGS "-fPIE -fPIC -O2 -Wall -pedantic
    -fstack-protector-strong -D_FORTIFY_SOURCE=2")
set(CMAKE_CXX_FLAGS "-fPIE -fPIC -O2 -Wall -pedantic
    -fstack-protector-strong -D_FORTIFY_SOURCE=2")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
# Set LDFLAGS
set(CMAKE_SHARED_LINKER_FLAGS "-z noexecstack -z relro -z now")

# The Qt5Widgets_INCLUDES also includes the include directories
# for dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})
# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})
# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})
#
include_directories(${Qt5Widgets_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}
    ${GMP_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
# Executables fail to build with Qt 5 in the
# default configuration without -fPIE, added here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
#
# Generate necessary headers from .ui files. (qmake lets `uic` do this job.)
# hint from [Cross-platform Qt5 project using cmake]
# (http://stackoverflow.com/questions/21174586/
# cross-platform-qt5-project-using-cmake)
#
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})
#
#
# IMPORTANT: Adding generated headers to target as dependencies
# hint from [unable to include a ui_form header of QT5 in cmake]
# (http://stackoverflow.com/questions/16245147/
# unable-to-include-a-ui-form-header-of-qt5-in-cmake)
#
add_executable(${TARGET} ${SOURCES} ${UI_GENERATED_HEADERS}
    ${APP_RES} ${QT_RES})
#
# `target_link_libraries()` rather than `qt5_use_modules()`
# for CMake 2.8.11 or later hint from [CMake & QT5 - QT5_WRAP_UI
# not generating ui header files]
# (http://stackoverflow.com/questions/25875255/
# cmake-qt5-qt5-wrap-ui-not-generating-ui-header-files)
#
target_link_libraries(${TARGET} ${QT5_LIBRARIES} ${PYTHON_LIBRARIES} -lmpfr -lgmp)
#
install(TARGETS ${TARGET}
  RUNTIME DESTINATION /usr/bin
  LIBRARY DESTINATION /usr/lib
  ARCHIVE DESTINATION /usr/lib
)
# ***************************** End of cmake **********************************
