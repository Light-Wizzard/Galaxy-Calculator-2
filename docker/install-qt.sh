#!/bin/bash
# Aurélien Brooke - License: MIT

if [ -z "$QT_VERSION" ]; then
    echo "Please define the QT_VERSION environment variable as desired"
    exit 1
fi

if [ -z "$QT_PATH" ]; then
    echo "Please define the QT_PATH environment variable as desired"
    exit 1
fi

if [ -z "$QT_PLATFORM" ]; then
    echo "Please define the QT_PLATFORM environment variable as desired"
    exit 1
fi

set -e #quit on error

mkdir /tmp/qt
curl -Lo /tmp/qt/installer.run "https://download.qt.io/archive/qt/$(echo "${QT_VERSION}" | cut -d. -f 1-2)/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run"
QT_CI_PACKAGES=qt.qt5.$(echo "${QT_VERSION}" | tr -d .).${QT_PLATFORM} \
/tmp/build/bin/extract-qt-installer /tmp/qt/installer.run "$QT_PATH"
find "${QT_PATH}" -mindepth 1 -maxdepth 1 ! -name "${QT_VERSION}" -exec echo 'Cleaning Qt SDK: {}' \; -exec rm -r '{}' \;
rm -rf /tmp/qt
