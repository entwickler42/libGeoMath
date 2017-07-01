REM CommandInterpreter: $(COMSPEC)
@echo off

md libgeomath

copy *.h libgeomath\
copy *.dll libgeomath\

echo Package "libgeomath" ready !
