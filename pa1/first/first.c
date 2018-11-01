#include<stdio.h>
#include<stdlib.h>

void sort(int arr[], int *len, int num);
int main(int argc, char **argv){
	if (argc != 2){
		printf("Invalid Input \n");
		return 0;
	}

	FILE *fp;
	int len = 0;
	fp = fopen(argv[1], "r");

	if (fp == NULL) return 0;

	fscanf(fp, "%d\n", &len);
	//printf("%d\n",len);

	int even[len];
	int odd[len];
	int evenNum = 0;
	int oddNum = 0;

	int num = 0;
	while(fscanf(fp, "%d ", &num) == 1){
		//printf("%d ", num);
		(num % 2 == 0) ? sort(even, &evenNum, num) : sort(odd, &oddNum, num);
	}
	//printf("\n");

	//int fullSorted[len];
	int i3 = 0;
	int i2 = 0;
	for(i2 = 0; i2 < evenNum; i2++){
		printf("%d\t", even[i2]);
		//fullSorted[i2+i3] = even[i2];
	}
	for(i3 = 0; i3 <oddNum; i3++){
		printf("%d\t", odd[i3]);
		//fullSorted[i2+i3] = odd[i3];
	}
	//UNIT TESTS HERE
	printf("\n");
	return 0;
}

void sort(int arr[], int* len, int num){
	//sort here
	int i;
	int j;
	for(i = 0; i < *len; i++){
		if(arr[i] > num){
			for(j = *len; j > i; j--){
				arr[j] = arr[j-1];
			}
			arr[i] = num;
			*len = *len + 1;
			return;
		}
	}
	arr[*len] = num;
	*len = *len + 1;
	return;
}
