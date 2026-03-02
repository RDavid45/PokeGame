play: Board.o Map.o SeedQueue.o play.o Movement.o MoveController.o Heap.o ArrayList.o Character.o CharacterMap.o
	gcc Board.o Map.o SeedQueue.o play.o Movement.o MoveController.o Heap.o ArrayList.o Character.o CharacterMap.o -o play

play.o: play.c headers/Map.h headers/Movement.h
	gcc -Iheaders play.c -Wall -Werror -g -c

board: Board.o genBoard.o SeedQueue.o
	gcc Board.o genBoard.o SeedQueue.o -o board

SeedQueue.o: data_structures/SeedQueue.c headers/SeedQueue.h
	gcc -Iheaders data_structures/SeedQueue.c -Wall -Werror -g -c

Character.o: characters/Character.c headers/Character.h headers/Movement.h
	gcc -Iheaders characters/Character.c -Wall -Werror -g -c

CharacterMap.o: characters/CharacterMap.c headers/CharacterMap.h headers/Character.h
	gcc -Iheaders characters/CharacterMap.c -Wall -Werror -g -c

Board.o: display/Board.c headers/Board.h headers/SeedQueue.h
	gcc -Iheaders display/Board.c -Wall -Werror -g -c

Map.o: display/Map.c headers/Map.h headers/Board.h headers/Character.h headers/CharacterMap.h
	gcc -Iheaders display/Map.c -Wall -Werror -g -c

genBoard.o: display/genBoard.c headers/Board.h
	gcc -Iheaders display/genBoard.c -Wall -Werror -g -c

ArrayList.o: data_structures/ArrayList.c headers/ArrayList.h
	gcc -Iheaders data_structures/ArrayList.c -Wall -Werror -g -c

Heap.o: data_structures/Heap.c headers/Heap.h headers/ArrayList.h
	gcc -Iheaders data_structures/Heap.c -Wall -Werror -g -c

Movement.o: movement/Movement.c headers/Movement.h headers/Heap.h
	gcc -Iheaders movement/Movement.c -Wall -Werror -g -c

MoveController.o: movement/MoveController.c headers/MoveController.h headers/Movement.h headers/CharacterMap.h
	gcc -Iheaders movement/MoveController.c -Wall -Werror -g -c

clean:
	rm -f *.o board *~ play