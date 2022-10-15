#!/usr/bin/python3

import os

N_list  =   [20000]
k_list  =   list(0.5*x for x in range(1, 11))
nSample =   100

path    =   "./random_network"

for N in N_list:
    for k in k_list:
            os.system(f"time {path} {N} {k} {nSample}")
            print(f"{N} {k} {nSample} is Done")
        
