#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;
	struct node* left;
	struct node* right;
	int height;
	int h;
};

void add(struct node*, struct node*);
void search(int);
void cleanUp(struct node*);
void employ(char, int);
void launch(char*);

struct node* head;

int main(int argc, char **argv){
	if(argc != 2){
		printf("error\n");
		return 0;
	}
	head = malloc(sizeof(struct node));
	head->h = 1;
	head->left = NULL;
	head->right = NULL;
	head->height = 0;
	launch(argv[1]);
	cleanUp(head);
	return 0;
}

void launch(char *argv){
	FILE *fp;
	fp = fopen(argv, "r");
	if (fp == NULL){
		printf("error\n");
		return;
	}
	
	char job;
	int num;
	while(fscanf(fp, "%c %d\n", &job, &num) == 2){
		employ(job, num);
	}
	return;
}

void employ(char job, int num){
	if(job == 'i'){
		struct node* newNode = (struct node*) malloc (sizeof(struct node));
		newNode->val = num;
		add(newNode, head);
	}
	else if(job == 's'){
		search(num);
	}
	else{
		//printf("ERROR AT JOB SELECTION");
	}
	return;
}

void add(struct node* newNode, struct node* base){
	if(base->h == 1 && base->left == NULL){
		base->left = newNode;
		newNode->height = 1;
		printf("inserted %d\n", 1);
		return;
	}
	else if(base->h == 1){
		base = base->left;
	}
	newNode->height = base->height + 1;
	if(newNode->val == base->val){
		printf("duplicate\n");
		return;
	}
	else if(newNode->val < base->val){
		if(base->left == NULL){
			base->left = newNode;
			printf("inserted %d\n", newNode->height);
			return;
		}
		else{
			add(newNode, base->left);
			return;
		}
	}
	else{
		if(base->right == NULL){
			base->right = newNode;
			printf("inserted %d\n", newNode->height);
			return;
		}
		else{
			add(newNode, base->right);
			return;
		}
	}
}

void search(int num){
	struct node* tracer = head->left;
	while(tracer != NULL){
		if(tracer->val == num){
			printf("present %d\n", tracer->height);
			return;
		}
		else if(tracer->val > num){
			tracer = tracer->left;
		}
		else{
			tracer = tracer->right;
		}
	}
	printf("absent\n");
	return;
}

void cleanUp(struct node* toClean){
	if(toClean == NULL){
		return;
	}
	cleanUp(toClean->left);
	cleanUp(toClean->right);
	free(toClean);
}
