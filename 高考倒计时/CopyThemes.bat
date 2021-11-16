@echo off
echo "remove res/themes"
for /d %%a in (res\\themes\\*.*)  do cd "%%a" & del *.* /q & cd ..  &  cd..& cd.. & rd %%a
echo "Copy themes to res/themes"
xcopy themes res\\themes /s /y
echo Done
pause