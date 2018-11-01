#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
	if(argc < 2){
		printf("No Input");
		return 0;
	}
	
	char* final = (char*) malloc (4 * 28 * (argc) * sizeof(char)); //4 for worse case, 28 for longest word
	char vowels[10] = {'a','e','i','o','u','A','E','I','O','U'};
	int i;
	int vowel; //0 or 1
	int tracer = 0;
	for(i = 1; i < argc; i++){
		char* temp = (char*) malloc (sizeof(argv[i]));
		size_t len = strlen(argv[i]);
		size_t j = 0;
		int z = 0;
		int breakers = 0;
		vowel = 0;
		for(j = 0; j < len; j++){
			if(vowel == 1){
				final[tracer] = argv[i][z];
				tracer++;
				z++;
			}
			else{
				int q;
				for(q = 0; q < 10; q++){
					if(argv[i][z] == vowels[q]){
						vowel = 1;
						final[tracer] = argv[i][z];
						tracer++;
					}
				}
				if(vowel == 0){
					temp[breakers] = argv[i][z];
					breakers++;
				}
				z++;
			}
		}
		if(breakers == 0){
			final[tracer] = 'y';
			final[tracer+1] = 'a';
			final[tracer+2] = 'y';
			tracer = tracer + 3;
		}
		else{
			for(z = 0; z < breakers; z++){
				final[tracer]= temp[z];
				tracer++;
			}
			final[tracer] = 'a';
			tracer++;
			final[tracer] = 'y';
			tracer++;
		}
		final[tracer] = ' ';
		tracer++;
	}
	
	for(i = 0; i < tracer; i++){
		printf("%c",final[i]);
	}
	printf("\n");
	return 0;
}
