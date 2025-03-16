taxi: taxi.cpp
	$(CC) taxi.cpp $(CCARGS) -o taxi

run_taxi: taxi
	./taxi 345432 1
	./taxi 676556 2
