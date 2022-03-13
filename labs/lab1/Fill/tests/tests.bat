@echo off

set PROGRAM="%~1"
if %PROGRAM%=="" (
    echo Please specify path to program
    exit /B 1
)

set OUT="%TEMP%\output.txt"

rem Running without arguments
%PROGRAM% > nul && goto err
echo Test #1: passed!

rem Input file is missing
%PROGRAM% input-missing.txt %OUT% > nul && goto err
echo Test #2: passed!

rem Filling in an empty file
%PROGRAM% empty.txt %OUT% || goto err
fc %OUT% empty-fill.txt > nul || goto err
echo Test #3: passed!

rem There is no start
%PROGRAM% not-start.txt %OUT% || goto err
fc %OUT% not-start-fill.txt > nul || goto err
echo Test #4: passed!

rem There is no border
%PROGRAM% not-border.txt %OUT% || goto err
fc %OUT% not-border-fill.txt > nul || goto err
echo Test #5: passed!

rem There two area
%PROGRAM% two-area.txt %OUT% || goto err
fc %OUT% two-area-fill.txt > nul || goto err
echo Test #6: passed!

rem A field with a hole
%PROGRAM% hole.txt %OUT% || goto err
fc %OUT% hole-fill.txt > nul || goto err
echo Test #7: passed!

rem The tests successful
echo All tests passed successfuly
exit /B 0

:err
echo Program testing failed
exit /B 1