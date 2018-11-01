#include<stdio.h>
#include<stdlib.h>

int test(int*, int);

int main(int argc, char **argv){
	if (argc != 2){
		printf("Invalid Input\n");
	}
	FILE *fp;
	fp = fopen(argv[1], "r");
	int len;
	fscanf(fp, "%d\n", &len);
	int squares[len * len];
	int i;
	for(i = 0; i < len; i++){
		int j;
		for(j = 0; j < len; j++){
			int temp;
			fscanf(fp, "%d", &temp);
			squares[len*i+j] = temp;
		}
		fscanf(fp, "\n");
	}
	if(test(squares, len) == 1){
		printf("magic\n");
	}
	else{
		printf("not-magic\n");
	}
	return 0;
}

int test(int* squares, int len){
	int i;
	int j;
	int magic_num = 0;
	int sum;
	for(j = 0; j < len; j++) magic_num += squares[j];
	
	//duplicates
	int nums[len*len];
	for(j = 0; j < len*len;j++){
		nums[j] = -1;
	}
	for(j = 0; j < len*len;j++){
		if(squares[j] < 1){
			return 0;
		}
		if(nums[squares[j]-1] == -1){
			nums[squares[j]-1] = 1;
		}
		else{
			return 0;
		}
	}

	//rows
	for(j = 0; j < len; j++){
		sum = 0;
		for(i = 0; i < len; i++){
			sum += squares[j*len + i];
		}
		if(sum != magic_num){
			return 0;
		}
	}

	//columns
	for(j = 0; j< len; j++){
		sum = 0;
		for(i = 0; i < len; i++){
			sum += squares[j+ len*i];
		}
		if(sum != magic_num){
			return 0;
		}
	}

	//top left diag
	sum = 0;
	for(i = 0; i < len*len; i = i + len + 1){
		sum += squares[i];
	}
	if(sum != magic_num){
		return 0;
	}

	//top right diag
	sum = 0;
	for(i = len - 1; i <= len*(len - 1); i = i + len - 1){
		sum += squares[i];
	}
	if(sum != magic_num){
		return 0;
	}
	return 1;
}
