#include<stdio.h>
#include<stdlib.h>

struct node{
	int value;
	struct node* next;
};

void launch(char*);
void employ(char, int);
void insert(int);
void sAD(int); //search And Destroy
void printList();

struct node* head;
int i = 0;

int main(int argc, char **argv){
	if(argc != 2){
		printf("Invalid Input \n");
		return 0;
	}
	head = malloc(sizeof(struct node));
	head->next = NULL;
	launch(argv[1]);
	return 0;
}

void launch(char* argv){
	FILE *fp;
	fp = fopen(argv, "r");
	//printf("%s\n",argv);
	if(fp == NULL){
		printf("error\n");
		return;
	}
	
	fseek(fp, 0, SEEK_END);
	if (ftell(fp) == 0){
		printf("%d\n", 0);
	}
	fseek(fp, 0, SEEK_SET);

	char job;
	int num;
	while(fscanf(fp, "%c %d\n", &job, &num) == 2){
		//printf("employing %d\n",num);
		employ(job, num);
	}
	printList();
	return;
}

void employ(char job, int num){
	if (job == 'i'){
		//printf("inserting %d\n", num);
		insert(num);
		i++;
	}
	else if(job == 'd'){
		sAD(num);
	}
	else{
		printf("ERROR AT JOB\n JOB = %c\n",job);
		return;
	}
	return;
}

void insert(int num){
	if(head->next == NULL){
		//printf("new\n");
		struct node* newNode = (struct node*)malloc(sizeof(struct node));
		newNode->value = num;
		head->next = newNode;
		return;
	}
	struct node* current = head->next;
	struct node* tracer = head;
	while(current != NULL){
		if(current->value == num){
			i = i - 1;
			return;
		}
		if(current->value > num){
			struct node* newNode = (struct node*)malloc(sizeof(struct node));
			newNode->value = num;
			tracer->next = newNode;
			newNode->next = current;
			return;
		}
		tracer = current;
		current = current->next;
	}
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->value = num;
	tracer->next = newNode;
	return;
}

void sAD(int num){
	struct node* current = head->next;
	struct node* tracer = head;
	while(current != NULL){
		if(current->value == num){
			tracer->next = current->next;
			current = current->next;
			i = i - 1;
		}
		else{
			tracer = current;
			current = current->next;
		}
	}
	return;
}

void printList(){
	if(head->next == NULL){
		printf("%d\n",0);
		return;
	}
	head = head->next;
	printf("%d\n", i);
	while(head != NULL){
		printf("%d\t", head->value);
		head = head->next;
	}
	return;
}
