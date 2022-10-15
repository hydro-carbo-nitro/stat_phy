# Random Network

> Reference : Networks : An Introduction - M. E. J. Newman

## Description of each files
1. Running **"_run_ER_generator.py"** creates a directory named of **"./data"** on this folder and makes a dataset with $N=20000, k = 0.5, 1.0, 1.5, \cdots, 5.0$ with $100$ of samples in **"./data/"**
2. Running **"_run_degree_distribution.py"** makes a degree distribution data in **"./data/N[size]_k[degree]/"**
3. Running **"_fig_degree_distribution.py"** draws a plot of degree distribution


### _code_degree_distribution.c
> input arguments : [size of network, mean degree, number of samples]

Check a degree distribution of given adjcency list. Read 2 columns data which is made of node $i$ and node $j$. 

### _code_random_network.c
> input arguments : [size of network, mean degree, number of samples]

Create random network with size $N$ and mean degree $\langle k \rangle$ 

### _exec_degree_distribution
executable file of *_code_degree_distribution.c*

### _exec_random_network
executable file of *_code_degree_distribution.c*

### _fig_degree_distribution.py
draw plot of degree distribution with output file of *_exec_degree_distribution*

### _run_ER_generator.py
as run this file, it is able to run *_exec_random_network*

### _run_degree_distribution.py
as run this file, it is able to run *_exec_degree_distribution*

## Theory


