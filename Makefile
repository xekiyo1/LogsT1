RTreeConst=src/RTreeConstructors/NearestXConstructor.cpp src/RTreeConstructors/STRConstructor.cpp src/RTreeConstructors/RTreeConstructor.cpp
Tester=src/RTree.cpp src/RandomSquare/RandomSquare.cpp
Timer=src/util/calcTime/calcTime.cpp

FILES-CONSTRUCT=src/main/createTrees.cpp $(RTreeConst) $(Timer)
FLAGS-CONSTRUCT=-O3 -o "$(OUT)"

FILES-QUERY=src/main/treeQueries.cpp $(Tester)
FLAGS-QUERY= -Wall -DSAN=1 -fsanitize=address -fsanitize=undefined $(FLAGS)

OUT=a.out

exec:
	./$(OUT)

compile-construct:
	g++ $(FLAGS-CONSTRUCT) $(FILES-CONSTRUCT)
run-construct:
	make compile-construct
	make exec

compile-query:
	g++ $(FLAGS-QUERY) $(FILES-QUERY)
run-query:
	make compile-query
	make exec

run:
	make run-construct
	make run-query

clean:
	find . -type f -name "*.bin" ! -path "*europa.bin" ! -path "*test.bin" ! -path "*random.bin" -delete
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
compile-build-trees:
	g++ -o bin/commands/build_tree.out src/main/build_trees.cpp