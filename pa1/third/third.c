#include<stdio.h>
#include<stdlib.h>

#define SIZE 10000

int keyGen(int);
void launch(char*);
void employ(char, int);
void insert(int);
void search(int);

struct item{
	int val;
	int key;
	struct item* next;
};

struct item* new_item(int);

struct item* table[SIZE];
struct item* new_item(int val){
	struct item* temp = malloc(sizeof(struct item));
	temp->val = val;
	return temp;
}

int keyGen(int val){
	return abs(val % SIZE);
}

int main(int argc, char **argv){
	if (argc != 2){
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

	char job;
	int num;
	while(fscanf(fp, "%c %d\n", &job, &num) == 2){
		employ(job, num);
	}
	//printList();
	return;
}

void employ(char job, int num){
	if(job == 'i'){
		insert(num);
	}
	else if(job == 's'){
		search(num);
	}
	else{
		printf("ERROR AT JOB\n JOB = %c %d\n", job, num);
	}
	return;
}

void insert(int num){
	int keyVal = keyGen(num);
	if(table[keyVal] == NULL){
		table[keyVal] = new_item(num);
		printf("inserted\n");
		return;
	}
	struct item* tracer = table[keyVal];
	struct item* prev = table[keyVal];
	while(tracer != NULL){
		if(tracer->val == num){
			printf("duplicate\n");
			return;
		}
		prev = tracer;
		tracer = tracer->next;
	}
	prev->next = new_item(num);
	printf("inserted\n");
	return;
}

void search(int num){
	int keyVal = keyGen(num);
	if(table[keyVal] == NULL){
		printf("absent\n");
		return;
	}
	struct item* tracer = table[keyVal];
	while(tracer != NULL){
		if(tracer->val == num){
			printf("present\n");
			return;
		}
		tracer = tracer->next;
	}
	printf("absent\n");
	return;
}
