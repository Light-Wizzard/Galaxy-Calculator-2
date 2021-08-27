#!/bin/bash
#
# Last Update: 27 Auguest 2021
#
# shell?check -x scripts/install_mac.sh
#
echo "install MacOS"
#
# Set Path
PATH="/usr/local/sbin:/usr/local/opt/qt@5/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:$PATH";
PATH="/usr/local/opt/openssl@1.1/bin:/usr/local/opt/binutils/bin:$PATH";
PATH="/usr/local/opt/libtool/libexec/gnubin:/usr/local/opt/curl/bin:$PATH";
PATH="${HOME}/venv${MY_PYTHON_VER}:${HOME}/venv${MY_PYTHON_VER}/bin:$PATH";
PATH="${HOME}/venv${MY_PYTHON_VER}/include:$PATH";
PATH="${HOME}/venv${MY_PYTHON_VER}/lib:$HOME/Qt/${MY_QT_VERSION}:$PATH";
PATH="/usr/local/opt/qt5/bin:$PATH";
PATH="${HOME}/Qt/${MY_QT_VERSION}/clang_64/bin:$PATH";
export PATH;
#
brew cleanup;
brew config;
brew doctor || true;
brew install --cask cmake;
# installed updated warning: pkg-config openssl@1.1
brew install curl autoconf automake libtool qt5 binutils create-dmg;
brew link qt5 --force;
#curl -fsS -o scripts/QtInstallerFramework-macOS.dmg "https://download.qt.io/official_releases/qt-installer-framework/$MY_QT_IF_VERSION/QtInstallerFramework-macOS-x86_64-$MY_QT_IF_VERSION.dmg";
# make it executable
#chmod +x scripts/QtInstallerFramework-macOS.dmg;
# ****************************** End of install.sh ****************************
