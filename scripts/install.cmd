write-host "install Windows"
#
if %platform%==x86 set PATH=%PY_DIR_32%;%PY_DIR_32%\Scripts;%PATH%
if %platform%==x86 set PATH=%MINGW_32%\bin;%QT5_32%\bin;%PATH%
if %platform%==x64 set PATH=%PY_DIR_64%;%PY_DIR_64%\Scripts;%PATH%
if %platform%==x64 set PATH=%MINGW_64%\bin;%QT5_64%\bin;%PATH%
if %platform%==x86 call "%QT5_32%\bin\qtenv2.bat"
if %platform%==x64 call "%QT5_64%\bin\qtenv2.bat"
if %platform%==x86 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
if %platform%==x64 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
