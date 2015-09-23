CC = g++
CFLAGS = -Wall -Werror
LFLAGS = -static
TARGET = main
OBJECTS =



all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)



%.o: %.cpp
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm *.o
	rm *.exe

run:
	./$(TARGET)
