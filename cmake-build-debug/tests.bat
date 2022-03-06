@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргументов, задающего путь к программе
if %MyProgram%=="" (
    echo Please specify path to program
    exit /B 1
)

REM Компирование пустого файла
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test #1: passed!

REM Компирование не пустого файла
%MyProgram% nonEmptyFile.txt "%TEMP%\output.txt" || goto err
fc nonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test #2: passed!

REM Компирование не существующего файла
%MyProgram% missingFile.txt "%TEMP%\output.txt" && goto err
echo Test #3: passed!

REM Не указан output файл
%MyProgram% missingFile.txt && goto err
echo Test #4: passed!

REM Запускаем программу без аргументов
%MyProgram% && goto err
echo Test #5: passed!

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Тесты провалились
:err
echo Test failed
exit /B 1
