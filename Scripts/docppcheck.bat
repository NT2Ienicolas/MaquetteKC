@echo OFF
rem Version 		: 1.0
rem modifications 	:

cd 	"..\sources"
cppcheck . -v --xml --enable=all --output-file=..\scripts\cppcheck.xml
