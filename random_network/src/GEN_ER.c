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
	
	sprintf(folder, "./data/ER/N%d_k%.2f", N, k);
	mkdirs(folder, 0755);								//	mkdir. in "utils.c"

	init_genrand64(time(NULL));							//	init random seed

	int		sample		=	0;
	
	while(sample < nSample)	
	{
		//	###########################
		//	initialize path
		//	###########################
		sprintf(path, "");
		sprintf(file, "/%03d.txt", sample);
		strcat(path, folder);
		strcat(path, file);
		fp	=	fopen(path, "w");

		//	###########################
		//	generate network
		//	###########################
		
		int**	adj			=	int_2d_arr(N, 1);			//	adjcency array
		int*	degree		=	int_1d_arr(N);				//	degree list
		
		GEN_ER(N, k, adj, degree);							//	in "network.c"
		
		//DeBuG_NeTWoRK(GC_info[1], adj, degree);			//	just for debug. in "network.c"
		
		//	############################
		//	write file
		//	############################
														
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < degree[i]; j++)
			{
				fprintf(fp, "%d %d\n", i, adj[i][j]);
			}
		}

		sample++;											//	next sample
		

		// #############################
		// free memory
		// #############################

		for(int i = 0; i < N; i++)
		{
			free(adj[i]);
		}
		free(adj);
		free(degree);
	}
	printf("\n[N, k] : [%d, %.3f]", N, k);				//	just for debug.
	return 0;
}

