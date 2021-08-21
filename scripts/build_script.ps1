If ($env:PLATFORM -eq "x64" -And $env:MY_COMPILER -eq "Qt") {
    Write-Host "build_script Windows QT x64" -ForegroundColor DarkGreen
    Set-Location -Path $env:APPVEYOR_BUILD_FOLDER
    New-Item -Path 'build' -ItemType Directory
    Set-Location -Path build
    $env:INSTALL_ROOT=AppDir
    $env:BUILD_ROOT=$env:APPVEYOR_BUILD_FOLDER\build
    Invoke-Expression "qmake -r -Wall -Wlogic -Wparser $env:APPVEYOR_BUILD_FOLDER\$env:MY_BIN_PRO_RES_NAME.pro -o AppDir CONFIG+=$env:CONFIGURATION CONFIG+=c++11 CONFIG+=x86_64 DESTDIR=AppDir $env:APPVEYOR_BUILD_FOLDER\build"
    Write-Host "build_script Windows QT x64 mingw32-make -j 2"
    Invoke-Expression "mingw32-make -j 2"
    Write-Host "build_script Windows QT x64 mingw32-make install INSTALL_ROOT=AppDir"
    Invoke-Expression "mingw32-make install INSTALL_ROOT=AppDir"
}
Else {
    Write-Host "build_script Windows QT x86" -ForegroundColor DarkGreen
    Set-Location -Path $env:APPVEYOR_BUILD_FOLDER
    New-Item -Path 'build' -ItemType Directory
    Set-Location -Path build
    $env:INSTALL_ROOT=AppDir
    $env:BUILD_ROOT=$env:APPVEYOR_BUILD_FOLDER\build
    Invoke-Expression "qmake -r -Wall -Wlogic -Wparser -spec win32-g++ $env:APPVEYOR_BUILD_FOLDER\$env:MY_BIN_PRO_RES_NAME.pro -o AppDir CONFIG+=$env:CONFIGURATION CONFIG+=c++11 CONFIG+=x86 DESTDIR=AppDir $env:APPVEYOR_BUILD_FOLDER\build"
    Invoke-Expression "mingw32-make -j 2"
    Invoke-Expression "mingw32-make install INSTALL_ROOT=AppDir"
}

If ($env:PLATFORM -eq "x64" -And $env:MY_COMPILER -eq "Vs") {
    Write-Host "build_script Windows VS x64" -ForegroundColor DarkGreen
    Set-Location -Path $env:APPVEYOR_BUILD_FOLDER
    New-Item -Path 'build' -ItemType Directory
    Set-Location -Path build
    $env:INSTALL_ROOT=AppDir
    $env:BUILD_ROOT=$env:APPVEYOR_BUILD_FOLDER\build
    $env:MY_QT_MAKE="qmake -r -Wall -Wlogic -Wparser $env:APPVEYOR_BUILD_FOLDER%\$env:MY_BIN_PRO_RES_NAME.pro CONFIG+=$env:CONFIGURATION CONFIG+=c++11 CONFIG+=x86_64 DESTDIR=AppDir $env:APPVEYOR_BUILD_FOLDER\build"
    Invoke-Expression $env:MY_QT_MAKE
    $env:MY_QT_MAKE="mmake"
    Invoke-Expression $env:MY_QT_MAKE
    $env:MY_QT_MAKE="mmake install INSTALL_ROOT=AppDir"
    Invoke-Expression $env:MY_QT_MAKE
}
Else {
    Write-Host "build_script Windows VS x86" -ForegroundColor DarkGreen
    Set-Location -Path $env:APPVEYOR_BUILD_FOLDER
    New-Item -Path 'build' -ItemType Directory
    Set-Location -Path build
    $env:INSTALL_ROOT=AppDir
    $env:BUILD_ROOT=$env:APPVEYOR_BUILD_FOLDER\build
    $env:MY_QT_MAKE="qmake -r -Wall -Wlogic -Wparser -spec win32-g++ $env:APPVEYOR_BUILD_FOLDER\$env:MY_BIN_PRO_RES_NAME.pro CONFIG+=$env:CONFIGURATION CONFIG+=c++11 CONFIG+=x86 DESTDIR=AppDir $env:APPVEYOR_BUILD_FOLDER\build"
    Invoke-Expression $env:MY_QT_MAKE
    $env:MY_QT_MAKE="mmake"
    Invoke-Expression $env:MY_QT_MAKE
    $env:MY_QT_MAKE="mmake install INSTALL_ROOT=AppDir"
    Invoke-Expression $env:MY_QT_MAKE
}

$currentDirectory = [System.AppDomain]::CurrentDomain.BaseDirectory.TrimEnd('\')
if ($currentDirectory -eq $PSHOME.TrimEnd('\')) {
    $currentDirectory = $PSScriptRoot
}
Write-Host "After Windows build $env:currentDirectory" -ForegroundColor DarkGreen
Get-ChildItem -Path AppDir
Copy-Item "C:\Qt\Tools\QtCreator\bin\plugins\platforms\*" -Destination "AppDir" -Recurse
Invoke-Expression "windeployqt AppDir\$env:MY_BIN_PRO_RES_NAME.exe --verbose=2"
Invoke-Expression "7z a -tzip $env:MY_BIN_PRO_RES_NAME-$env:MY_OS-$env:CONFIGURATION-$env:PLATFORM.zip AppDir -r"
Copy-Item "$env:APPVEYOR_BUILD_FOLDER\build\$env:MY_BIN_PRO_RES_NAME-$env:MY_OS-$env:CONFIGURATION-$env:PLATFORM.zip" -Destination "$env:APPVEYOR_BUILD_FOLDER\"
Copy-Item "*.zip" -Destination "$env:APPVEYOR_BUILD_FOLDER\"
Set-Location -Path $env:APPVEYOR_BUILD_FOLDER
Write-Host "Completed-Build Windows" -ForegroundColor DarkGreen
