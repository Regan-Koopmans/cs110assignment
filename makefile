CC = g++
CFLAGS = -Wall -Werror -g
LFLAGS = -static
TARGET = main
OBJECTS = RandomNumberGenerator.o Dungeon.o Creature.o RolePlayingGame.o main.o


all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)


%.o: %.cpp
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm *.o
	rm *.exe

run:
	./$(TARGET)
