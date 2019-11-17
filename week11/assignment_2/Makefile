.SUFFIXES: .cpp .o
OBJECTS = Integer.o Float.o Complex.o
TEST_FILE = test.o $(OBJECTS)
CXX = g++
TEST = test
$(TEST) : $(TEST_FILE)
	$(CXX) -o $(TEST) $(TEST_FILE)

clean :
	rm -rf $(TEST) $(TEST_FILE)

test.o : test.cpp
Integer.o : Integer.cpp
Float.o : Float.cpp
Complex.o : Complex.cpp
