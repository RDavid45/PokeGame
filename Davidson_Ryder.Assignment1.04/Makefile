# === Compiler + Flags ===
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -g -Iheaders 
LDFLAGS :=
LDLIBS  := 

NCURSES_CFLAGS := $(shell pkg-config --cflags ncursesw 2>/dev/null)
NCURSES_LIBS   := $(shell pkg-config --libs ncursesw 2>/dev/null)

CFLAGS  += $(NCURSES_CFLAGS)
LDLIBS  += $(NCURSES_LIBS)

# === Sources ===
SRCS_PLAY := \
    display/Board.c \
    display/Map.c \
	display/Colors.c \
    data_structures/SeedQueue.c \
    movement/Movement.c \
    movement/MoveController.c \
    data_structures/Heap.c \
    data_structures/ArrayList.c \
    characters/Character.c \
    characters/CharacterMap.c \
    play.c

#SRCS_BOARD := \
    display/Board.c \
    display/genBoard.c \
    data_structures/SeedQueue.c

OBJS_PLAY  := $(SRCS_PLAY:.c=.o)
#OBJS_BOARD := $(SRCS_BOARD:.c=.o)

# === Default target ===
.PHONY: all
all: play #board

# === Link targets ===
play: $(OBJS_PLAY)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

#board: $(OBJS_BOARD)
#	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# === Pattern rule for all .c -> .o (applies CFLAGS with -Iheaders) ===
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# === Housekeeping ===
.PHONY: clean
clean:
	rm -f $(OBJS_PLAY) $(OBJS_BOARD) play board *~ core
