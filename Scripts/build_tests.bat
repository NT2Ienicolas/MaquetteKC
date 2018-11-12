@ECHO OFF
rem RunTests.bat
rem Compile GoogleTest lib, tests projects and then run the tests of each projects

rem Version 		: 1.0
rem modifications 	: MLB /2017
SET SCRIPT_FOLDER=%CD%
SET SRC_FOLDER=%SCRIPT_FOLDER%\..\sources\

REM LOADING RSVARS FROM EMBARCADERO
CALL "C:\Program Files (x86)\Embarcadero\RAD Studio\12.0\bin\rsvars.bat"

REM COMPILE 
cd %SRC_FOLDER%\
call :CleanAndBuild

:END
exit

:CleanAndBuild
REM CLEAN AND BUILD
msbuild /t:clean /p:config=Debug
msbuild /t:make /p:config=Debug
goto:eof