.SUFFIXES: .cpp .o 
OBJECTS = gameIO.o
TEST_FILE = game.o $(OBJECTS)
CXX = g++ 
TEST = game
$(TEST) : $(TEST_FILE)
	$(CXX) -o $(TEST) $(TEST_FILE)

clean :
	rm -rf   $(TEST) $(TEST_FILE)

game.o : game.cpp
gameIO.o : gameIO.cpp
