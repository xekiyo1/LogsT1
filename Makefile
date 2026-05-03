
RTreeConst=RTreeConstructors/NearestXConstructor.cpp RTreeConstructors/STRConstructor.cpp RTreeConstructors/RTreeConstructor.cpp

FILES=test.cpp RTree.cpp $(RTreeConst)
OUT=a.out
FLAGS=-O3 -o "$(OUT)"

TEST-FILES=test.cpp RTree.cpp $(RTreeConst)
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
	touch bin/placeholder.out
	touch placeholder.bin
	ls | grep -P "^(?!europa|test|random)\w+\.bin" | xargs -d "\n" rm
	rm *.out
	rm ./*/*.out


allow-cli:
	chmod +rx ./sh/cli.sh
	chmod +rxw ./sh/logger.sh