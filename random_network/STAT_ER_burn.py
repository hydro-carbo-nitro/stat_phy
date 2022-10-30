#!/usr/bin/python3
#-*- coding: utf-8 -*-

import numpy as np
import os

if  __name__=="__main__":
    path        =   "./data/DIST_ER_burn"

    dataList    =   []
    dirList     =   []    
    NList       =   [10000 * x for x in range(1, 6)]
    kList       =   [0.1 * x for x in range(1, 51)]

    for i, k in enumerate(kList):
        kList[i]=   round(k, 2)

    for N in NList:
        for k in kList:
            dirList.append(f"N{N}_k{k}0.txt")
    for item in dirList:
        if "N" in item:
            data    =   np.loadtxt(path+"/"+item, encoding='cp949')
            dataList.append(data)

    idx         =   0
    statSet     =   []

    for N in NList:
        for k in kList:
            data        =   dataList[idx]
            mean_N      =   np.mean(data[:, 0])
            mean_k      =   np.mean(data[:, 1])
            std_N       =   np.std(data[:, 0])
            std_k       =   np.std(data[:, 1])

            stat        =   [N, k, mean_N, mean_k, std_N, std_k]
            statSet.append(stat)
            idx         +=  1

    statArr     =   np.array(statSet)
    fmt         =   '%d', '%1.1f', '%1.3f', '%1.3f', '%1.3e', '%1.3e'
    np.savetxt(path+"/stat.txt", statArr, fmt=fmt, encoding='utf-8')

    print("DONE")
