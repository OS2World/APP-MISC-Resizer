# makefile
# Created by IBM WorkFrame/2 MakeMake at 15:34:16 on 16 Sept 2000
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES:

.SUFFIXES: \
    .c .obj 

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ti /C %s

{D:\C_Projects\Window_Resizer_Source}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ti /C %s

all: \
    .\resizer.exe

.\resizer.exe: \
    .\resizer.obj
    @echo " Link::Linker "
    icc.exe @<<
     /B" /de /pmtype:pm"
     /Feresizer.exe 
     .\resizer.obj
<<

.\resizer.obj: \
    D:\C_Projects\Window_Resizer_Source\resizer.c
