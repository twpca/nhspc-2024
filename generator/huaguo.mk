huaguo: huaguo.cpp
	$(CC) huaguo.cpp $(CCARGS) -o huaguo

run_huaguo: huaguo
	./huaguo random    -T=1      -sum_n=100     -subtask=1 -yes_probability=1                            > 1_001.in
	./huaguo random    -T=10     -sum_n=100     -subtask=1 -yes_probability=1                            > 1_002.in
	./huaguo random    -T=30     -sum_n=100     -subtask=1 -yes_probability=1                            > 1_003.in
	./huaguo random    -T=50     -sum_n=100     -subtask=1 -yes_probability=1                            > 1_004.in
	./huaguo only_one  -T=1      -sum_n=2       -subtask=1 -an=100   -k=1                                > 1_005.in
	./huaguo random    -T=1      -sum_n=100     -subtask=2 -yes_probability=1                            > 2_001.in
	./huaguo random    -T=10     -sum_n=100     -subtask=2 -yes_probability=1                            > 2_002.in
	./huaguo random    -T=50     -sum_n=100     -subtask=2 -yes_probability=1                            > 2_003.in
	./huaguo only_one  -T=1      -sum_n=100     -subtask=2 -an=100   -k=99                               > 2_004.in
	./huaguo construct        -T=1      -sum_n=1000    -subtask=3                    -min_t=10000  -max_t=10000  -min_add=0 -max_add=0 > 3_001.in
	./huaguo construct        -T=10     -sum_n=1000    -subtask=3                    -min_t=5000   -max_t=10000  -min_add=0 -max_add=0 > 3_002.in
	./huaguo construct        -T=100    -sum_n=1000    -subtask=3                    -min_t=1      -max_t=10000  -min_add=0 -max_add=0 > 3_003.in
	./huaguo construct        -T=100    -sum_n=1000    -subtask=3 owo                -min_t=1      -max_t=10000  -min_add=0 -max_add=0 > 3_004.in
	./huaguo construct        -T=100    -sum_n=1000    -subtask=3 qwq                -min_t=1      -max_t=10000  -min_add=0 -max_add=0 > 3_005.in
	./huaguo only_one         -T=1      -sum_n=998     -subtask=3 -an=1      -k=999                                                    > 3_006.in
	./huaguo construct,random -T=1      -sum_n=1000    -subtask=3 -yes_probability=0 -min_t=10000  -max_t=10000  -min_add=0 -max_add=0 > 3_007.in
	./huaguo construct,random -T=10     -sum_n=1000    -subtask=3 -yes_probability=0 -min_t=5000   -max_t=10000  -min_add=0 -max_add=0 > 3_008.in
	./huaguo construct,random -T=100    -sum_n=1000    -subtask=3 -yes_probability=0 -min_t=1      -max_t=10000  -min_add=0 -max_add=0 > 3_009.in
	./huaguo construct,random -T=100    -sum_n=1000    -subtask=3 -yes_probability=0 -min_t=1      -max_t=10000  -min_add=0 -max_add=3 > 3_010.in
	./huaguo construct        -T=100    -sum_n=1000    -subtask=3 -yes_probability=0 -min_t=1      -max_t=10000  -min_add=0 -max_add=3 > 3_011.in
	./huaguo only_one         -T=100    -sum_n=1000    -subtask=3 -an=1000   -k=999                                                    > 3_012.in
	./huaguo random2          -T=1      -sum_n=1000    -subtask=3 -yes_probability=1 -max_min_a=100 -min_max_a=900                     > 3_013.in
	./huaguo construct        -T=10     -sum_n=1000    -subtask=3 -min_t=995 -max_t=1000 -min_add=0 -max_add=0 114                     > 3_014.in
	./huaguo random2          -T=100    -sum_n=1000    -subtask=3 -yes_probability=1 -max_min_a=0 -max_max_a=50 -max_sum_a=100 0       > 3_015.in
	./huaguo enumerate        -sum_n=1000 -n=4 -max_sum_a=100 > 3_016.in
	./huaguo enumerate        -sum_n=1000 -n=5 -max_sum_a=100 > 3_017.in
	./huaguo enumerate        -sum_n=1000 -n=6 -max_sum_a=100 > 3_018.in
	./huaguo construct        -T=1      -sum_n=1000    -subtask=4                    -min_t=10000  -max_t=10000  -min_add=0 -max_add=0 > 4_001.in
	./huaguo construct        -T=1      -sum_n=1000    -subtask=4                    -min_t=100000 -max_t=100000 -min_add=0 -max_add=0 > 4_002.in
	./huaguo construct        -T=1      -sum_n=1000    -subtask=4                    -min_t=90000  -max_t=100000 -min_add=0 -max_add=0 > 4_003.in
	./huaguo construct        -T=1      -sum_n=50000   -subtask=4                    -min_t=10000  -max_t=10000  -min_add=0 -max_add=0 > 4_004.in
	./huaguo construct        -T=1      -sum_n=51231   -subtask=4                    -min_t=100000 -max_t=100000 -min_add=0 -max_add=0 > 4_005.in
	./huaguo construct        -T=1      -sum_n=58888   -subtask=4                    -min_t=90000  -max_t=100000 -min_add=0 -max_add=0 > 4_006.in
	./huaguo construct        -T=1      -sum_n=100000  -subtask=4                    -min_t=100000 -max_t=100000 -min_add=0 -max_add=0 > 4_007.in
	./huaguo construct        -T=1      -sum_n=100000  -subtask=4 -force_a1=0        -min_t=100000 -max_t=100000 -min_add=0 -max_add=0 > 4_008.in
	./huaguo only_one         -T=1      -sum_n=100000  -subtask=4 -an=100000 -k=99999                                                  > 4_009.in
	./huaguo construct        -T=1      -sum_n=81231   -subtask=4                    -min_t=50000  -max_t=100000 -min_add=0 -max_add=0 > 4_010.in
	./huaguo construct        -T=1      -sum_n=100000  -subtask=4                    -min_t=1      -max_t=100000 -min_add=0 -max_add=0 > 4_011.in
	./huaguo construct        -T=1      -sum_n=92354   -subtask=4                    -min_t=1      -max_t=100000 -min_add=0 -max_add=0 > 4_012.in
	./huaguo construct        -T=1      -sum_n=99995   -subtask=4                    -min_t=90000  -max_t=100000 -min_add=0 -max_add=0 > 4_013.in
	./huaguo construct        -T=1      -sum_n=99987   -subtask=4                    -min_t=90000  -max_t=100000 -min_add=0 -max_add=0 > 4_014.in
	./huaguo construct        -T=1      -sum_n=99987   -subtask=4 -force_k=99987     -min_t=90000  -max_t=100000 -min_add=0 -max_add=0 > 4_015.in
	./huaguo construct        -T=1      -sum_n=92354   -subtask=4                    -min_t=1      -max_t=100000 -min_add=1 -max_add=1 > 4_016.in
	./huaguo construct        -T=1      -sum_n=99995   -subtask=4 -force_k=100000    -min_t=90000  -max_t=100000 -min_add=1 -max_add=1 > 4_017.in
	./huaguo construct        -T=1      -sum_n=99987   -subtask=4 -force_k=66658     -min_t=90000  -max_t=100000 -min_add=1 -max_add=1 > 4_018.in
	./huaguo random           -T=1      -sum_n=99999   -subtask=4 -yes_probability=0                                                   > 4_019.in
	./huaguo random           -T=1      -sum_n=87878   -subtask=4 -yes_probability=0                                                   > 4_020.in
	./huaguo random           -T=1      -sum_n=99824   -subtask=4 -yes_probability=0                                                   > 4_021.in
	./huaguo random           -T=1      -sum_n=100000  -subtask=4 -yes_probability=0                                                   > 4_022.in
	./huaguo construct        -T=1      -sum_n=100000  -subtask=4                      -min_t=1      -max_t=1      -min_add=0 -max_add=0 > 4_023.in
	./huaguo construct        -T=10     -sum_n=100000  -subtask=4 -yes_probability=0.9 -min_t=100000 -max_t=100000                       > 4_024.in
	./huaguo construct        -T=50     -sum_n=100000  -subtask=4 -yes_probability=0.9 -min_t=100000 -max_t=100000                       > 4_025.in
	./huaguo construct        -T=50     -sum_n=100000  -subtask=4 -yes_probability=0.1 -min_t=100000 -max_t=100000                       > 4_026.in
	./huaguo construct        -T=100    -sum_n=100000  -subtask=4 -yes_probability=0.5 -min_t=100000 -max_t=100000                       > 4_027.in
	./huaguo construct        -T=100    -sum_n=100000  -subtask=4 -yes_probability=0.1 -min_t=100000 -max_t=100000                       > 4_028.in
	./huaguo construct        -T=100    -sum_n=100000  -subtask=4 -yes_probability=0   -min_t=100000 -max_t=100000                       > 4_029.in
	./huaguo construct        -T=1000   -sum_n=100000  -subtask=4 -yes_probability=0.1 -min_t=100000 -max_t=100000                       > 4_030.in
	./huaguo construct        -T=10000  -sum_n=100000  -subtask=4 -yes_probability=0.1 -min_t=100000 -max_t=100000                       > 4_031.in
	./huaguo construct        -T=10000  -sum_n=100000  -subtask=4 -yes_probability=0.01 -min_t=100000 -max_t=100000                      > 4_032.in
	./huaguo enumerate        -sum_n=10000 -n=6 -max_sum_a=100 > 4_033.in
	./huaguo random    -T=1      -sum_n=10      -subtask=5 -yes_probability=1                            > 5_001.in
	./huaguo random    -T=1      -sum_n=1000000 -subtask=5 -yes_probability=0                            > 5_002.in
	./huaguo random    -T=1      -sum_n=999999  -subtask=5 -yes_probability=0                            > 5_003.in
	./huaguo random    -T=1      -sum_n=987877  -subtask=5 -yes_probability=0                            > 5_004.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9                          > 5_005.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 5                        > 5_006.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 48                       > 5_007.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 40                       > 5_008.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 qwq                      > 5_009.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 o_o                      > 5_010.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 owo                      > 5_011.in
	./huaguo random    -T=10     -sum_n=1000000 -subtask=5 -yes_probability=0.9 awa                      > 5_012.in
	./huaguo random    -T=100    -sum_n=1000000 -subtask=5 -yes_probability=0.9                          > 5_013.in
	./huaguo random    -T=1000   -sum_n=1000000 -subtask=5 -yes_probability=0.9                          > 5_014.in
	./huaguo random    -T=10000  -sum_n=1000000 -subtask=5 -yes_probability=0.9                          > 5_015.in
	./huaguo random    -T=100000 -sum_n=1000000 -subtask=5 -yes_probability=0.9                          > 5_016.in
	./huaguo random    -T=300000 -sum_n=1000000 -subtask=5 -yes_probability=0.9                          > 5_017.in
	./huaguo random    -T=300000 -sum_n=1000000 -subtask=5 -yes_probability=0.001                        > 5_018.in
	./huaguo enumerate        -sum_n=1000000 -n=7 -max_sum_a=100 > 5_019.in
