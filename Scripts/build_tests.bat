@ECHO OFF
rem Compile 
rem Version 		: 1.0
rem modifications 	: MLB /2017
SET SCRIPT_FOLDER=%CD%
SET SRC_FOLDER=%SCRIPT_FOLDER%\..\sources\

REM LOADING RSVARS FROM EMBARCADERO
CALL "C:\Program Files (x86)\Embarcadero\RAD Studio\12.0\bin\rsvars.bat"

REM COMPILE 
cd %SRC_FOLDER%\
msbuild /t:clean /p:config=Debug
msbuild /t:make /p:config=Debug
cd 	"..\scripts"

