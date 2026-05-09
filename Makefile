RTreeConst=src/RTreeConstructors/NearestXConstructor.cpp src/RTreeConstructors/STRConstructor.cpp src/RTreeConstructors/RTreeConstructor.cpp
Tester=src/RTree.cpp src/util/RandomSquare/RandomSquare.cpp
Timer=src/util/calcTime/calcTime.cpp

FILES-CONSTRUCT=$(RTreeConst) src/RTreeConstructors/NodoCalculador.cpp $(Timer)
FLAGS-CONSTRUCT=-O3 -o "$(OUT)"

FILES-QUERY=$(Tester)
FLAGS-QUERY= -Wall -DSAN=1 -fsanitize=address -fsanitize=undefined 

OUT=a.out

exec:
	./$(OUT)

compile-construct:
	g++ $(FLAGS-CONSTRUCT) src/main/createTrees.cpp $(FILES-CONSTRUCT)
run-construct:
	make compile-construct
	make exec

compile-query:
	g++ $(FLAGS-QUERY) src/main/treeQueries.cpp $(FILES-QUERY)
run-query:
	make compile-query
	make exec

run:
	make run-construct
	make run-query

clean:
	find . -type f -name "*.bin" ! -path "*/data/*" -delete
	find -type f -name "*.out" -delete
clean-logs:
	find -type f -name "*.log | *.csv"
allow-cli:
	chmod +rx ./sh/cli.sh
	chmod +rxw ./sh/logger.sh

init:
	install -Dv /dev/null bin/commands/__init_placeholder__.out
	install -Dv /dev/null bin/trees/__init_placeholder__.out
	make clean
	make allow-cli


COMMAND_FLAGS=-O3 -Wall
CUSTOM-BUILD-OUT=bin/commands/custom_build.out
CUSTOM-QUERY-OUT=bin/commands/custom_query.out

compile-custom:
	g++ -o $(CUSTOM-BUILD-OUT) src/main/custom_build.cpp $(FILES-CONSTRUCT)
	g++ -o $(CUSTOM-QUERY-OUT) src/main/custom_query.cpp $(FILES-QUERY)

run-bonus:
	make compile-custom
	./$(CUSTOM-BUILD-OUT) europa_bonus.bin STR 24
	./$(CUSTOM-QUERY-OUT) custom.bin -11 32 -1 40

run-all:
	make clean
	make run
	make run-bonus
