CXX = g++
CXXFLAGS = -c -std=c++11 -Wall

makeFileSystem: part2.o 
	$(CXX) part2.o -o makeFileSystem

part2.o: part2.cpp
	$(CXX) $(CXXFLAGS) part2.cpp

clean:
	rm -rf *.o makeFileSystem *.txt
