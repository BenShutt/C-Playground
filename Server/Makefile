CC = gcc
CFLAGS = -g -Wall -Wextra
RM = rm -rf

TARGET = server

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
	$(RM) *.dSYM

