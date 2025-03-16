permutation: permutation.cpp
	$(CC) permutation.cpp $(CCARGS) -o permutation

run_permutation: permutation
	./permutation gen 2 1 seed=1 > 1_01.in
	./permutation gen 2 -1 seed=1 > 1_02.in
	./permutation gen 1000 1 seed=1 > 2_01.in
	./permutation gen 1000 -1 seed=1 > 2_02.in
	./permutation gen 1000 0 seed=1 > 2_03.in
	./permutation gen 1000 0 seed=2 > 2_04.in
	./permutation gen 1000 0 seed=3 > 2_05.in
	./permutation gen 1000 0 seed=4 > 2_06.in
	./permutation gen 1000 0 seed=5 > 2_07.in
	./permutation gen_hack_sort 1000 0 > 2_08.in
	./permutation gen_hack_sort 1000 1 > 2_09.in
