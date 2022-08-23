cd %cd%

g++ "src/main.cpp" "src/ArgManager/argList.cpp" "src/ArgManager/treatment.cpp" "src/ArgManager/userinterface.cpp" "src/DrawingMethods/drawUtilities.cpp" "src/DrawingMethods/sorting.cpp" "src/DrawingMethods/streamRead.cpp" "src/DrawingMethods/plot.cpp" "src/StreamOperations/streamOperations.cpp" "src/DrawingMethods/drawStream.cpp" -o "./bin/output.exe" -L"./lib" -m32 -g -lopengl32 -lglut32

@echo off

IF %errorlevel% == 0 echo Application compiled succeffully
IF %errorlevel% == 1 echo Application compilation failed

echo.
pause