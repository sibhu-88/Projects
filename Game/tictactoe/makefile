CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
EXECUTABLE = gtk_out
SOURCE = tictactoe.c

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
