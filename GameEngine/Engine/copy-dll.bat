  
@echo off

set solutiondir=%1
set target=%2

echo Copiando archivos...

xcopy "%solutiondir%libs\glew-2.1.0\bin\Release\Win32\glew32.dll" "%target%" /E /Y /S
xcopy "%solutiondir%libs\assimp\lib\assimp-vc141-mt.dll" "%target%" /E /Y /S

echo Copia finalizada