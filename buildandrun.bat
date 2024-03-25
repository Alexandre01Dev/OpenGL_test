@echo off
echo Starting compilation process...
cd .\build\ && cmake --build . --config Release && cd .. && .\build\Release\OPENGL_TEST.exe cd .\build\
echo Process finished.