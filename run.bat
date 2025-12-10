@echo off
echo -------------------------------
echo Running FirstProject v2.0...
echo -------------------------------

REM Go to the Debug folder where executables are generated
cd build\Debug

echo.
echo Running main program...
program.exe
echo.
echo Running abstract demo...
demo.exe
echo.
echo Running unit tests...
test_runner.exe

echo.
echo -------------------------------
echo All done!
pause
