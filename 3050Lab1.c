#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include "3050Lab1.h"

unsigned long
hash(unsigned char *str) // Hash function djb2 that was designed by dan bernstein
{
        unsigned long hash = 5381;
        int c;

        while ((c = *str++) != 0)
            hash = ((hash << 5) + hash) + c; // hash * 33 + c 

     return hash%13;
}

HashTable* createTable(int size, int num_elements) {
	HashTable *t;

	t = malloc(sizeof(*t));

	assert(t != 0);

	t->size = size;
	t->num_elements = num_elements;
	t->table = malloc(sizeof(struct personstruct *) * size);

	assert(t->table != 0);

	for (int i = 0; i < size; i++) { t->table[i] = 0; }

	return t;
}

void destroyTable(HashTable *t) {
	struct personstruct *p;
	struct personstruct *next;

	for(int i = 0; i < t->size; i++) {
		for(p = t->table[i]; p != 0; p = next) {
			next = p->next;
			if (p != NULL) {
				free(p->name);
				free(p->key);
				free(p);
			}
		}
	}

	free(t->table);
	free(t);

}

char* printTable(HashTable *t, char* key) {
	struct personstruct *p;

	for(p = t->table[hash((unsigned char *)key)]; p != 0; p = p->next) {
		if(strcmp((p->key),key)) {
			return p->name;
		}
	}
	return "";
}

void insertTable(HashTable *t, unsigned char *key, char *name) {
	struct personstruct *p;
	unsigned long hashN;

	assert(key);
	assert(name);

	p = malloc(sizeof(*p));

	assert(p);

	p->key = (char*) key;
	p->name = (char*) name;

	hashN = hash(key);

	p->next = t->table[hashN];
	t->table[hashN] = p;

	t->num_elements++;

	printf("%s has been inserted into the table.\n",name);
}

void createPerson(HashTable *t, char* input) {

	char capInput[255];
	char *realInput = malloc(sizeof(char) * 255);

	strcpy(capInput, input);
	strcpy(realInput,input);

	printf("%s\n", input);
	for(int i = 0; i < strlen(capInput); i++) {
		capInput[i] = toupper(capInput[i]);
	}
	printf("%s\n",capInput);
	printf("%s\n",input);
	int hashed = hash((unsigned char*) capInput);
	printf("%d\n", hashed);

	insertTable(t,(unsigned char *)capInput,realInput);
	char* name = printTable(t,"SAM");
	printf("%s\n",name);
}

/*bool isFriend(Person*) {

}

int beFriend(Person*, Person*) {

}

int unFriend(Person*, Person*) {

}

void printFriends(Person*) {

}*/

int main() {

	//char input[255];
	char *input = malloc(sizeof(char) * 255);
	char *token = NULL;

	int max = 13;
	int hash_size = 0;

	HashTable *table = NULL;

	table = createTable(max, hash_size);

	while(true) {

		printf("Command: ");
  		if(fgets(input,255,stdin)) {
  		
  			printf("%s",input);

  			token = strtok(input, " \n\t");
  			*token = toupper(*token);

  			if(strcmp(token,"P") == 0) {
  				// TODO createPerson();
  				printf("CREATING A PERSON :)\n");
  				createPerson(table, strtok(NULL, " \t\n"));
  			}
			else if(strcmp(token,"F") == 0) {
				// TODO beFriend();
				printf("Friending someone.\n");
			}

			else if(strcmp(token,"U") == 0) {
				// TODO unFriend();
				printf("Unfriending someone.\n");
			}

			else if(strcmp(token,"L") == 0) {
				// TODO printFriends();
				printf("Printing out all friends of specified person\n");
			}

			else if(strcmp(token,"Q") == 0) {
				// TODO isFriend();
				printf("Are these two people friends?\n");
			}

			else if(strcmp(token,"X") == 0) {
				break;
			} else {
				printf("That is not a proper command!\n");
			}
		} else {
			printf("What you entered is invalid\n");
		}
		
	}

	struct personstruct *p;
	struct hTable *t;
	t = table;
	p = t->table[hash((unsigned char *)("SAM"))];
	//printf("%s",t->table[hash((unsigned char *)("SAM"))]);

	char* name = printTable(table,"SAM");
	printf("%s\n",name);
	//destroyTable(&table);
	return 0;
}