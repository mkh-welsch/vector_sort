all: generate_nets
	#clang++ -g         ./main.cpp -o main_debug_clang   -march=native -std=c++14
	#g++     -g         ./main.cpp -o main_debug_gcc     -march=native -std=c++14
	#g++     -pg -O2    ./main.cpp -o main_profile_gcc   -march=native -std=c++14
	clang++ -O2 -Ofast ./main.cpp -o main_profile_clang -march=native -std=c++14

.PHONY: generate_indices generate_nets
generate_indices:
	gcc -o generate_indices generate_indices.c

generate_nets:
	g++ -o generate_nets -std=c++14 generate_nets.cpp
	./generate_nets > sorting_network.hpp
