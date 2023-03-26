CC = gcc
CFLAGS = -g -Wall -Wextra
RM = rm -rf

TARGET = triangleNumbers

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
	$(RM) *.dSYM

