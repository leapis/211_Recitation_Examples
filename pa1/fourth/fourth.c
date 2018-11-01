#include<stdio.h>
#include<stdlib.h>

void launch(char*);

int main(int argc, char **argv){
	if(argc != 2){
		printf("Invalid Input\n");
	}
	launch(argv[1]);
	return 0;
}

void launch(char* argv){
	FILE *fp;
	fp = fopen(argv, "r");
	if(fp == NULL){
		printf("error\n");
		return;
	}
		
	int x1, y1;
	fscanf(fp, "%d %d", &x1, &y1);
	int matrix1[x1][y1];
	int i;
	for(i = 0; i < x1; i++){
		int j;
		int num;
		for(j = 0; j < y1; j++){
			fscanf(fp, "%d", &num);
			matrix1[i][j] = num;
		}
		fscanf(fp, "\n");
	}
	
	int x2, y2;
	fscanf(fp, "%d %d", &x2, &y2);
	int matrix2[x2][y2];
	for(i = 0; i < x2; i++){
		int j;
		int num;
		for(j = 0; j < y2; j++){
			fscanf(fp, "%d", &num);
			matrix2[i][j] = num;
		}
		fscanf(fp, "\n");
	}

	if(y1 != x2){
		printf("bad-matrices\n");
		return;
	}
	
	int matrix3[x1][y2];
	for(i = 0; i < x1; i++){
		int j;
		for(j = 0; j < y2; j++){
			int pointSum = 0;
			int z;
			for(z = 0; z < x2; z++){
				pointSum += matrix1[i][z] * matrix2[z][j];
			}
			matrix3[i][j] = pointSum;
		}
	}
	
	i = 0;
	int j = 0;
	while(i < x1){
		for(j = 0; j < y2; j++){
			printf("%d\t", matrix3[i][j]);
		}
		printf("\n");
		i++;
	}
	return;
}
		
