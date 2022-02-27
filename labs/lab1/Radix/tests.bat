@echo off

set Program="%~1"
if %Program%=="" (
    echo Please specify path to program
    exit /B 1
)

set Output="%TEMP%\output.txt"

rem Conversion from 2 to 36
%Program% 2 36 101010 > "%TEMP%\output.txt" || goto err
fc convertingNumber101010From2To36WithExpectation16.txt "%TEMP%\output.txt" > nul || goto err
echo Test #1: passed!

rem Conversion from 36 to 2
%Program% 36 2 16 > "%TEMP%\output.txt" || goto err
fc convertingNumber16From36To2WithExpectation101010.txt "%TEMP%\output.txt" > nul || goto err
echo Test #2: passed!

rem Conversion from 9 to 5
%Program% 9 5 871 > "%TEMP%\output.txt" || goto err
fc convertingNumber871From9To5WithExpectation10322.txt "%TEMP%\output.txt" > nul || goto err
echo Test #3: passed!

rem Conversion from 12 to 28
%Program% 12 28 8B71 > "%TEMP%\output.txt" || goto err
fc convertingNumber8B71From12To28WithExpectationJL9.txt "%TEMP%\output.txt" > nul || goto err
echo Test #4: passed!

rem Running without arguments
%Program% && goto err
echo Test #5: passed!

rem Erroneous argument
%Program% 2 37 1010 && goto err
echo Test #6: passed!

rem Int overflow
%Program% 10 37 2147483648 && goto err
echo Test #7: passed!

rem The absence of a symbol in the number system
%Program% 2 37 2000 && goto err
echo Test #8: passed!

rem The tests successful
echo All tests passed successfuly
exit /B 0

rem Tests failed
:err
echo Test failed
exit /B 1
