@echo off
set CURDIR=%~dp0
echo %CURDIR%

echo ---------------------------------------------------------------------------------------------------------------------------
mklink /j %CURDIR%\logging_system D:\DEVELOPMENT\QT4\_MY__\my_lib\logging_system
mklink /j %CURDIR%\qp D:\DEVELOPMENT\QT4\_MY__\my_lib\qp\
mklink /j %CURDIR%\qp_test_model D:\DEVELOPMENT\QT4\_MY__\my_lib\qp_test_model\
mklink /j %CURDIR%\delegates D:\DEVELOPMENT\QT4\_MY__\my_lib\delegates\


echo ---------------------------------------------------------------------------------------------------------------------------
pause
