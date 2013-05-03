@echo off
mkdir build
cd build
cmake -G"NMake Makefiles" ..
nmake
mkdir out
nmake install DESTDIR=.\out
cd ..
