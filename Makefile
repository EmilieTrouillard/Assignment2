
SRCS 	= jacobi.c
SRCS	= gauss_seidel.c
SRCS	= Mallocation.c

OBJS	= jacobi.o
OBJS	= gauss_seidel.o
OBJS	= Mallication.o

TARGET	= mainPois.$(CC)

CC		= cc
OPT		= -g -O3
CFLAGS	= $(OPT)

LIBS	= -L /usr/lib64/atlas -lsatlas

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -c stdafx.h -o stdafx.h.gch
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
