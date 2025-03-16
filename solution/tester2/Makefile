CC = $(CXX)
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -march=native
STUB = $(if $(wildcard ../../stub/.), ../../stub, ../../contest)
GRADER = $(if $(wildcard ../../checker/.), ../../checker, ../../checker_cms)

run_%: %
	./$^

%: %.cpp
	$(CC) $(CCARGS) $^ -o $@

indset: indset.cpp grader.indset.cpp
	$(CC) $(CCARGS) $^ -o $@

indset%: indset%.cpp grader.indset.cpp
	$(CC) $(CCARGS) $^ -o $@

grader.%.cpp:
	ln -s $(GRADER)/$*_grader.cpp ./$@
