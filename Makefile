# Define the compiler
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -g

# Define the target executable
TARGET=smht48

# Define the source files
SRC=smht48.c

# Define the object files
OBJ=$(SRC:.c=.o)

# The first target is the default when make is run without arguments
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to clean the build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Declare 'clean' as a phony target to ensure it always runs
.PHONY: clean

