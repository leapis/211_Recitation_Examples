#include<stdio.h>
#include<stdlib.h>

struct puzzle{
	int spots[9][9];
};

int toFind[81];
int numToFind;

int check(struct puzzle);
int test(int[][9], int, int);
struct puzzle solve(struct puzzle, int);
struct puzzle copyPuzzle(struct puzzle);
void dumpPuzzle(int[][9]);

int main(int argc, char **argv){
	numToFind = 0;
	FILE *fp;
        fp = fopen(argv[1], "r");
        struct puzzle sol;
        int i = 0;
        while(i < 81){
                char temp;
                if(i%9 == 0){
                        fscanf(fp, "\n");
                }
                fscanf(fp, "%c \t", &temp);
                if(temp == '-'){
                        sol.spots[i/9][i%9] = -1;
			toFind[numToFind] = i;
			numToFind++;
                }
                else{
                        int tempint = temp - '0';
                        sol.spots[i/9][i%9] = tempint;
                }
                i++;
        }
	int j, lowest, temp, val1, val2;
	for (i = 0; i < numToFind; i++){
		lowest = i;
		for(j=i; j<numToFind; j++){
			int k;
			val1 = 0;
			val2 = 0;
			for(k = 1; k <= 9; k++){
                                if(test(sol.spots,toFind[lowest],k) == 1){
                                        val1++;
                                }
				if(test(sol.spots,toFind[j],k) == 1){
					val2++;
				}
			}
			if(val2>val1){
				lowest = j;
			}
		}
		temp = toFind[i];
		toFind[i] = toFind[lowest];
		toFind[lowest] = temp;
	}
	sol = solve(sol, 0);
	dumpPuzzle(sol.spots);
	return 0;
}

struct puzzle solve(struct puzzle sol, int k){
	if(k>numToFind - 1){
		return sol;
	}
	int i = toFind[k];
	int found = 0;
	int j = 0;
	for(j = 1; j <= 9; j++){
		if(test(sol.spots,i,j) == 1){
			found++;
			struct puzzle tempSol = copyPuzzle(sol);
			//printf("%d\n",sol.spots[i/9][i%9]);
			tempSol.spots[i/9][i%9] = j;
			//printf("trying %d = %d\n", i, j);
			tempSol = solve(tempSol,k+1);
			if(check(tempSol) == 1){
				//printf("found\n");
				return tempSol;
			}
		}
	}
	if(found == 0){
		return sol;
	}
	return sol;
}

int test(int sol[][9], int i, int p){
        int count = 0;
        int i2 = i%9;
        for(; i2 < 81; i2 = i2 + 9){
                if(sol[i2/9][i2%9] == p){
                        count++;
                }
        }
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


struct puzzle copyPuzzle(struct puzzle toCopy){
	struct puzzle copy;
	int i;
	for(i = 0; i < 81; i++){
		copy.spots[i/9][i%9] = toCopy.spots[i/9][i%9];
	}
	return copy;
}

int check(struct puzzle sol){
	int i;
        for(i = 0; i < 81; i++){
                if(sol.spots[i/9][i%9]==-1){
			//dumpPuzzle(sol.spots);
                        return 0;
                }
        }
        return 1;
}

void dumpPuzzle(int solution[][9]){
	int i;
	for(i = 0; i < 81; i++){
                printf("%d\t", solution[i/9][i%9]);
                if((i+1)%9 == 0){
                        printf("\n");
                }
        }
}
