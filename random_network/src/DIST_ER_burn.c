#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../mylibs/network.c"
#include "../mylibs/network.h"
#include "../mylibs/utils.c"
#include "../mylibs/utils.h"

int		main(int argc, char* argv[])
{
	//	############################
	//	arguments declare
	//	############################

	int		N			=	atoi(argv[1]);
	double	k			=	atof(argv[2]);
	int		nSample		=	atoi(argv[3]);				//	number of samples
	
	char	folder[100];								//	name of folder where the dataset is saved
	char	file[100];									//	name of data file
	char	path[100];									//	name of path
	FILE*	fp;											//	pointer for write data
	
	sprintf(folder, "./data/DIST_ER_burn");
	mkdirs(folder, 0755);								//	mkdir. in "utils.c"

	init_genrand64(time(NULL));							//	init random seed

	int		GC_N;										//	size of GC
	double	GC_k;										//	mean degree of GC

	int		sample		=	0;
	
	//	###########################
	//	initialize path
	//	###########################
	sprintf(path, "");
	sprintf(file, "/N%d_k%.2f.txt", N, k);
	strcat(path, folder);
	strcat(path, file);
	fp	=	fopen(path, "w");
		
	while(sample < nSample)	
	{

		//	###########################
		//	generate network
		//	###########################
		
		int*	GC_info		=	int_1d_arr(3);				//	GC_info. 0: GC ID, 1: GC_size, 2: GC_nLink
		
		int**	adj			=	int_2d_arr(N, 1);			//	new adjcency array of GC
		int*	degree		=	int_1d_arr(N);				//	new degree list of GC
		
		GEN_ER_BURN(N, k, GC_info, adj, degree);			//	in "network.c"
		
		//DeBuG_NeTWoRK(GC_info[1], adj, degree);			//	just for debug. in "network.c"
		
		GC_N	=	GC_info[1];								//	modify the size of GC
		GC_k	=	(double)2*GC_info[2]/GC_info[1];		//	modify the mean degree of GC
		
		//	############################
		//	write file
		//	############################

		fprintf(fp, "%d %.3f\n", GC_N, GC_k);
		sample++;										//	next sample

		// #############################
		// free memory
		// #############################

		for(int i = 0; i < GC_N; i++)
		{
			free(adj[i]);
		}
		free(adj);
		free(degree);
		free(GC_info);
	}
	return 0;

	printf("N%d k%.2f totSample%d DONE\n", N, k, nSample);
}

