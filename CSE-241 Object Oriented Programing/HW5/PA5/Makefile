CompileRun: Program Run

Program: Field main
	g++ -std=c++11 ./lib/Field.o ./lib/main.o -o ./bin/program.exe

Field:
	g++ -std=c++11 -I "./include" -c ./src/Field.cpp -o ./lib/Field.o

main:
	g++ -std=c++11 -I "./include" -c ./src/main.cpp -o ./lib/main.o

Run:
	./bin/program.exe

