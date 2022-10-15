#! /usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import os
import math
from scipy.special import factorial

def normalization(data):
    for sample in data:
        sample[:, 1] /= np.sum(sample[:, 1])

if __name__ == "__main__":

    N           =   20000
    kList       =   list(0.5*x for x in range(1, 11))
    dataSet     =   []

    root_path   =   "./data/"
    dirList     =   os.listdir(root_path)

    for dirName in dirList:
        fileList    =   os.listdir(root_path+dirName)
    
        for file in fileList:
            if "degree" in file:
                dataSet.append(np.loadtxt(root_path + dirName + "/" + file))

    normalization(dataSet)


    start   =   0
    end     =   15
    plt.figure(figsize=(16, 9), facecolor=(0.9, 0.9, 0.9))
    plt.tick_params(axis='both', direction='in', length=10.0, width=2.0, labelsize=20)
    
    for k, data, in zip(kList, dataSet):
        plt.plot(data[start:end, 0], data[start:end, 1],
                label=r"$k=$"+str(k), marker="^", linestyle=None, markersize=15)
    
    plt.legend(loc="best", fontsize=17)
    plt.xlabel(r"$number\;of\;degree$", fontsize=30)
    plt.ylabel(r"$p_k$", fontsize=30)
    plt.show()
