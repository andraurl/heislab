# Which compiler to use
CC = clang-3.8

# Compiler flags go here.
CFLAGS = -g -Wall

# Linker flags go here.
LDFLAGS = -lcomedi -lm

# list of sources
ELEVSRC = elev.c io.c main.c event_handler.c hardware_driver.c FSM.c order_module.c memory.c time_module.c

# program executable file name.
TARGET = heis

# top-level rule, to compile everything.
all: $(TARGET)

# Define all object files.
ELEVOBJ = $(ELEVSRC:.c=.o)

# rule to link the program
$(TARGET): $(ELEVOBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(ELEVOBJ)

rebuild:	clean all

.PHONY: all rebuild clean


#Martin Korsgaard, 2006
