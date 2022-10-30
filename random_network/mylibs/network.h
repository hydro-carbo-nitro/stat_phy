//	######################################################################################################################
//	ARRAY FUNCTIONS
//	######################################################################################################################
int*		int_1d_arr(int size);
//	create 1-dim array with dtype int, initial value 0, size {size}
//	{size}				:	size of array	
//
int**		int_2d_arr(int row, int col);
//	create dtype int 2-dim array with dtype int, initial value 0, size {row} * {col}
//	{row}				:	the number of rows of array
//	{col}				:	the number of columns of array
//
double*		double_1d_arr(int size);
//	create 1-dim array with dtype double, initial value 0, size {size}
//	{size}				:	size of array	
//
double**	double_2d_arr(int row, int col);
//	create dtype int 2-dim array with dtype double, initial value 0, size {row} * {col}
//	{row}				:	the number of rows of array
//	{col}				:	the number of columns of array
//
//	######################################################################################################################
//	NETWORK FUNCTIONS
//	######################################################################################################################
void		DeBuG_NeTWoRK(int size, int** adjcency, int* degree_list);
//	print the all elements of adjcency list.
//	{size}				:	size of adjcency list (= network size)
//	{adjcency}			:	adjcency[i][j] = jth neighbor of node i
//	{degree_list}		:	degree_list[i] = the number of degree of node i
//
void		GC_BFS(int size, int* cluster, int* GC_info, int** adjcency, int* degree_list);
//	Breadth First Search. This function find Giant Cluster of the network.
//	{size}				:	size of adjcency list (= network size)
//	{cluster}			:	cluster[i] = cluster index of node i, i.e. if there is 3 clusters,
//							value of cluster[i] has no choice but to have a value 1 ~ 3.
//	{GC_info}			:	GC_info[0] = index of giant cluster
//							GC_info[1] = size of giant cluster
//							GC_info[2] = mean degree of giant cluster(It is not used in this function)
//	{adjcency}			:	adjcency[i][j] = jth neighbor of node i
//	{degree_list}		:	degree_list[i] = the number of degree of node i
//
void		GEN_ER(int N, double k, int** adj, int* degree);
//	Generate Erdos Renyi Network.
//	{N}					:	size of network
//	{k}					:	mean degree of network
//	{adjcency}			:	adjcency[i][j] = jth neighbor of node i
//	{degree_list}		:	degree_list[i] = the number of degree of node i
//
void		BURNING(int size, int* cluster, int* GC_info, int** adjcency, int* degree_list, int** GC_adjcency, int* GC_degree_list);
//	Burning Alogrithm. Extracting only the giant cluster
//	{size}				:	size of adjcency list (= network size)
//	{cluster}			:	cluster[i] = cluster index of node i, i.e. if there is 3 clusters,
//							value of cluster[i] has no choice but to have a value 1 ~ 3.
//	{GC_info}			:	GC_info[0] = index of giant cluster
//							GC_info[1] = size of giant cluster
//							GC_info[2] = mean degree of giant cluster(It is not used in this function)
//	{adjcency}			:	adjcency[i][j] = jth neighbor of node i
//	{degree_list}		:	degree_list[i] = the number of degree of node i
//	{GC_adjcency}		:	adjcency of giant cluster
//	{GC_degree_list}	:	degree list of giant cluster
//	
void		GEN_ER_BURN(int size, double mean_degree, int* GC_info, int** GC_adjcency, int* GC_degree_list);
//	Generate Erdos Renyi network from burning algorithm
//	{size}				:	size of adjcency list (= original network size)
//	{mean_degree}		:	mean degree of original network.
//	{GC_info}			:	GC_info[0] = index of giant cluster
//							GC_info[1] = size of giant cluster
//							GC_info[2] = mean degree of giant cluster(It is not used in this function)
//	{GC_adjcency}		:	adjcency of giant cluster
//	{GC_degree_list}	:	degree list of giant cluster
//	
