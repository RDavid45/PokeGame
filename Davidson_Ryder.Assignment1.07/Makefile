# === Compiler + Flags ===
CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror -g -Iheaders
LDFLAGS  :=
LDLIBS   :=

NCURSES_CXXFLAGS := $(shell pkg-config --cflags ncursesw 2>/dev/null)
NCURSES_LIBS     := $(shell pkg-config --libs ncursesw 2>/dev/null)

CXXFLAGS += $(NCURSES_CXXFLAGS)
LDLIBS   += $(NCURSES_LIBS)

# === Sources ===
SRCS_PLAY := \
    display/Board.cpp \
    display/Map.cpp \
    display/Colors.cpp \
    display/Chunk.cpp \
    data_structures/SeedQueue.cpp \
    movement/Movement.cpp \
    movement/MoveController.cpp \
    movement/Move.cpp \
    pokemon/Pokemon.cpp \
    pokemon/PokemonFactory.cpp \
    pokemon/Mon.cpp \
    characters/Character.cpp \
    characters/CharacterMap.cpp \
    CSVReader.cpp \
    play.cpp

OBJS_PLAY := $(SRCS_PLAY:.cpp=.o)

# === Default target ===
.PHONY: all
all: play

# === Link targets ===
play: $(OBJS_PLAY)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_PLAY) play *~ core
