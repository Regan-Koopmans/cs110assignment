CC = g++
CFLAGS = -Wall -Werror
LFLAGS = -static
TARGET = main
OBJECTS = RandomNumberGenerator.o Dungeon.o Creature.o RolePlayingGame.o


all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)



%.o: %.cpp
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm *.o
	rm *.exe

run:
	./$(TARGET)
