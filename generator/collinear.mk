collinear: collinear.cpp
	$(CC) collinear.cpp $(CCARGS) -o collinear

run_collinear: collinear
	./collinear gen 100000 100000 0 0 0 seed=1 > 1_01.in
	./collinear gen 100000 100000 0 0 0 seed=2 > 1_02.in
	./collinear gen 100000 100000 1 0 0 seed=2 > 1_03.in
	./collinear gen 100000 100000 0 1 0 seed=1 > 1_04.in
	./collinear gen 100000 100000 0 0 1 seed=1 > 1_05.in
	./collinear gen 100000 100000 1 0 0 seed=1 > 1_06.in
	./collinear gen 100000 100000 1 1 0 seed=1 > 1_07.in
	./collinear gen 100000 100000 1 0 1 seed=1 > 1_08.in
	./collinear gen 100000 100000 0 0 0 seed=3 > 1_09.in
	./collinear gen 100000 100000 2 0 0 seed=1 > 1_10.in
	./collinear gen 100000 100000 3 0 0 seed=1 > 1_11.in
	./collinear gen 300 75 0 0 0 seed=1 > 2_01.in
	./collinear gen 300 76 0 0 0 seed=1 > 2_02.in
	./collinear gen 300 77 0 1 0 seed=1 > 2_03.in
	./collinear gen 300 75 2 1 0 seed=1 > 2_04.in
	./collinear gen 300 78 0 0 1 seed=1 > 2_05.in
	./collinear gen 300 78 1 0 0 seed=1 > 2_06.in
	./collinear gen 300 78 1 0 1 seed=1 > 2_07.in
	./collinear gen 300 100 5 0 0 seed=1 > 2_08.in
	./collinear gen 300 100 0 0 0 seed=1 > 2_09.in
	./collinear gen 100000 25000 0 0 0 seed=1 > 3_01.in
	./collinear gen 100000 25000 0 0 0 seed=2 > 3_02.in
	./collinear gen 100000 25100 1 0 0 seed=2 > 3_03.in
	./collinear gen 100000 25020 0 1 0 seed=1 > 3_04.in
	./collinear gen 100000 25034 0 0 1 seed=1 > 3_05.in
	./collinear gen 100000 25012 1 0 0 seed=1 > 3_06.in
	./collinear gen 100000 30000 1 1 0 seed=1 > 3_07.in
	./collinear gen 100000 40000 1 0 1 seed=1 > 3_08.in
	./collinear gen 100000 25001 0 0 0 seed=3 > 3_09.in
	./collinear gen 100000 25000 2 0 0 seed=1 > 3_10.in
	./collinear gen 100000 25004 3 0 0 seed=1 > 3_11.in
