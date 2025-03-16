fingerprint: fingerprint.cpp
	$(CC) fingerprint.cpp $(CCARGS) -o fingerprint

run_fingerprint: fingerprint
	./fingerprint 1 1
	./fingerprint 2 2
	./fingerprint 3 3