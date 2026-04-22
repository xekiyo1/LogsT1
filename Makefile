FILES=test.cpp
OUT=a.out
FLAGS=-O3 -o "$(OUT)"

compile:
	g++ $(FLAGS) $(FILES)
exec:
	./$(OUT)
run:
	make compile
	make exec
clean:
	rm *.out