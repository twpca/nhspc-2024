paint: paint.cpp
	$(CC) paint.cpp $(CCARGS) -o paint

run_paint: paint
	./paint 114514 1
	./paint 1919 2
	./paint 810 3
