#!/bin/bash
# Galaxy Calculator 2
# 
# Last Update: 20 July 2021
#
# shell?check -x scripts/build-script.sh
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
echo build_script Unix
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
    echo -e "Add BIN_PRO_RES_NAME to your Appveyor Settings Environment Variable with a value from Github value for Binary, pro, and resource Name ";
    if [ "${EXIT_ON_UNDEFINED}" -eq 1 ]; then exit 1; fi    
fi
# APPVEYOR_REPO_NAME should always have your GITHUB_USERNAME as the first part / GITHUB_PROJECT, so I split them to use later.
if [ -z "${GITHUB_USERNAME+x}" ] || [ -z "${GITHUB_PROJECT}" ]; then
    OLD_IFS="$IFS"; IFS='/'; read -ra repo_parts <<< "$APPVEYOR_REPO_NAME"; IFS="$OLD_IFS";
    declare -x GITHUB_PROJECT;
    GITHUB_USERNAME="${repo_parts[0]}";  GITHUB_PROJECT="${repo_parts[1]}";
fi
# Set our Artifacts for later
#
export ARTIFACT_APPIMAGE="${BIN_PRO_RES_NAME}-x86_64.AppImage";
export ARTIFACT_ZSYNC="${BIN_PRO_RES_NAME}-x86_64.AppImage.zsync";
export ARTIFACT_QIF="${BIN_PRO_RES_NAME}-Linux-Installer";
# 
# use RAM disk if possible (as in: not building on CI system like Appveyor, and RAM disk is available)
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
# source ${HOME}/venv${PYTHON_VER}/bin/activate
if [[ "$APPVEYOR_BUILD_WORKER_IMAGE" = "${MY_OS}" ]] && [[ "$PLATFORM" = "x86" ]]; then
    export PATH="${HOME}/Qt/${QT5_VERSION}/gcc_32/bin:${HOME}/Qt/${QT5_VERSION}/gcc_32/lib:${HOME}/Qt/${QT5_VERSION}/gcc_32/include:$PATH";
    export PATH="/usr/lib/python${PYTHON_VER}:/usr/include/python${PYTHON_VER}:$PATH";
    # export PATH=${HOME}/venv${PYTHON_VER}:${HOME}/venv${PYTHON_VER}/bin:${HOME}/venv${PYTHON_VER}/lib:$PATH
fi
#
if [[ "$APPVEYOR_BUILD_WORKER_IMAGE" = "${MY_OS}" ]] && [[ "$PLATFORM" = "x64" ]]; then
    export PATH="${HOME}/Qt/${QT5_VERSION}/gcc_64/bin:${HOME}/Qt/${QT5_VERSION}/gcc_64/lib:${HOME}/Qt/${QT5_VERSION}/gcc_64/include:$PATH";
    export PATH="/usr/lib/python${PYTHON_VER}:/usr/include/python${PYTHON_VER}:$PATH";
    # export PATH=${HOME}/venv${PYTHON_VER}:${HOME}/venv${PYTHON_VER}/bin:${HOME}/venv${PYTHON_VER}/lib:$PATH
fi
#
if [[ $APPVEYOR_BUILD_WORKER_IMAGE = "${MY_OS}" ]]; then
    echo "PATH=$PATH";
    # 
    # configure build files with qmake
    qmake "${REPO_ROOT}";
    # 
    # build project and install files into AppDir
    make -j"$(nproc)";
    make install INSTALL_ROOT="AppDir";
fi
#
#
# make sure Qt plugin finds QML sources so it can deploy the imported files
if [ -d "${REPO_ROOT}/qml" ]; then
    export QML_SOURCES_PATHS="${REPO_ROOT}/qml";
fi
# now, build AppImage using linuxdeploy and linuxdeploy-plugin-qt
# download linuxdeploy and its Qt plugin
if [[ "$APPVEYOR_BUILD_WORKER_IMAGE" = "${MY_OS}" ]]; then
    wget -c -nv  https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage; 
    wget -c -nv  https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage; 
    # make them executable
    chmod +x linuxdeploy*.AppImage; 
    # QtQuickApp does support "make install", but we don't use it because we want to show the manual packaging approach in this example
    # initialize AppDir, bundle shared libraries, add desktop file and icon, use Qt plugin to bundle additional resources, and build AppImage, all in one command
    ./linuxdeploy-x86_64.AppImage --appdir=AppDir -i "${REPO_ROOT}/desktop/${BIN_PRO_RES_NAME}.svg" -d "${REPO_ROOT}/desktop/${BIN_PRO_RES_NAME}.desktop" --plugin qt --output appimage;
    7z a -tzip -r "${BIN_PRO_RES_NAME}-$MY_OS-$CONFIGURATION-$PLATFORM.zip" AppDir;
    cp ./*.zip ../;
    # $QT5_64/Tools/QtInstallerFramework/binarycreator.exe --offline-only -c "$APPVEYOR_BUILD_FOLDER/config/config.xml" -p "$APPVEYOR_BUILD_FOLDER\packages" "$BIN_PRO_RES_NAME-Windows-Installer.exe"
fi
# 
# 
# AppImage update informatoin
# 
# 
chmod +x "${BIN_PRO_RES_NAME}"*.AppImage*;
mv "${BIN_PRO_RES_NAME}"*.AppImage* "$OLD_CWD";
# Pop Directory for Qt Installer Framework
#
# Pop Directory for Qt Installer Framework
popd;
# 
echo "Preparing for Qt Installer Framework";
# 
# Instead of trying to install Qt Installer Framework, I use 7zip to compress the bin folder
# I will use a relative path from APPVEYOR_BUILD_FOLDER
# I hard code the path
#mkdir -pv qtinstallerframework;
#7z e "${QIF_ARCHIVE}" -o./qtinstallerframework;
#chmod -R +x ./qtinstallerframework;
# 
# Copy all the files that Qt Installer Framework needs
ls "${APPVEYOR_BUILD_FOLDER}";
#
# Copy both AppImages to where Qt Installer Framework needs them
if [ -f "${APPVEYOR_BUILD_FOLDER}/${ARTIFACT_APPIMAGE}" ]; then
    cp -pv "${APPVEYOR_BUILD_FOLDER}/${ARTIFACT_APPIMAGE}" "${QIF_PACKAGE_URI}/data";
    cp -pv "${APPVEYOR_BUILD_FOLDER}/${ARTIFACT_ZSYNC}" "${QIF_PACKAGE_URI}/data";
else
    echo -e "Missing ${BUILD_DIR}/${ARTIFACT_APPIMAGE} ";
fi
# The packages/${QIF_PACKAGE_URI}/meta/installscript.qs creates this: cp -v "desktop/${BIN_PRO_RES_NAME}.desktop" "${QIF_PACKAGE_URI}";
cp -v "${APPVEYOR_BUILD_FOLDER}/desktop/${BIN_PRO_RES_NAME}.png" "${QIF_PACKAGE_URI}/data";
cp -v "${APPVEYOR_BUILD_FOLDER}/desktop/${BIN_PRO_RES_NAME}.svg" "${QIF_PACKAGE_URI}/data";
cp -v "${APPVEYOR_BUILD_FOLDER}/desktop/${BIN_PRO_RES_NAME}.ico" "${QIF_PACKAGE_URI}/data";
rsync -Ravr "${APPVEYOR_BUILD_FOLDER}/usr/share/icons" "${QIF_PACKAGE_URI}/icons";
ls "${QIF_PACKAGE_URI}/data";
# 
echo "Running Qt Installer Framework";
#./qtinstallerframework/binarycreator -c "${APPVEYOR_BUILD_FOLDER}/config/config.xml" -p "${APPVEYOR_BUILD_FOLDER}/packages" "${ARTIFACT_QIF}";
#
echo -e "Completed build-script.sh";
################################ End of File ##################################
