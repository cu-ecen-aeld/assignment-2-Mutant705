# Default compiler definitions
# If CROSS_COMPILE is provided (e.g., CROSS_COMPILE=aarch64-linux-), 
# CC becomes aarch64-linux-gcc. Otherwise, it defaults to native gcc.
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror -g

# Target application name
TARGET = writer
OBJS = writer.o

# Default target: Builds the "writer" application
.PHONY: all
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: Removes the application executable and all object files
.PHONY: clean
clean:
	rm -f $(TARGET) *.o
