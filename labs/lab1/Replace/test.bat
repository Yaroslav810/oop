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
%PROGRAM% test-data\input-missing.txt %OUT% dog cat && goto err
echo Test #2: passed!

rem Replacing an empty file
%PROGRAM% test-data\empty.txt %OUT% '' '' || goto err
fc %OUT% test-data\empty-replace-empty-with-empty.txt > nul || goto err
echo Test #3: passed!

rem No replacements
%PROGRAM% test-data\fox.txt %OUT% dog2 cat || goto err
fc %OUT% test-data\fox-replace-dog2-with-cat.txt > nul || goto err
echo Test #4: passed!

rem Replacing an empty word
%PROGRAM% test-data\fox.txt %OUT% '' cat || goto err
fc %OUT% test-data\fox-replace-empty-with-cat.txt > nul || goto err
echo Test #5: passed!

rem Word replacement
%PROGRAM% test-data\fox.txt %OUT% dog cat || goto err
fc %OUT% test-data\fox-replace-dog-with-cat.txt > nul || goto err
echo Test #6: passed!

rem Big file
%PROGRAM% test-data\53043200-characters-a.txt %OUT% a BB || goto err
echo Test #7: passed!

rem The tests successful
echo All tests passed successfuly
exit /B 0

:err
echo Program testing failed
exit /B 1