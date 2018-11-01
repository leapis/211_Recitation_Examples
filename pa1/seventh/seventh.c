#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
	if(argc < 2){
		printf("No Input\n");
	}
	char* final = (char*) malloc ((argc) * sizeof(char));
	int i;
	for(i = 1; i < argc; i++){
		final[i-1] = argv[i][strlen(argv[i]) - 1];
	}
	printf("%s\n", final);
	return 0;
}
