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
LIBS    = ${LIBDIR}         -lm               -lySTR            -lyURG
LIBD    = ${LIBDIR}         -lm               -lySTR_debug      -lyURG_debug      -lyLOG
LIBU    = ${LIBDIR}         -lm               -lySTR_debug      -lyURG_debug      -lyLOG            -lyUNIT           -lyVAR

#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (5)--------------
HEADS   = ${BASE}.h         ${BASE}_priv.h
OBJS    = ${BASE}.os        ${BASE}_conv.os   ${BASE}_entry.os  ${BASE}_list.os   ${BASE}_table.os  
OBJD    = ${BASE}.o         ${BASE}_conv.o    ${BASE}_entry.o   ${BASE}_list.o    ${BASE}_table.o   
OBJU    = ${OBJD}.o         ${UNIT}.o

#*---(make variables)-----------------*#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



all                : ${BASE}_make
	#-----------------------#


${BASE}_make       : ${BASE}_make.o
	${LINK}  -o ${BASE}_make        ${BASE}_make.os  ${LIBS}  -lX11  -lyX11  -lGL -lyFONT
	${LINK}  -o ${BASE}_make_debug  ${BASE}_make.os  ${LIBD}  -lX11  -lyX11  -lGL -lyFONT


${BASE}_make.o     : ${HEADS}       ${BASE}_make.c
	${COMP}  -fPIC  ${BASE}_make.c                           ${INC}
	${STRIP}        ${BASE}_make.c      > ${BASE}_make.cs
	${COMP}  -fPIC  ${BASE}_make.cs    -o ${BASE}_make.os    ${INC}


#*---(standard library build)---------*#
#all                : ${BASE}.so.1.0 ${BASE}.a

#${BASE}.so.1.0     : ${OBJS}
#	${LINK}  -shared -Wl,-soname,lib${BASE}.so.1  ${LIBS}  -o lib${BASE}.so.1.0  ${OBJS}

#${BASE}.a          : ${OBJS}
#	ar       rcs  lib${BASE}.a  ${OBJS}


#*---(test version)-------------------*#
#test                    : yPALETTE_unit.o yPALETTE.o yPALETTE_list.o yPALETTE_conv.o yPALETTE_entry.o yPALETTE_table.o
#	${LINK}  -lm -lyUNIT -lyVAR -o test    yPALETTE_unit.o yPALETTE.o yPALETTE_entry.o yPALETTE_list.o yPALETTE_conv.o yPALETTE_table.o

#*---(build object file)--------------*#



#${BASE}.o               : yPALETTE.h yPALETTE_proto.h yPALETTE_color.h yPALETTE_table.h yPALETTE.c
#	${COMP}  -fPIC ${INCS} ${BASE}.c

#yPALETTE_unit.o         : yPALETTE.unit
#	uUNIT    yPALETTE
#	${COMP}  yPALETTE_unit.code


#yPALETTE_table.o        : yPALETTE_table.h yPALETTE_table.c
#	${COMP}  yPALETTE_table.c


#yPALETTE_entry.o        : yPALETTE.h yPALETTE_proto.h yPALETTE_color.h yPALETTE_table.h yPALETTE_entry.c
#	${COMP}  yPALETTE_entry.c


#yPALETTE_list.o         : yPALETTE.h yPALETTE_proto.h yPALETTE_color.h yPALETTE_table.h yPALETTE_list.c
#	${COMP}  yPALETTE_list.c


#yPALETTE_conv.o         : yPALETTE.h yPALETTE_proto.h yPALETTE_list.c
#	${COMP}  yPALETTE_conv.c

#library                 : yPALETTE.o yPALETTE_conv.o yPALETTE_entry.o yPALETTE_list.o yPALETTE_table.o
#	${LINK}  -shared -Wl,-soname,libyPALETTE.so.1 -o libyPALETTE.so.1.0   yPALETTE.o yPALETTE_entry.o yPALETTE_list.o yPALETTE_conv.o yPALETTE_table.o
#	chmod 0755 libyPALETTE.so.1.0
#	cp libyPALETTE.so.1.0 /usr/lib/
#	chmod 0755 /usr/lib/libyPALETTE.so.1.0
#	ldconfig -n /usr/lib/
#	ln -sf /usr/lib/libyPALETTE.so.1 /usr/lib/libyPALETTE.so
#	cp yPALETTE.h /usr/include/
#	chmod 0644 /usr/include/yPALETTE.h



#_colorscheme            : _colorscheme.o
#	${LINK}  -o _colorscheme _colorscheme.o -lyPALETTE


#_colorscheme.o          : _colorscheme.c
#	${COMP}  _colorscheme.c


#color                   : yPALETTE.o
#	${LINK}  -o yPALETTE yPALETTE.o


#color.o                 : yPALETTE.c yPALETTE.h
#	${COMP}  yPALETTE.c






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
#	sha1sum   lib${BASE}.so.1.0
#	_lib      -s ${BASE}
#	ldconfig
#	sha1sum   lib${BASE}.a
#	_lib      -a ${BASE}
#	ldconfig
	#---(debug version)-------------------#
#	sha1sum   lib${DEBUG}.so.1.0
#	_lib      -S ${DEBUG}
#	ldconfig
#	sha1sum   lib${DEBUG}.a
#	_lib      -A ${DEBUG}
#	ldconfig
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
	#---(production version)--------------#
#	${COPY}   ${BASE}_show         ${IDIR}/
#	chown     root:root            ${IDIR}/${BASE}_show
#	chmod     0755                 ${IDIR}/${BASE}_show
#	@sha1sum  ${BASE}_show
	#---(debug version)-------------------#
#	${COPY}   ${BASE}_show_debug   ${IDIR}/
#	chown     root:root            ${IDIR}/${BASE}_show_debug
#	chmod     0755                 ${IDIR}/${BASE}_show_debug
#	@sha1sum  ${BASE}_show_debug
	#---(production version)--------------#
#	${COPY}   ${BASE}_tick         ${IDIR}/
#	chown     root:root            ${IDIR}/${BASE}_tick
#	chmod     0755                 ${IDIR}/${BASE}_tick
#	@sha1sum  ${BASE}_tick
	#---(debug version)-------------------#
#	${COPY}   ${BASE}_tick_debug   ${IDIR}/
#	chown     root:root            ${IDIR}/${BASE}_tick_debug
#	chmod     0755                 ${IDIR}/${BASE}_tick_debug
#	@sha1sum  ${BASE}_tick_debug
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
