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

rem Invalid mode
%PROGRAM% cript empty.txt %OUT% 20 > nul && goto err
echo Test #3: passed!

rem Invalid key
%PROGRAM% decrypt empty.txt %OUT% CAT > nul && goto err
echo Test #4: passed!

rem Filling in an empty file
%PROGRAM% crypt empty.txt %OUT% 10 || goto err
fc %OUT% empty-crypt.txt > nul || goto err
echo Test #5: passed!

rem Encrypted @#& with code 10, expectation JEQ
%PROGRAM% crypt "@#&.txt" %OUT% 10 || goto err
fc %OUT% "encrypt-@#&-code-10-with-expectation-JEQ.txt" > nul || goto err
echo Test #6: passed!

rem Decrypted JEQ with code 10, expectation @#&
%PROGRAM% decrypt "JEQ.txt" %OUT% 10 || goto err
fc %OUT% "decrypt-JEQ-code-10-with-expectation-@#&.txt" > nul || goto err
echo Test #7: passed!

rem The tests successful
echo All tests passed successfuly
exit /B 0

:err
echo Program testing failed
exit /B 1