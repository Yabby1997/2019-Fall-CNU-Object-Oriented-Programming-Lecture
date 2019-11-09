.SUFFIXES: .cpp .o
OBJECTS = vehicle.o bike.o car.o 
TEST_FILE = main.o $(OBJECTS)
CXX = g++ 
TEST = test
$(TEST) : $(TEST_FILE)
	$(CXX) -o $(TEST) $(TEST_FILE)

clean :
	rm -rf   $(TEST) $(TEST_FILE)

main.o : main.cpp
vehicle.o : vehicle.cpp
car.o : car.cpp
bike.o : bike.cpp
