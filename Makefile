CL65	= cl65
LD65	= ld65

#-------------------------------------------------------------------------------
CSOURCES = main.c

ASMSOURCES =	startup.asm

OBJECTS	=	$(CSOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

LIBRARIES =	cc65_sincos.o
#-------------------------------------------------------------------------------
all :	$(OBJECTS) $(LIBRARIES)
	LD65 -o main.nes --config main.cfg --obj $(OBJECTS) $(LIBRARIES) --lib nes.lib

.SUFFIXES : .asm .o

.c.o :
	CL65 -t none -o $*.o -c -O $*.c

.asm.o :
	CL65 -t none -o $*.o -c $*.asm

.s.o :
	CL65 -t none -o $*.o -c $*.s

clean :
	rm *.nes
	rm *.o
