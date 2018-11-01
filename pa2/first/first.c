#include<stdio.h>
#include<stdlib.h>



int main(int argc, char **argv){
	FILE *fp;
	fp = fopen(argv[1], "r");
	int k; //number of training data attributes
	int n; //number of training samples
	
	fscanf(fp, "%d\n", &k);
	fscanf(fp, "%d\n", &n);
	double x[n][k+1];
	double y[n][1];
	int i;
	for(i = 0; i < n; i++){ //assemble x
		int j;
		x[i][0] = 1;
		for(j = 1; j <= k; j++){
			double temp1;
			fscanf(fp, "%lf,", &temp1);
			x[i][j] = temp1;
		}
		double temp2;
		fscanf(fp, "%lf", &temp2);
		y[i][0] = temp2; 
		fscanf(fp, "\n");
	}
	double xtranspose[k+1][n];
	for(i = 0; i < k+1; i++){ //assemble transpose
		int j;
		for(j = 0; j < n; j++){
			xtranspose[i][j] = x[j][i];
		}
	}
	double x2[k+1][k+1];
	for(i = 0; i < k+1; i++){ //x * xtranspost
		int j;
		for(j = 0; j < k+1; j++){
			int z;
			double total = 0;
			for(z = 0; z <= n; z++){
				total += x[z][i] * xtranspose[j][z];
			}
			x2[i][j] = total;
		}
	}
	
	double identity[k+1][k+1];
	for(i = 0; i < k+1; i++){ //assemble identity matrix
		int j;
		for(j = 0; j < k+1; j++){
			if(i == j){
				identity[i][j] = 1;
			}
			else{
				identity[i][j] = 0;
			}
		}
	}
	
	double augmented[(k+1)][2*(k+1)];
	for(i = 0; i < k+1;i++){ //construct augmented
		int j;
		for(j = 0; j < k+1; j++){
			augmented[i][j] = x2[i][j];
		}
	}
	for(i = 0; i < (k+1); i++){
		int j;
		for(j = k+1; j < 2*(k+1); j++){
			augmented[i][j] = identity[i][j-(k+1)];
		}
	}
	for(i = 0; i < k+1; i++){ //gaussian elim
		/*int p;
		for(p = 0; p < k+1; p++){
			int j;
			for(j = 0; j < 2*(k+1); j++){
				printf("%lf\t", augmented[p][j]);
			}
			printf("\n");
		}
		printf("\n");*/
		if(augmented[i][i] == 0){
			int j;
			int z = 0;
			for(j = i; j < k+1; j++){
				if(augmented[j][i] != 0){
					z = j;
					break;
				}
			}
			for(j = 0; j < 2*(k+1); j++){
				augmented[i][j] = augmented[i][j] + augmented[z][j];
			}
		}
		if(augmented[i][i] != 1){
			int j;
			double div = augmented[i][i];
			for(j = 0; j < 2*(k+1); j++){
				augmented[i][j] = augmented[i][j] / div;
			}
		}
		int j;
		for(j = i + 1; j < k+1; j++){
			if(augmented[j][i] != 0){
				double div = augmented[j][i];
				int z;
				for(z = 0; z < 2*(k+1); z++){
					augmented[j][z] = augmented[j][z] - augmented[i][z] * div;
				}
			}
		}
	}
	for(i = 0; i < k; i++){
		int j;
		for(j = i+1; j < k+1; j++){
			if(augmented[i][j] != 0){
				double div = augmented[i][j];
				int z;
				for(z = j; z < 2*(k+1); z++){
					augmented[i][z] = augmented[i][z] - augmented[j][z] * div;
				}
			}
		}
	}
	
	double xaug2[k+1][k+1]; //remove identity
	for(i = 0; i < k+1; i++){
		int j;
		for(j = 0; j < k+1; j++){
			xaug2[i][j] = augmented[i][j+k+1];
		}
	}
	
	double x3[k+1][n];
	for(i = 0; i < k+1; i++){ //xaug2 * xtranspost
		int j;
		for(j = 0; j < n; j++){
			int z;
			double total = 0;
			for(z = 0; z < k+1; z++){
				total += xaug2[i][z] * xtranspose[z][j];
			}
			x3[i][j] = total;
		}
	}
	
	double w[k+1];
	for(i = 0; i < k+1; i++){
		int j;
		double total = 0;
		for(j = 0; j < n; j++){
			total += y[j][0] * x3[i][j];
		}
		w[i] = total;
	}
	
	int len;
	fp = fopen(argv[2], "r");
	fscanf(fp, "%d\n", &len);
	double tests[len][k];
	for(i = 0; i < len; i++){
		int j;
		for(j = 0; j < k; j++){
			double temp3;
			fscanf(fp, "%lf,", &temp3);
			tests[i][j] = temp3;
		}
		fscanf(fp, "\n");
	}
	for(i = 0; i < len; i++){
		double total = w[0];
		int j;
		for(j = 0; j < k; j++){
			total += w[j+1] * tests[i][j];
		}
		printf("%0.0lf\n", total);
	}
		
	//prints'
	/*
	printf("%d\t%d\n",k+1,n);
	printf("\n x s: %lf \n", x[0][0]);
	for(i = 0; i < n; i++){
		int j;
		for(j = 0; j<= k; j++){
			printf("%lf\t", x[i][j]);
		}
		printf("\n");
	}
	
	printf("\n x transpose \n");
	for(i = 0; i <= k; i++){
		int j;
		for(j = 0; j< n; j++){
			printf("%lf\t", xtranspose[i][j]);
		}
		printf("\n");
	}
	
	printf("\n xt * x \n");
	for(i = 0; i < k+1; i++){
		int j;
		for(j = 0; j < k+1; j++){
			printf("%lf\t", x2[i][j]);
		}
		printf("\n");
	}
	printf("\n xaug2 \n");
	for(i = 0; i < k+1; i++){
		int j;
		for(j = 0; j < (k+1); j++){
			printf("%lf\t", xaug2[i][j]);
		}
		printf("\n");
	}
	
	printf("\nfin\n");
	for(i = 0; i < k+1; i++){
		int j;
		for(j = 0; j < n; j++){
			printf("%lf\t", x3[i][j]);
		}
		printf("\n");
	}	
	
	printf("\n final \n");
	for(i = 0; i < k+1; i++){
		printf("%lf\n", w[i]);
	}
	*/
	return 0;
}
