# Compiler
CC = cc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror

# Source Files
SRCS = main.c RFID.c add.c show.c modify.c delete.c save.c

# Object Files (Replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Output Executable
OUTFILE = student_record

# Default Rule
all: $(OUTFILE)

# Link Object Files to Create Executable
$(OUTFILE): $(OBJS)
	$(CC) $(OBJS) -o $(OUTFILE)

# Compile Source Files into Object Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -f $(OBJS) $(OUTFILE)

# Rebuild Everything
rebuild: clean all
