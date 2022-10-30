#include <stdio.h>
#include <stdlib.h>
#include "mt64.c"
#include "mt64.h"
int*	int_1d_arr(int size)
{
	int* arr = (int*) calloc(size, sizeof(int));
	return arr;
}

int**	int_2d_arr(int row, int col)
{
	int** arr = (int**) calloc(row, sizeof(int*));
	for (int tmp = 0; tmp < row; tmp++)
	{
		arr[tmp] = (int*) calloc(col, sizeof(int));
	}
	return arr;
}
double*		double_1d_arr(int size)
{
	double* arr = (double*) calloc(size, sizeof(double));
	return arr;
}

double**	double_2d_arr(int row, int col)
{
	double** arr = (double**) calloc(row, sizeof(double*));
	for (int tmp = 0; tmp < row; tmp++)
	{
		arr[tmp] = (double*) calloc(col, sizeof(double));
	}
	return arr;
}
void		DeBuG_NeTWoRK(int size, int** adjcency, int* degree_list)
{
	printf("\n>>>> DEBUG AREA <<<<\n");
	for(int i = 0; i < size; i++)
	{
		printf("%d : ", i);
		for(int j = 0; j < degree_list[i]; j++)
		{
			printf("%d ", adjcency[i][j]);
		}
		printf("\n");
	}
}
void		GC_BFS(int size, int* cluster, int* GC_info, int** adjcency, int* degree_list)
{
	int*	queue			=	int_1d_arr(size+1);
	int*	cluster_size	=	int_1d_arr(size+1);
	int		ndi, ndj, read, write, cluster_id;
	
	cluster_id				=	0;

	for(int idx = 0; idx < size; idx++)					//	for all nodes
	{
		if (!cluster[idx])								//	cluster[idx]=0 means that the node is not visited.
		{
			read			=	0;						//	initialize read pointer
			write			=	0;						//	initialize write pointer
			cluster_id++;								//	initialize cluster_id
			
			ndi				=	idx;					//	start searching
			queue[write]	=	ndi;					//	stack queue
			write++;									//	move write pointer
			
			cluster[ndi]	=	cluster_id;				//	node i is in cluster_id
			cluster_size[cluster_id]++;					//	increase cluster size

			while(read != write)						//	until read pointer = write pointer
			{
				read++;									//	move read pointer
				for(int tmp = 0; tmp < degree_list[ndi]; tmp++)
				{
					ndj		=	adjcency[ndi][tmp];		//	neighbor of node i
					if(!cluster[ndj])					//	node is not visited
					{
						cluster[ndj]	=	cluster_id;	//	node j is in cluster_id
						cluster_size[cluster_id]++;		//	increase cluster size
						queue[write]	=	ndj;		//	stack queue
						write++;						//	move write pointer
					}
				}
				ndi			=	queue[read];			//	there is no more neighbor, so pop queue
			}
		}
	}

	for(int idx = 1; idx < cluster_id+1; idx++)			//	for all clusters
	{
		if(cluster_size[idx] >= GC_info[1])
		{
			GC_info[0]	=	idx;							//	who is the largest cluster?
			GC_info[1]	=	cluster_size[idx];				//	how big is the largest cluster?
		}
	}

	free(queue);
	free(cluster_size);
}
void		GEN_ER(int N, double k, int** adj, int* degree)
{
	int ndi, ndj, linkT, linkC, judge;

	linkT		=	(int) (((double)N * k)/2.0);	//	link Target
	linkC		=	0;								//	link Current
	
	while(linkC < linkT)
	{
		ndi		=	(int)(genrand64_real2() * N);
		ndj		=	(int)(genrand64_real2() * N);
		judge		=	1;

		if(ndi != ndj)
		{
			for(int tmp = 0; tmp < degree[ndi]; tmp++)
			{
				if(adj[ndi][tmp] == ndj)
				{
					judge	=	0;
					break;
				}
			}
			if(judge)
			{
				adj[ndi][degree[ndi]]	=	ndj;
				adj[ndj][degree[ndj]]	=	ndi;

				degree[ndi]++;
				degree[ndj]++;

				linkC++;

				adj[ndi]	=	realloc(adj[ndi], sizeof(int)*(degree[ndi]+1));
				adj[ndj]	=	realloc(adj[ndj], sizeof(int)*(degree[ndj]+1));
			}
		}
	}
}
void		BURNING(int size, int* cluster, int* GC_info, int** adjcency, int* degree_list, int** GC_adjcency, int* GC_degree_list)
{
	int		new_idx			=	0;							//	new index for GC

	int*	match_OtoG		=	int_1d_arr(size);			//	match_OtoG[origin_index]	=	giant_index
	int*	match_GtoO		=	int_1d_arr(GC_info[1]);		//	match_GtoO[giant_index]		=	origin_index
	for(int i = 0; i < size; i++)
	{
		match_OtoG[i]		=	-1;							//	-1 means unmatched
	}

	for(int	idx = 0; idx < size; idx++)						//	index matching. idx is old idx
	{
		if(cluster[idx] == GC_info[0])
		{
			match_GtoO[new_idx]		=	idx;				//	giant to origin
			match_OtoG[idx]			=	new_idx;			//	origin to giant
			new_idx++;
		}
	}


	for(int idx = 0; idx < GC_info[1]; idx++)				//	New adj and degree. idx is new idx
	{
		GC_degree_list[idx]			=	degree_list[match_GtoO[idx]];								//	copy degree list
		GC_adjcency[idx]			=	realloc(GC_adjcency[idx], sizeof(int)*GC_degree_list[idx]);	//	realloc
		GC_info[2]					+=	GC_degree_list[idx];										//	calculate new total links

		for(int j = 0; j < GC_degree_list[idx]; j++)
		{
			GC_adjcency[idx][j]		=	match_OtoG[adjcency[match_GtoO[idx]][j]];
		}
	}

	GC_info[2]	/=	2;		// it is overlapped 2 times

	free(match_OtoG);
	free(match_GtoO);
}

void		GEN_ER_BURN(int size, double mean_degree, int* GC_info, int** GC_adjcency, int* GC_degree_list)
{
	int**	adjcency		=	int_2d_arr(size, 1);
	int*	degree_list		=	int_1d_arr(size);

	int*	cluster			=	int_1d_arr(size);

	GEN_ER(size, mean_degree, adjcency, degree_list);
	GC_BFS(size, cluster, GC_info, adjcency, degree_list);
	BURNING(size, cluster, GC_info, adjcency, degree_list, GC_adjcency, GC_degree_list);

	free(cluster);
	free(degree_list);
	for(int i = 0; i < size; i++)
	{
		free(adjcency[i]);
	}
	free(adjcency);
}


