@echo off

if exist "kinx.exe" (
    kinx.exe utility\VersionSetup.kx 0.17.1
)

cl.exe /DWINMAIN /Feaddpath.exe utility\src\addpath.c Advapi32.lib User32.lib /link /SUBSYSTEM:WINDOWS
cl.exe /Feaddpathc.exe utility\src\addpath.c Advapi32.lib User32.lib
nmake -f Makefile.msc %*
