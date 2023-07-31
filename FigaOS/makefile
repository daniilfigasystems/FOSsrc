OBJS	= /src/drivers/vga.o /src/boot/fldinit.o
SOURCE	= /src/drivers/vga.c /src/boot/fldinit.c
HEADER	= 
OUT	= bin.bin
CC	 = gcc
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

/src/drivers/vga.o: /src/drivers/vga.c
	$(CC) $(FLAGS) /src/drivers/vga.c 

/src/boot/fldinit.o: /src/boot/fldinit.c
	$(CC) $(FLAGS) /src/boot/fldinit.c 


clean:
	help
