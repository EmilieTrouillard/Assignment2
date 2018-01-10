TARGET	= jacobi
OBJS	= mainPois.o jacobi.o gauss_seidel.o Mallocation.o

OPT	= -g -fast -xopenmp -xloopinfo
ISA	= 
PARA	= 

PNGWRITERPATH = pngwriter
ARCH	      = $(shell uname -p)
PNGWRTLPATH   = $(PNGWRITERPATH)/lib/$(ARCH)
PNGWRTIPATH   = $(PNGWRITERPATH)/include
PNGWRITERLIB  = $(PNGWRTLPATH)/libpngwriter.a

CCC	= CC
CXX	= CC
CXXFLAGS= -I $(PNGWRTIPATH)

CFLAGS	= $(OPT) $(ISA) $(PARA) $(XOPT)

F90C  	= f90

LIBS	= -L $(PNGWRTLPATH) -lpngwriter -lpng 


all: $(PNGWRITERLIB) $(TARGET)

$(TARGET): $(OBJS) 
	$(CCC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(PNGWRITERLIB):
	@cd pngwriter/src && $(MAKE)

clean:
	@/bin/rm -f *.o core

realclean: clean
	@cd pngwriter/src && $(MAKE) clean
	@rm -f $(PNGWRITERLIB)
	@rm -f $(TARGET)
	@rm -f jacobi.png

# dependencies
#
main.o  : mainPois.c
write_png.o: write_png.h write_png.cc
