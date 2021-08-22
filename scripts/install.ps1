If ($env:PLATFORM -eq "x64" -And $env:MY_COMPILER -eq "Qt") {
   Write-Host "install Windows QT x64" -ForegroundColor DarkGreen
   $env:Path += ";C:\Qt\Tools\$env:MY_QT_MINGW64\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW64\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW64"
   $env:Path += ";C:\Python$env:MY_PYTHON_VER-x64"
   $env:Path += ";C:\MINGW\bin\"
   $env:MY_QT_BAT = "C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW64\bin\qtenv2.bat"
   $env:MY_VS_BAT = "C:\PROGRA~2\Microsoft^ Visual^ Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars64.bat"
   Invoke-Expression $env:MY_QT_BAT
   Invoke-Expression $env:MY_VS_BAT
   #Invoke-Expression "C:\PROGRA~2\Microsoft Visual Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars64.bat"
   #iex "C:\PROGRA~2\Microsoft Visual Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars64.bat"
   #"C:\PROGRA~2\Microsoft Visual Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars64.bat"
}
Else {
   Write-Host "install Windows QT x86" -ForegroundColor DarkGreen
   $env:Path += ";C:\Qt\Tools\$env:MY_QT_MINGW32\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW32\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW32"
   $env:Path += ";C:\Python$env:MY_PYTHON_VER"
   $env:Path += ";C:\MINGW\bin\"
   $env:MY_QT_BAT = "C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW64\bin\qtenv2.bat"
   $env:MY_VS_BAT = "C:\PROGRA~2\Microsoft Visual Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars32.bat"
   Invoke-Expression $env:MY_QT_BAT
   Invoke-Expression $MY_VS_BAT
}
If ($env:PLATFORM -eq "x64" -And $env:MY_COMPILER -eq "Vs") {
   $env:Path += ";C:\Qt\Tools\$env:MY_QT_MINGW64\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\msvc$env:MY_VS_VERSION_64\bin"
   $env:Path += ";C:\Python$env:MY_PYTHON_VER-x64"
   $env:Path += ";C:\MINGW\bin\"
   Invoke-Expression "C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW64\bin\qtenv2.bat"
   Invoke-Expression "C:\PROGRA~2\Microsoft Visual Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars64.bat"
}
Else {
   $env:Path += ";C:\Qt\Tools\$env:MY_QT_MINGW32\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW32\bin"
   $env:Path += ";C:\Qt\$env:MY_QT_VERSION\$env:MY_QT_MINGW32"
   $env:Path += ";C:\Python$env:MY_PYTHON_VER"
   $env:Path += ";C:\MINGW\bin\"
   Invoke-Expression "C:\Qt\$env:MY_QT_VERSION\msvc$env:MY_VS_VERSION\bin\qtenv2.bat"
   Invoke-Expression "C:\PROGRA~2\Microsoft Visual Studio\$env:MY_VS_VERSION\Community\VC\Auxiliary\Build\vcvars32.bat"
}
