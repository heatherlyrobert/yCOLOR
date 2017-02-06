#*============================----beg-of-source---============================*#

#===(current variables)=================================================================================================================================================#
BASE    = yCOLOR
DEBUG   = ${BASE}_debug
UNIT    = ${BASE}_unit
HDIR    = /home/system/yCOLOR.color_scheme_creator
IDIR    = /usr/local/bin
#*---(library documentation)----------*#
MNUM    = 3
MDIR    = /usr/share/man/man${MNUM}
MBASE   = ${BASE}.${MNUM}
#*---(overview)-----------------------*#
ONUM    = 0
ODIR    = /usr/share/man/man${ONUM}
OBASE   = ${BASE}.${ONUM}
#===(compilier variables)===============================================================================================================================================#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include 
#===(linker options)====================================================================================================================================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (E)-------------- (F)--------------
LINK    = gcc
LIBDIR  = -L/usr/local/lib
LIBS    = ${LIBDIR}         -lX11             -lGL              -lm               -lySTR            -lyURG
LIBD    = ${LIBDIR}         -lX11             -lGL              -lm               -lySTR_debug      -lyURG_debug      -lyLOG
LIBU    = ${LIBDIR}         -lX11             -lGL              -lm               -lySTR_debug      -lyURG_debug      -lyLOG            -lyUNIT           -lyVAR
#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (5)--------------
HEADS   = ${BASE}.h         ${BASE}_priv.h
OBJS    = ${BASE}.os        
OBJD    = ${BASE}.o         
OBJU    = ${OBJD}.o         ${UNIT}.o
#*---(make variables)-----------------*#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#*---(executables)--------------------*#
#all                : ${DEBUG}  ${BASE}  ${UNIT}  ${BASE}_make
all                : ${DEBUG}  ${BASE}  ${BASE}_make

${BASE}            : ${OBJS}
	${LINK}  -shared -Wl,-soname,lib${BASE}.so.1   ${LIBS}  -o lib${BASE}.so.1.0   ${OBJS}
	ar       rcs  lib${BASE}.a   ${OBJS}

${DEBUG}           : ${OBJD}
	${LINK}  -shared -Wl,-soname,lib${DEBUG}.so.1  ${LIBD}  -o lib${DEBUG}.so.1.0  ${OBJD}
	ar       rcs  lib${DEBUG}.a  ${OBJD}

${BASE}_make       : ${BASE}_make.o
	${LINK}  -o ${BASE}_make        ${BASE}_make.os  ${LIBS}  -lyX11  -lyCOLOR -lyFONT
	${LINK}  -o ${BASE}_make_debug  ${BASE}_make.os  ${LIBD}  -lyX11  -lyCOLOR -lyFONT



#*---(components)---------------------*#
${BASE}.o          : ${HEADS}       ${BASE}.c
	${COMP}  -fPIC  ${BASE}.c                                ${INC}
	${STRIP}        ${BASE}.c           > ${BASE}.cs
	${COMP}  -fPIC  ${BASE}.cs         -o ${BASE}.os         ${INC}

${BASE}_make.o     : ${HEADS}       ${BASE}_make.c
	${COMP}  -fPIC  ${BASE}_make.c                           ${INC}
	${STRIP}        ${BASE}_make.c      > ${BASE}_make.cs
	${COMP}  -fPIC  ${BASE}_make.cs    -o ${BASE}_make.os    ${INC}



#*---(housecleaning)------------------*#
clean              :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "cleaning out local object, backup, and temp files\n"
	${CLEAN} lib${BASE}.so.1
	${CLEAN} lib${BASE}.so.1.0
	${CLEAN} lib${DEBUG}.so.1
	${CLEAN} lib${DEBUG}.so.1.0
	${CLEAN} *.o
	${CLEAN} *.cs
	${CLEAN} *.os
	${CLEAN} *~
	${CLEAN} temp*
	${CLEAN} ${BASE}_unit.c

bigclean           :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "clean out local swap files\n"
	${CLEAN}  '.'*.sw?

remove             :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "remove ${BASE} from production\n"
	_lib      -d  ${BASE}
	_lib      -d  ${DEBUG}
	ldconfig

install            :
	#---(production version)--------------#
	sha1sum   lib${BASE}.so.1.0
	_lib      -s ${BASE}
	ldconfig
	sha1sum   lib${BASE}.a
	_lib      -a ${BASE}
	ldconfig
	#---(debug version)-------------------#
	sha1sum   lib${DEBUG}.so.1.0
	_lib      -S ${DEBUG}
	ldconfig
	sha1sum   lib${DEBUG}.a
	_lib      -A ${DEBUG}
	ldconfig
	#---(production version)--------------#
	${COPY}   ${BASE}_make         ${IDIR}/
	chown     root:root            ${IDIR}/${BASE}_make
	chmod     0755                 ${IDIR}/${BASE}_make
	@sha1sum  ${BASE}_make
	#---(debug version)-------------------#
	${COPY}   ${BASE}_make_debug   ${IDIR}/
	chown     root:root            ${IDIR}/${BASE}_make_debug
	chmod     0755                 ${IDIR}/${BASE}_make_debug
	@sha1sum  ${BASE}_make_debug
	#---(overview)------------------------#
	rm -f     ${ODIR}/${OBASE}.bz2
	cp -f     ${OBASE}    ${ODIR}
	bzip2     ${ODIR}/${OBASE}
	chmod     0644  ${ODIR}/${OBASE}.bz2
	#---(documentation)-------------------#
	rm -f     ${MDIR}/${MBASE}.bz2
	cp -f     ${MBASE}    ${MDIR}
	bzip2     ${MDIR}/${MBASE}
	chmod     0644  ${MDIR}/${MBASE}.bz2
	#---(done)----------------------------#
