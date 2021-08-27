#!/bin/bash
#
# Last Update: 27 Auguest 2021
#
# shell?check -x scripts/install_mac.sh
#
echo "install MacOS"
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
