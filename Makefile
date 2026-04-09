CC?=cc
CFLAGS=-Wall -Wextra
TARGET=rwx

.PHONY: all clean

all:$(TARGET)

$(TARGET):$(TARGET).c
	@echo "Compiling using $(CC)"
	@$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)
	@echo "Success! Run program with ./$(TARGET)"
clean:
	@echo "Cleaning up"
	@rm -f $(TARGET)
