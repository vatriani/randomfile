ifeq ($(OS),Windows_NT)
	WIN += 1
    EXECUTEABLE += randomfile.exe
	CC="C:\mingw64\bin\gcc.exe"
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
	EXECUTEABLE += randomfile
	CC="gcc"
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif

FLAGS=-Wall -O2 -mtune=native -march=native
SRCS=string.o file.o output.o lists.o

all: $(EXECUTEABLE)

$(EXECUTEABLE): $(SRCS) main.c
	$(CC) $(FLAGS) $(SRCS) -o $(EXECUTEABLE) main.c

spagetti: spagetti.c
	$(CC) $(FLAGS) $(CCFLAGS) -o $(EXECUTEABLE) spagetti.c

run:
	$(EXECUTEABLE) ./

clean:
ifeq ($(OS),Windows_NT)
	del $(EXECUTEABLE)
	del *.o
else
	rm -f *.d *.o $(EXECUTEABLE)
endif

install: $(TARGET)
	cp $(TARGET) /usr/bin/$(TARGET)
	chmod go+rx /usr/bin/$(TARGET)
