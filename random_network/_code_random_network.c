#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int*	int_1d_arr(int size);
int**	int_2d_arr(int row, int col);
int		mkdirs(const char* path, mode_t mode);
void	gen_network(int N, double k, int** adj, int* degree);

int		main(int argc, char* argv[])
{
	srand(time(NULL));

	int			N		=	atoi(argv[1]);			//	network size
	double		k		=	atof(argv[2]);			//	mean degree
	int			nSample =	atoi(argv[3]);			//	number of samples

	char		file[100];							//	file name
	char		folder[100];						//	folder name
	char		path[200];							//	path name = file name + folder name
	FILE*		fp;									//	pointer for writing file

	sprintf(folder, "./data/N%d_k%.2f", N, k);		//	folder name
	mkdirs(folder, 0755);							//	make directory

	for (int sample = 0; sample < nSample; sample++)
	{	
		
		int**	adj		= int_2d_arr(N, 1);			//	adjcency list
		int*	degree	= int_1d_arr(N);			//	degree list

		gen_network(N, k, adj, degree);				//	generate network
	

		//====	write file	====//
		sprintf(path, "");												//	initialize path name
		sprintf(file, "/N%d_k%.2f_sample_%02d.txt", N, k, sample);		//	file name
		strcat(path, folder);
		strcat(path, file);												//	path name = folder + file

		fp	=	fopen(path, "w");					//	file pointer on path
		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < degree[i]; j++)
			{
				fprintf(fp, "%d %d\n", i, adj[i][j]);
			}
		}
		fclose(fp);

		//====	free memory	====//
		for (int i = 0; i < N; i++)
		{
			free(adj[i]);
		}
		free(adj);
		free(degree);
	}
	return 0;
}


int*	int_1d_arr(int size)
{
	int*	arr		=	(int*)	calloc(size, sizeof(int));
	return arr;
}

int**	int_2d_arr(int row, int col)
{
	int**	arr		=	(int**)	calloc(row, sizeof(int*));
	for (int tmp = 0; tmp < row; tmp++)
	{
		arr[tmp]	=	(int*)	calloc(col, sizeof(int));
	}
	return arr;
}


int mkdirs(const char* path, mode_t mode)
{
    char tmp_path[2048];
    const char *tmp = path;
    int  len  = 0;
    int  ret;

    if(path == NULL || strlen(path) >= 2048) {
        return -1;
    }

    while((tmp = strchr(tmp, '/')) != NULL) {
        len = tmp - path;
        tmp++;

        if(len == 0) {
            continue;
        }
        strncpy(tmp_path, path, len);
        tmp_path[len] = 0x00;

        if((ret = mkdir(tmp_path, mode)) == -1) {
            if(errno != EEXIST) {
                return -1;
            }
        }
    }

    return mkdir(path, mode);
}

void	gen_network(int N, double k, int** adj, int* degree)
{
	int		ndi;
	int		ndj;
	int		judge;

	int		target_degree		=	(int) ((double)N * k/2.0);
	int		current_degree		=	0;
	
	while(current_degree < target_degree)
	{
		judge = 1;
		ndi		=	rand() % N;		//	pick random node
		ndj		=	rand() % N;		//	pick random node
		
		if(ndi!=ndj)				//	except i = j
		{
			for(int idx = 0; idx < degree[ndi]; idx++)	//	check all nodes which in connected with i
			{
				if(adj[ndi][idx] == ndj)				//	if i and j are already connected
				{
					judge = 0;							//	do not connect
					break;
				}
			}
			if(judge)									//	if i and j are not connected
			{
				adj[ndi][degree[ndi]]	=	ndj;		//	connect i and j
				adj[ndj][degree[ndj]]	=	ndi;		//	connect j and i
				degree[ndi]++;							//	increase degree of i
				degree[ndj]++;							//	increase degree of j
				current_degree++;						//	increase current entire degree

				adj[ndi]	=	realloc(adj[ndi], (degree[ndi] + 1)*sizeof(int));	//	resize degree[ndi]	
				adj[ndj]	=	realloc(adj[ndj], (degree[ndj] + 1)*sizeof(int));	//	resize degree[ndj]
			}
		}
	}
	return;
}
