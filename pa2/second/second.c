#include<stdio.h>
#include<stdlib.h>

int test(int[][9],int,int);

int main(int argc, char **argv){
	//catches
	FILE *fp;
	fp = fopen(argv[1], "r");
	int solution[9][9];
	int i = 0;
	int solved = 0;
	while(i < 81){
		char temp;
		if(i%9 == 0){
			fscanf(fp, "\n");
		}
		fscanf(fp, "%c \t", &temp);
		if(temp == '-'){
			solution[i/9][i%9] = -1;
		}
		else{
			int tempint = temp - '0';
			solution[i/9][i%9] = tempint;
			solved++;
		}
		i++;
	}
	int x = 0;
	while(x < 81){
		if(solution[x/9][x%9] == -1){
			int solvs = 0;
			int solvsnum = 0;
			int p;
			for(p = 1; p <= 9; p++){
				if(test(solution, x, p) == 1){
					solvs++;
					solvsnum = p;
				}
			}
			if(solvs == 1){
				solution[x/9][x%9] = solvsnum;
				solved++;
				x = -1;
			}
		}
		x++;
	}
	for(i = 0; i < 81; i++){
		if(solution[i/9][i%9]==-1){
			printf("no-solution");
			return 0;
		}
	}
	for(i = 0; i < 81; i++){
		printf("%d\t", solution[i/9][i%9]);
		if((i+1)%9 == 0){
			printf("\n");
		}
	}
	return 0;
		
}

int test(int sol[][9], int i, int p){
	int count = 0;
	int i2 = i%9;
	for(; i2 < 81; i2 = i2 + 9){
		if(sol[i2/9][i2%9] == p){
			count++;
			//printf("%d %d\t",i2, sol[i2/9][i2%9]);
		}
	}
	//printf("%d\t", count);
	i2 = i/9;
	int i3;
	for(i3 = 0; i3 < 9; i3++){
		if(sol[i2][i3] == p){
			count++;
		}
	}
	for(i2 = (i/9) - ((i/9)%3);i2 < (i/9)-((i/9)%3) + 3; i2++){
		for(i3 = i%9 - i%3;i3 < i%9 - i%3 + 3;i3++){
			if(sol[i2][i3] == p){
				count++;
			}
		}
	}
	if(count == 0){
		return 1;
	}
	else{
		return 0;
	}
}
