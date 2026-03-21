
play: Board.o Map.o SeedQueue.o play.o Movement.o Heap.o ArrayList.o Character.o
	gcc Board.o Map.o SeedQueue.o play.o Movement.o Heap.o ArrayList.o Character.o -o play

play.o: play.c Map.h Movement.h
	gcc play.c -Wall -Werror -g -c

board: Board.o genBoard.o SeedQueue.o
	gcc Board.o genBoard.o SeedQueue.o -o board

seedQueue.o: SeedQueue.c SeedQueue.h
	gcc SeedQueue.c -Wall -Werror -g -c

Character.o: Character.c Character.h Movement.h

Board.o: Board.c Board.h seedQueue.h
	gcc Board.c -Wall -Werror -g -c

Map.o: Map.c Map.h Board.h Character.h
	gcc Map.c -Wall -Werror -g -c

genBoard.o: genBoard.c Board.h
	gcc genBoard.c -Wall -Werror -g -c

ArrayList.0: ArrayList.c ArrayList.h
	gcc ArrayList.c -Wall -Werror -g -c

Heap.o: Heap.c Heap.h ArrayList.h
	gcc Heap.c -Wall -Werror -g -c

Movement.o: Movement.c Movement.h Heap.h
	gcc Movement.c -Wall -Werror -g -c

clean:
	rm -f *.o board *~ play