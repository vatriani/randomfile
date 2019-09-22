FLAGS=-Wall -O2 -mtune=native -march=native
#FLAGS:=-Wall
SRCS=string.o file.o output.o lists.o
TARGET=randomfile

all: $(TARGET)

randomfile: $(SRCS) main.c
	gcc $(FLAGS) $(SRCS) -o $(TARGET) main.c

spagetti: spagetti.c
	gcc $(FLAGS) -o spagetti spagetti.c

clean:
	rm -f *.d *.o $(TARGET)
	rm -f *.d *.o spagetti

install: $(TARGET)
	cp $(TARGET) /usr/bin/$(TARGET)
	chmod go+rx /usr/bin/$(TARGET)
