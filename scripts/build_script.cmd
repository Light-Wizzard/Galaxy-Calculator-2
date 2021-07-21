write-host "build_script Windows" 
# 
cd %APPVEYOR_BUILD_FOLDER% 
mkdir build 
cd build 
mkdir AppDir 
if %platform%==x86 qmake -v && qmake ..\%BIN_PRO_RES_NAME%.pro CONFIG+=%configuration% CONFIG+=c++11 DESTDIR=%cd% && mingw32-make && mingw32-make install INSTALL_ROOT=AppDir 
if %platform%==x64 qmake -v && qmake ..\%BIN_PRO_RES_NAME%.pro CONFIG+=%configuration% CONFIG+=c++11 DESTDIR=%cd% && mingw32-make && mingw32-make install INSTALL_ROOT=AppDir 
write-host "after_build Windows" 
dir 
copy "%APPVEYOR_BUILD_FOLDER%\build\%BIN_PRO_RES_NAME%.exe" "AppDir\%BIN_PRO_RES_NAME%-%MY_OS%-%CONFIGURATION%-%platform%.exe" 
windeployqt "AppDir/%BIN_PRO_RES_NAME%.exe" --verbose=2 
#for %%I in (%PRJLIBS%) do copy %PRJLIBDIR%\%%I AppDir\ 
7z a -tzip "%BIN_PRO_RES_NAME%-%MY_OS%-%CONFIGURATION%-%platform%.zip" AppDir -r 
copy "%APPVEYOR_BUILD_FOLDER%\build\%BIN_PRO_RES_NAME%-%MY_OS%-%CONFIGURATION%-%platform%.zip" "%APPVEYOR_BUILD_FOLDER%\ 
echo APPVEYOR_BUILD_FOLDER=%APPVEYOR_BUILD_FOLDER% 
#xcopy /s /e /f "%APPVEYOR_BUILD_FOLDER%\build\AppDir" "%APPVEYOR_BUILD_FOLDER%\%QIF_PACKAGE_URI%" 
#C:\Qt\QtIFW-3.1.1\bin\binarycreator.exe --offline-only -c "%APPVEYOR_BUILD_FOLDER%\config\config.xml" -p "%APPVEYOR_BUILD_FOLDER%\packages" "%BIN_PRO_RES_NAME%-Windows-Installer.exe" 
#7z a -tzip "%BIN_PRO_RES_NAME%-Windows-Installer.zip" "%BIN_PRO_RES_NAME%-Windows-Installer.exe" 
C:\Qt\Tools\QtInstallerFramework\binarycreator.exe --offline-only -c "%APPVEYOR_BUILD_FOLDER%\config\config.xml" -p "%APPVEYOR_BUILD_FOLDER%\packages" "%BIN_PRO_RES_NAME%-Windows-Installer.exe" 
copy *.zip %APPVEYOR_BUILD_FOLDER% 
copy *.exe %APPVEYOR_BUILD_FOLDER% 
cd %APPVEYOR_BUILD_FOLDER% 
echo Current Path is %cd% 
dir 
write-host "Completed-Build Windows"
