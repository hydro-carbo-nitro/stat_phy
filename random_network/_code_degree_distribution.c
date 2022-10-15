#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int*	int_1d_arr(int size);
void	main(int argc, char* argv[])
{
	int			N		=	atoi(argv[1]);			//	network size
	double		k		=	atof(argv[2]);			//	mean degree
	int			nSample =	atoi(argv[3]);			//	number of samples
	
	int*		dist	=	int_1d_arr(N+1);
	int			ndi;
	int			ndj;
	
	
	//====	common	====//
	char		folder[100];							//	folder name

	//====	read	====//
	char		r_file[100];							//	file name
	char		r_path[200];							//	path name = file name + folder name
	FILE*		r_fp;									//	pointer for writing file

	//====	write	====//
	char		w_file[100];							//	file name
	char		w_path[200];							//	path name = file name + folder name
	FILE*		w_fp;									//	pointer for writing file
	

	sprintf(folder, "./data/N%d_k%.2f", N, k);			//	folder name

	for (int sample = 0; sample < nSample; sample++)
	{	
		
		int*	degree	= int_1d_arr(N);			//	degree list

		//====	read file	====//
		sprintf(r_path, "");											//	initialize path name
		sprintf(r_file, "/N%d_k%.2f_sample_%02d.txt", N, k, sample);	//	file name
		strcat(r_path, folder);											
		strcat(r_path, r_file);											//	path name = folder + file

		r_fp	=	fopen(r_path, "r");					//	load file
		if (r_fp == NULL)
		{
			printf("Failed to load [%s]", r_path);		//	failed to load file
		}
		else
		{
			while(!feof(r_fp))							//	until the end of line
			{
				fscanf(r_fp, "%d %d\n", &ndi, &ndj);	//	read lines
				degree[ndi]++;							//	increase degree
			}
		}
		for (int idx = 0; idx < N; idx++)
		{
			dist[degree[idx]]++;						//	degree distribution
		}
		fclose(r_fp);
		free(degree);
	}

	//====	write file	====//
	sprintf(w_path, "");
	sprintf(w_file, "/N%d_k%.2f_degree_dist.txt", N, k);
	strcat(w_path, folder);
	strcat(w_path, w_file);

	w_fp	=	fopen(w_path, "w");
	for (int idx = 0; idx < N; idx++)
	{
		fprintf(w_fp, "%d %d\n", idx, dist[idx]);
	}
	free(dist);
}


int*	int_1d_arr(int size)
{
	int*	arr		=	(int*)	calloc(size, sizeof(int));
	return arr;
}

