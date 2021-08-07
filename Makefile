SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

EXE = $(BIN_DIR)/tsp
SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CPPFLAGS = -MMD -MP
CXXFLAGS = -O3 -Wall #-pg
LDFLAGS = #-pg
LDLIBS =

$(shell mkdir -p $(dir $(OBJ)) >/dev/null)
$(shell mkdir -p $(dir $(EXE)) >/dev/null)

.PHONY: all clean win

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

win:
	if [ ! -d bin ]; then mkdir bin; fi
	x86_64-w64-mingw32-g++ -O3 -static $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp -o $(EXE).exe

win32:
	if [ ! -d bin ]; then mkdir bin; fi
	i686-w64-mingw32-g++ -O3 -static $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp -o $(EXE)32.exe

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
