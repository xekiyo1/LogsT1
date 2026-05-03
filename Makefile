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
	touch placeholder.out
	install -Dv /dev/null bin/placeholder.out
	touch placeholder.bin
	ls | grep -P "^(?!europa|test|random)\w+\.bin" | xargs -d "\n" rm
	rm *.out
	rm ./*/*.out


allow-cli:
	chmod +rx ./sh/cli.sh
	chmod +rxw ./sh/logger.sh