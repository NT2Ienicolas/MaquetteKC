@ECHO OFF
rem Compile 
rem Version 		: 1.0
rem modifications 	: MLB /2017
SET SCRIPT_FOLDER=%CD%
SET SRC_FOLDER=%SCRIPT_FOLDER%\..\sources\

REM LOADING RSVARS FROM EMBARCADERO
CALL "C:\Program Files\Embarcadero\RAD Studio\12.0\bin\rsvars.bat"

REM COMPILE 
cd %SRC_FOLDER%\
C:\Windows\Microsoft.NET\Framework\v4.0.30319\msbuild /t:clean /p:config=Debug
C:\Windows\Microsoft.NET\Framework\v4.0.30319\msbuild /t:make /p:config=Debug
cd 	"..\scripts"

