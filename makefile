CC = g++
CFLAGS = -Wall -Werror -pedantic -g
LFLAGS = -static -g
TARGET = main
OBJECTS = RandomNumberGenerator.o Dungeon.o Creature.o Hero.o RolePlayingGame.o main.o


all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)


%.o: %.cpp
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm *.o
	rm *.exe
	rm $(TARGET)

run:
	./$(TARGET)
