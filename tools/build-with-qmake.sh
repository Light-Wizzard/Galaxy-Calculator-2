#! /bin/bash
# Galaxy Calculator 2
# 
# Last Update: 11 July 2021
#
# I cd to my project folder and run shell?check without the ?, it fails if I remove it in a file its checking, then add all files, commit and push, stops on fail
# cd /mnt/qnap-light-wizzard/workspace/WeBook/projects/WeBookServer && shell?check -x tools/build-with-qmake.sh && git add -A && git commit -m "Update" && git push -u origin master
#
# Original Code is from: https://github.com/linuxdeploy/QtQuickApp TheAssassin
#
# This file is Open Source and I tried my best to make it cut and paste, so I am adding the Environment Variables here
# as well as the OS installer.
# I got some of my concepts and code from this project https://github.com/patrickelectric/mini-qml I use his upload.sh
#
# I run Shell Check, it requires strict Bash Standards, so the extra code is to pass the test. 
# replace the ? in shell check
# In my Environment I define DEV_CURRENT_PROJECT="path to root of this project"; 
# and I define Shell Check DEV_SHELL_CHECK="shell?check"; again remove the "?", 
# you can not use that word in any doc you check, it is a Key Word used only by it, you define exceptions to your code.
# cd "${DEV_CURRENT_PROJECT}/tools"; "$DEV_SHELL_CHECK" -x build-with-qmake.sh
# If you see no output, you have no warnings or errors.
# You can automate the checking of your scripts this way.
#
# I will not minimize this code, but if I did, you would understand why I put ";" to terminate all lines requiring them.
# 
# Debug Information, not always a good idea when not debugging, and thanks to the TheAssassin, this is now working.
# These are the setting you might want to change
declare -ix DEBUGGING;         DEBUGGING=0;          # Set 1=True and 0=False
declare -ix EXIT_ON_UNDEFINED; EXIT_ON_UNDEFINED=0;  # Set 1=True and 0=False
# Below should be agnostic
# I use a Variable so I can turn it off on exit
if [ "${DEBUGGING}" -eq 1 ]; then set -x; fi
# Exit on error
set -e;
#
# If not defined it will use this as a default
if [ -z "${BIN_PRO_RES_NAME+x}" ]; then
    echo -e "Add BIN_PRO_RES_NAME to your Travis Settings Environment Variable with a value from Github value for Binary, pro, and resource Name ";
    if [ "${EXIT_ON_UNDEFINED}" -eq 1 ]; then exit 1; fi    
fi
# TRAVIS_REPO_SLUG should always have your GITHUB_USERNAME as the first part / GITHUB_PROJECT, so I split them to use later.
if [ -z "${GITHUB_USERNAME+x}" ] || [ -z "${GITHUB_PROJECT}" ]; then
    OLD_IFS="$IFS"; IFS='/'; read -ra repo_parts <<< "$TRAVIS_REPO_SLUG"; IFS="$OLD_IFS";
    declare -x GITHUB_PROJECT;
    GITHUB_USERNAME="${repo_parts[0]}";  GITHUB_PROJECT="${repo_parts[1]}";
fi
# Set our Artifacts for later
#
export ARTIFACT_APPIMAGE="${BIN_PRO_RES_NAME}-x86_64.AppImage";
export ARTIFACT_ZSYNC="${BIN_PRO_RES_NAME}-x86_64.AppImage.zsync";
export ARTIFACT_QIF="${BIN_PRO_RES_NAME}-Linux-Installer";
# 
# use RAM disk if possible (as in: not building on CI system like Travis, and RAM disk is available)
declare TEMP_BASE;
if [ "$CI" == "" ] && [ -d "/dev/shm" ]; then TEMP_BASE="/dev/shm"; else TEMP_BASE="/tmp"; fi
#
echo "Make Temp Foler";
#
# building in temporary directory to keep system clean
BUILD_DIR="$(mktemp -d -p "$TEMP_BASE" "${BIN_PRO_RES_NAME}-build-XXXXXX")";
# 
# make sure to clean up build dir, even if errors occur
function cleanup()
{
    if [ -d "$BUILD_DIR" ]; then rm -rf "$BUILD_DIR"; fi
    if [ "${DEBUGGING}" -eq 1 ]; then set +x; fi
}
trap "cleanup; exit;" SIGINT SIGTERM
#trap cleanup EXIT;
# 
# store repo root as variable
REPO_ROOT="$(readlink -f "$(dirname "$(dirname "$0")")")";
OLD_CWD="$(readlink -f .)";
# 
# switch to build dir
pushd "$BUILD_DIR";
# 
# configure build files with qmake
qmake -makefile "${REPO_ROOT}";
# 
# build project and install files into AppDir
make -j"$(nproc)";
make install INSTALL_ROOT="AppDir";
# 
# Renamed -*x86_64.AppImage.zsync not sure what the * does, but if it does version numbers, I do not want it.
export UPDATE_INFORMATION="gh-releases-zsync|${GITHUB_USERNAME}|${GITHUB_PROJECT}|continuous|${ARTIFACT_ZSYNC}";
# 
# I will have an Example of using LinuxDeploy and LinuxDeployQt
#
declare -i LINUX_DEPLOY_USING;
# Set to 0 to enable LinuxDeploy
LINUX_DEPLOY_USING=0;
#
if [ "${LINUX_DEPLOY_USING}" -eq 0 ]; then
    # make sure Qt plugin finds QML sources so it can deploy the imported files
    export QML_SOURCES_PATHS="${REPO_ROOT}/qml";
    # now, build AppImage using linuxdeploy and linuxdeploy-plugin-qt
    # download linuxdeploy and its Qt plugin
    wget -c -nv "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage";
    wget -c -nv "https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage";
    # 
    # make them executable
    chmod +x linuxdeploy*.AppImage;
    # 
    # AppImage update informatoin
    # 
    # QtQuickApp does support "make install", but we don't use it because we want to show the manual packaging approach in this example
    # initialize AppDir, bundle shared libraries, add desktop file and icon, use Qt plugin to bundle additional resources, and build AppImage, all in one command
    ./linuxdeploy-x86_64.AppImage --appdir "AppDir" -e "${BIN_PRO_RES_NAME}" -i "${REPO_ROOT}/resources/${BIN_PRO_RES_NAME}.png" -d "${REPO_ROOT}/resources/${BIN_PRO_RES_NAME}.desktop" --plugin qt --output appimage;
    # 
    chmod +x "${BIN_PRO_RES_NAME}"*.AppImage*;
    mv "${BIN_PRO_RES_NAME}"*.AppImage* "$OLD_CWD";
    # Pop Directory for Qt Installer Framework
fi
# Set to 1 to enable LinuxDeployQt
LINUX_DEPLOY_USING=1;
if [ "${LINUX_DEPLOY_USING}" -eq 1 ]; then
    echo "Downloading LinuxDeployQt";
    wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage";
    chmod a+x "linuxdeployqt-continuous-x86_64.AppImage";
    unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH;
    export VERSION="travis";
    # Move our executable into the bin folder
    if [ -f "${BIN_PRO_RES_NAME}" ]; then
        mkdir -p "${TRAVIS_BUILD_DIR}/usr/bin";
        cp -pv "${BIN_PRO_RES_NAME}" "${TRAVIS_BUILD_DIR}/usr/bin";
        ls "${TRAVIS_BUILD_DIR}/usr/bin";
    fi
    #
    echo "Starting linuxdeployqt-continuous-x86_64.AppImage";
    ./linuxdeployqt-continuous-x86_64.AppImage "${TRAVIS_BUILD_DIR}/usr/share/applications/${BIN_PRO_RES_NAME}.desktop" -extra-plugins=iconengines,imageformats -verbose=2 -qmldir="${TRAVIS_BUILD_DIR}/qml/" -appimage;
    chmod +x "${BIN_PRO_RES_NAME}"*.AppImage*;
    ls;
    # Move them
    chmod +x "${BIN_PRO_RES_NAME}"*.AppImage*;
    mv "${BIN_PRO_RES_NAME}"*.AppImage* "$OLD_CWD";
    echo "Finished linuxdeployqt-continuous-x86_64.AppImage"
fi
#
# Pop Directory for Qt Installer Framework
popd;
# 
echo "Preparing for Qt Installer Framework";
# 
# Instead of trying to install Qt Installer Framework, I use 7zip to compress the bin folder
# I will use a relative path from TRAVIS_BUILD_DIR
# I hard code the path
mkdir -pv qtinstallerframework;
7z e "${QIF_ARCHIVE}" -o./qtinstallerframework;
chmod -R +x ./qtinstallerframework;
# 
# Copy all the files that Qt Installer Framework needs
ls "${TRAVIS_BUILD_DIR}";
#
# Copy both AppImages to where Qt Installer Framework needs them
if [ -f "${TRAVIS_BUILD_DIR}/${ARTIFACT_APPIMAGE}" ]; then
    cp -pv "${TRAVIS_BUILD_DIR}/${ARTIFACT_APPIMAGE}" "${QIF_PACKAGE_URI}/data";
    cp -pv "${TRAVIS_BUILD_DIR}/${ARTIFACT_ZSYNC}" "${QIF_PACKAGE_URI}/data";
else
    echo -e "Missing ${BUILD_DIR}/${ARTIFACT_APPIMAGE} ";
fi
# The packages/${QIF_PACKAGE_URI}/meta/installscript.qs creates this: cp -v "resources/${BIN_PRO_RES_NAME}.desktop" "${QIF_PACKAGE_URI}";
cp -v "${TRAVIS_BUILD_DIR}/resources/${BIN_PRO_RES_NAME}.png" "${QIF_PACKAGE_URI}/data";
cp -v "${TRAVIS_BUILD_DIR}/resources/${BIN_PRO_RES_NAME}.svg" "${QIF_PACKAGE_URI}/data";
cp -v "${TRAVIS_BUILD_DIR}/resources/${BIN_PRO_RES_NAME}.ico" "${QIF_PACKAGE_URI}/data";
rsync -Ravr "${TRAVIS_BUILD_DIR}/usr/share/icons" "${QIF_PACKAGE_URI}/icons";
ls "${QIF_PACKAGE_URI}/data";
# 
echo "Running Qt Installer Framework";
./qtinstallerframework/binarycreator -c "${TRAVIS_BUILD_DIR}/config/config.xml" -p "${TRAVIS_BUILD_DIR}/packages" "${ARTIFACT_QIF}";
#
echo -e "Completed build-with-qmake.sh";
################################ End of File ##################################
