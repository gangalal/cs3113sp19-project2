#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_READ 1024
#define BUFF 100;


struct _process{//to hold the data
	char processName[20];
	int process;
};

typedef struct _process process;

char** parseString(char* str);//parses line of string 
int findKey(int Array1[], int key, int max);//this function is not used here

int main (int argc, char **argv)
{

	if ( (atoi(argv[2])<pow(2,4)) || (atoi(argv[2])>pow(2,30)))
	{
		printf("enter allcoation size <N> as 124000000\n");
		return 0;
	}

	FILE *stream;
	char *line = NULL;
	size_t num = 0;
	ssize_t read;

	//process* library;
	int totalAmount =  atoi(argv[2]);
	process* library = (process*) malloc(totalAmount * sizeof(process));
	int* flag = malloc(16*sizeof(int)); 
	int* blocks = malloc(16*sizeof(int));
	int* block2 = malloc(totalAmount*sizeof(int));
	int freeBlocks[16];
	int keySize = 0;
	int blockSize = 0;
	int boolAllocation = 0;
	int check = 0;
	int boolFind = 0;
	int boolRelease = 0;
	int temp;
	for (int i = 0; i<16; i ++)
	{
		flag[i] = 0;
		//library[i].process = -1;
	}
	library[0].process = totalAmount;
	block2[0] = 0;
	blocks[0] = totalAmount;
	//strcpy(library[0].processName, "A");

	//library[1].process = totalAmount;
	//printf("%d\n", totalAmount);

	int numProcess = 0;
	int availableAmount = totalAmount;

	stream = fopen(argv[3], "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &num, stream)) != -1)
	{

		if(strstr(line, "#") == NULL)
		{
			if(strstr(line, "REQUEST") != NULL)
			{
				line[strlen(line) - 1] = '\0';
				char** temp  = parseString(line);
				//availableAmount = totalAmount;
				char tempName[20];
				strcpy(tempName, temp[1]);
				//int size = 0;
				if(blockSize < 16 && availableAmount>=0)
				{
					printf("ALLOCATED %s %d\n", temp[1], blockSize);
					library[blockSize].process = atoi(temp[2]);
					blocks[blockSize] = atoi(temp[2]);
					block2[blockSize] = atoi(temp[2]);
					strcpy(library[blockSize].processName, tempName);
					flag[blockSize] = 1;
					boolAllocation = 1;
					availableAmount = availableAmount - atoi(temp[2]);
					library[blockSize+1].process = availableAmount;
					numProcess++;
					blockSize++;

				}
				else
				{

					for(int i = blockSize; i>-1; i--)
					{

						if (blocks[i]>=library[i].process)
						{
							printf("ALLOCATED %s %d\n", temp[1], i);
							library[i].process = atoi(temp[2]);
							blocks[i] = atoi(temp[2]);
							block2[i] = atoi(temp[2]);
							strcpy(library[i].processName, tempName);
							flag[i] = 1;
							boolAllocation = 1;
							i = -1;
						}





					}

					if (boolAllocation!=1)
					{
						printf("FAIL REQUEST %s %d\n", temp[1], atoi(temp[2]));

					}

				}


			}

			if(strstr(line, "RELEASE") != NULL)
			{
				line[strlen(line) -  1] = '\0';
				char** temp  = parseString(line);
				//availableAmount = totalAmount;
				char tempName[20];
				strcpy(tempName, temp[1]);
				for(int i = 0; i<blockSize; i++)
				{
					if (flag[i] ==1 && (strcmp(library[i].processName, tempName)==0))
					{
						printf("FREE %s %d %d\n", tempName, library[i].process, i);
						strcpy(library[i].processName, "NULL");
						//library[i].process = 0;
						block2[i] = 0;
						flag[i] = 0;
						boolRelease = 1;
					}
				}
				if (boolRelease == 0)
				{
					printf("FAIL RELEASE %s\n", tempName);
				}
			}

			if(strstr(line, "LIST AVAILABLE") != NULL)
			{
				int boolCheck = 0;
				for(int i = 0; i< numProcess; i++)
				{
					if (flag[i] == 0 && block2[i] ==0)
					{
						printf("(%d, %d)\n", blocks[i], i);
						boolCheck = 1;

					}
				}

				if(availableAmount == 0)
				{
					printf("Full\n");
				}
				else
				{
					printf("(%d, %d)\n", abs(availableAmount), numProcess);
				}


			}
			if(strstr(line, "LIST ASSIGNED") != NULL)
			{
				for(int i = 0; i<blockSize; i++)
				{
					if (flag[i] ==1)
					{
						printf("(%s, %d, %d)\n", library[i].processName, blocks[i], i);
						check = 1;

					}
				}
				if ( check == 0 || availableAmount == totalAmount)
				{
					printf("NONE\n");
				}

			}

			if(strstr(line, "FIND") != NULL)
			{
				line[strlen(line) - 1] = '\0';
				char** temp  = parseString(line);
				//availableAmount = totalAmount;
				char tempName[20];
				strcpy(tempName, temp[1]);
				for(int i = 0; i<blockSize; i++)
				{
					if (flag[i] ==1 && (strcmp(library[i].processName, tempName)==0))
					{
						printf("(%s, %d, %d)\n", tempName, library[i].process, i);
						boolFind = 1;
					}
				}
				if (boolFind == 0)
				{
					printf("FAULT\n");
				}

			}



		}

	}



	/* 	for(int i = 0; i<numProcess; i++)
		{
		printf("%d\n", library[i].process);
		}*/

	return 0;
}


char** parseString(char* str)
{
	char* ptr = strtok(str, " ");
	char** stri = malloc(1000*sizeof(char*));
	int j = 0;
	while(ptr != NULL)
	{
		stri[j] = ptr;
		ptr = strtok(NULL, " ");
		j++;
	}

	char** strings = stri;
	free(stri);
	return strings;

}

int findKey(int Array1[], int key, int max){
	int diff = abs( key - Array1[0]);
	int Num1 = 0;
	int Num2 = 0;
	for (int a = 0; a < max; a++)
	{
		if (diff > abs( key - Array1[a] ))
		{
			diff = abs( key - Array1[a]);
			Num1 = Array1[a];

		}
	}
	return Num1;
}
