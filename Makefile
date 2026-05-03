RTreeConst=RTreeConstructors/NearestXConstructor.cpp RTreeConstructors/STRConstructor.cpp RTreeConstructors/RTreeConstructor.cpp
Tester=RTree.cpp RandomSquare.cpp
Timer="util/calcTime/calcTime.cpp"

FILES=test.cpp $(Tester) $(RTreeConst) $(Timer)
OUT=a.out
FLAGS=-O3 -o "$(OUT)"

TEST-FILES=$(FILES)
TEST-FLAGS= -Wall -DSAN=1 -fsanitize=address -fsanitize=undefined $(FLAGS)

compile:
	g++ $(FLAGS) $(FILES)
exec:
	./$(OUT)
run:
	make compile
	make exec

compile-test:
	g++ $(TEST-FLAGS) $(TEST-FILES)
test:
	make clean
	make compile-test
	make exec


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