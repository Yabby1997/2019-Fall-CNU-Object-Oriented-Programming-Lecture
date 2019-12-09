.SUFFIXES: .cpp .o
OBJECTS = map.o game.o
TEST_FILE = main.o $(OBJECTS)
CXX = g++ 
TEST = game
$(TEST) : $(TEST_FILE)
	$(CXX) -o $(TEST) $(TEST_FILE)

clean :
	rm -rf   $(TEST) $(TEST_FILE)

main.o : main.cpp
map.o : map.cpp
game.o : game.cpp
