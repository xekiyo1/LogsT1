FILES=test.cpp
OUT=a.out
FLAGS=-O3 -o "$(OUT)"

TEST-FILES=test.cpp RTree.cpp STR.cpp Nearest_X.cpp
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
	touch placeholder.bin
	ls | grep -P "^(?!europa|test|random)\w+\.bin" | xargs -d "\n" rm
	rm *.out