@echo off
set /P count=<BuildCount.txt
set /A count += 1
echo Current BuildCount:%count%
echo %count% > BuildCount.txt