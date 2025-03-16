CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -march=native
GENERATOR_LIST = nums \
				 huaguo \
				 indset \
				 collinear \
				 permutation \
				 fingerprint \
				 paint \
				 taxi

all: $(GENERATOR_LIST)

clean:
	rm -f $(GENERATOR_LIST)

-include huaguo.mk

nums: nums.py
	echo "OAO"

run_nums: nums.py
	python3 nums.py

indset: indset.cpp
	$(CC) indset.cpp $(CCARGS) -o indset.exe

run_indset: indset
	./indset.exe -n=10 -q=10 -C=100 -array=random -query=l1 > 1_01.in
	./indset.exe -n=100 -q=100 -C=100000 -array=random -query=l1 > 1_02.in
	./indset.exe -n=2000 -q=2000 -C=10000000 -array=random -query=l1 > 1_03.in
	./indset.exe -n=2000 -q=2000 -C=1000000000 -array=random -query=l1 > 1_04.in
	./indset.exe -n=1754 -q=1754 -C=1000000000 -array=random -query=l1 > 1_05.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=1 -mode=random -query=l1 > 1_06.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=3 -mode=random -query=l1 > 1_07.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=5 -mode=random -query=l1 > 1_08.in
	./indset.exe -n=1497 -q=1497 -array=cartesian -full=0 -segment=1 -mode=inc -inv=5 -query=l1 > 1_09.in
	./indset.exe -n=1319 -q=1319 -array=cartesian -full=0 -segment=1 -mode=dec -inv=5 -query=l1 > 1_10.in
	./indset.exe -n=10 -q=10 -C=100 -array=random -query=subtask2 > 2_01.in
	./indset.exe -n=100 -q=100 -C=10000 -array=random -query=subtask2 > 2_02.in
	./indset.exe -n=2000 -q=2000 -C=1000000 -array=random -query=subtask2 > 2_03.in
	./indset.exe -n=2000 -q=2000 -C=1000000000 -array=random -query=subtask2 > 2_04.in
	./indset.exe -n=1234 -q=2000 -C=1000000000 -array=random -query=subtask2 > 2_05.in
	./indset.exe -n=1998 -q=2000 -array=cartesian -full=0 -segment=666 -mode=random -query=special > 2_06.in
	./indset.exe -n=1998 -q=2000 -array=cartesian -full=0 -segment=666 -mode=random -query=special2 > 2_07.in
	./indset.exe -n=1784 -q=2000 -C=1000000000 -array=random -query=subtask2 > 2_08.in
	./indset.exe -n=567 -q=2000 -C=1000000000 -array=random -query=subtask2 > 2_09.in
	./indset.exe -n=987 -q=2000 -C=1000000000 -array=random -query=subtask2 > 2_10.in
	./indset.exe -n=10 -q=55 -C=100 -array=random -query=full > 3_01.in
	./indset.exe -n=62 -q=1953 -C=1000 -array=random -query=full > 3_02.in
	./indset.exe -n=2000 -q=2000 -C=10 -array=random -query=random > 3_03.in
	./indset.exe -n=2000 -q=2000 -C=1000 -array=random -query=random > 3_04.in
	./indset.exe -n=2000 -q=2000 -C=1000000 -array=random -query=random > 3_05.in
	./indset.exe -n=1832 -q=2000 -C=1000000000 -array=random -query=random > 3_06.in
	./indset.exe -n=2000 -q=2000 -C=10 -array=random -query=hardcase > 3_07.in
	./indset.exe -n=2000 -q=2000 -C=1000 -array=random -query=hardcase > 3_08.in
	./indset.exe -n=1293 -q=2000 -C=1000000 -array=random -query=hardcase > 3_09.in
	./indset.exe -n=2000 -q=2000 -C=1000000000 -array=random -query=hardcase > 3_10.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=1 -query=cartesian -cartspec=1 > 3_11.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=1 -query=cartesian -cartspec=2 > 3_12.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=1 -mode=random -query=cartesian -cartspec=0 > 3_13.in
	./indset.exe -n=1474 -q=2000 -array=cartesian -full=0 -segment=10 -mode=random -query=cartesian -cartspec=0 > 3_14.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=100 -mode=random -query=cartesian -cartspec=0 > 3_15.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=1 -inv=200 -mode=inc -query=cartesian -cartspec=0 > 3_16.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=10 -inv=20 -mode=inc -query=cartesian -cartspec=0 > 3_17.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=1 -inv=200 -mode=dec -query=cartesian -cartspec=0 > 3_18.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=10 -inv=20 -mode=dec -query=cartesian -cartspec=0 > 3_19.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=1 -mode=random -query=hardcase > 3_20.in
	./indset.exe -n=1687 -q=2000 -array=cartesian -full=0 -segment=5 -mode=random -query=hardcase > 3_21.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=10 -mode=random -query=hardcase > 3_22.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=50 -mode=random -query=hardcase > 3_23.in
	./indset.exe -n=2000 -q=2000 -array=cartesian -full=0 -segment=100 -mode=random -query=hardcase > 3_24.in
	./indset.exe -n=1989 -q=2000 -array=cartesian -full=0 -segment=10 -mode=random -query=random > 3_25.in
	./indset.exe -n=1462 -q=2000 -array=cartesian -full=0 -segment=20 -mode=random -query=random > 3_26.in
	./indset.exe -n=1728 -q=2000 -array=cartesian -full=0 -segment=50 -mode=random -query=random > 3_27.in
	./indset.exe -n=908 -q=2000 -C=1000000000 -array=random -mode=random -query=random > 3_28.in
	./indset.exe -n=656 -q=2000 -C=1000000000 -array=random -mode=random -query=random > 3_29.in
	./indset.exe -n=673 -q=2000 -C=1000000000 -array=random -mode=random -query=random > 3_30.in

-include collinear.mk

-include permutation.mk

-include fingerprint.mk

-include taxi.mk

television: television.cpp
	$(CC) television.cpp $(CCARGS) -o television.exe

run_television: television
	./television.exe

-include paint.mk

pirate: pirate.cpp
	$(CC) pirate.cpp $(CCARGS) -o pirate

run_pirate: pirate
	./pirate 1337 1
	./pirate 1688 2
	./pirate 7382 3
	./pirate 6189 4
