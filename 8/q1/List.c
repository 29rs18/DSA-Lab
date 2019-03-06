#include "List.h"


void* myalloc(int size){
	globalCounter+=size+sizeof(int);
	int* asd = (int*)malloc(size+sizeof(int));
	*asd = size+sizeof(int);
	return (((void*)asd)+sizeof(int));
}

void myfree(void* x){
	int* toread = (int*)(x-sizeof(int));
	int size = *toread;
	globalCounter-=size;
	free(toread);
}


void insertAtEnd(List myList,Node myNode){
	myNode->next = NULL;
	if(myList->count==0){
		myList->count=1;
		myList->first = myList->last = myNode;
		return;
	}
	else{
		(myList->count)++;
		myList->last->next = myNode;
		myList->last = myNode;
	}
}

List createList(Student studArray, int arraySize){
	List myList = myalloc(sizeof(struct list));
	myList->first = myList->last = NULL;
	myList->count = 0;

	for(int i=0;i<arraySize;i++){
		//create a node with the student
		Node myNode = myalloc(sizeof(struct node));
		myNode->record = &studArray[i];

		//insert in a constant time operation
		insertAtEnd(myList, myNode);
	}
	return myList;
}

void insertInOrder(List list, Node newNode){	
	if(list->count==0){
		insertAtEnd(list, newNode);
		return;
	}

	Node temp = list->first;
	Node prev = NULL;
	while(temp && (newNode->record)->marks > (temp->record)->marks){
		prev =  temp;
		temp = temp->next;
	}

	(list->count)++;
	if(prev==NULL){
		newNode->next = list->first;
		list->first = newNode;
	}
	else if(prev==list->last){
		(list->last)->next = newNode;
		list->last = newNode;
		newNode->next = NULL;
	}
	else{
		prev->next = newNode;
		newNode->next = temp;
	}
	return;
}

List insertionSort(List list){
	List newList = myalloc(sizeof(struct list));
	newList->first = newList->last = NULL;
	newList->count = 0;

	Node temp = list->first;
	Node nextNode;
	while(temp){
		nextNode = temp->next; // I have to read this before the call to insertInOrder, because insertInOrder will modify temp->next
		insertInOrder(newList, temp);
		temp = nextNode;
	}

	return newList;
}

double measureSortingTime(List list){

	struct timeval t1,t2;
	double elapsedTime;

	gettimeofday(&t1,NULL);
	insertionSort(list);
	gettimeofday(&t2,NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	return elapsedTime;
}