#!/bin/bash
#
# Last Update: 26 Auguest 2021
#
# shell?check -x scripts/install.sh
#
echo "install MacOS"
#
export PATH="/usr/local/sbin:/usr/local/opt/qt5/bin:$PATH";
brew cleanup;
brew config;
brew doctor || true;
brew install --cask cmake;
# installed updated warning: pkg-config openssl@1.1
brew install curl autoconf automake libtool;
brew install qt5 binutils create-dmg;
brew link qt5 --force;
export PATH="$(brew --prefix qt5)/bin:$PATH";
export CMAKE_PREFIX_PATH="$(brew --prefix qt5)";
#if ! softwareupdate --all --install --force; then
#    sudo rm -rf /Library/Developer/CommandLineTools;
#    sudo xcode-select --install;
#fi
xcode-select --install;
#    curl -fsS -o scripts/QtInstallerFramework-macOS.dmg "https://download.qt.io/official_releases/qt-installer-framework/$MY_QT_IF_VERSION/QtInstallerFramework-macOS-x86_64-$MY_QT_IF_VERSION.dmg";
#    # make it executable
#    chmod +x scripts/QtInstallerFramework-macOS.dmg;
# ****************************** End of install.sh ****************************
