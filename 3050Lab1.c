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

// Creates the hashtable and sets the size and number of elements accordingly.
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

/* So this is a cool function that I designed. 
* It is able to find a person given its name (provided there are no duplicates)
* Even if it is not in the position it should be (given collisions)
* It is using linear probing until it finds the proper name otherwise the name is not in the table.
*/
Person* findName(HashTable *t, char* key, char* name) {
	struct personstruct *p = NULL;

	unsigned long hash1 = hash((unsigned char*) key);
	unsigned long hash2 = hash((unsigned char*) key);

	while (true) {
		p = t->table[hash2];
		if(strcmp((p->name),name) == 0) {
			return p;
		} else {
			hash2++;
			if (hash2 > 12) hash2 = 0;
			printf("\n%lu\n",hash2);
		}
		if (hash2 == hash1) break;
	}
	return NULL;
}

// Classic insert into hash table function. Uses that hash function discussed above.
void insertTable(HashTable *t, unsigned char *key, char *name) {
	struct personstruct *p;
	unsigned long hashN;

	if (t->num_elements >= t->size) {
		printf("The table is full!\n");
		return;
	}

	assert(key);
	assert(name);

	p = malloc(sizeof(*p));

	assert(p);

	p->key = (char*) key;
	p->name = (char*) name;

	hashN = hash(key);
	while (t->table[hashN] != NULL) {
		hashN++;
		if (hashN > 12) hashN = 0;
	}
	t->table[hashN] = p;
	printf("%lu\n", hashN);

	t->num_elements++;

	printf("%s has been inserted into the table.\n",name);
}
// Creates a person and makes the name be all caps to keep consistency
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

	insertTable(t,(unsigned char *)capInput,realInput);
}

// This goes through the array to make sure two people are friends
bool isFriend(HashTable *t, char* name, char* name2) {
	char capInput[255];

	struct personstruct *p;

	strcpy(capInput, name);

	for(int i = 0; i < strlen(capInput); i++) {
		capInput[i] = toupper(capInput[i]);
	}

	p = findName(t,capInput,name);

	int loop = 0;

	while(true) {
		if (strcmp(p->arrayOfFriends[loop],name2) == 0) {
			return true;
		}
		loop++;
	}
	return false;
}

int beFriend(HashTable *t, char* name, char* name2) {
	char capInput[255];
	char capInput2[255];

	strcpy(capInput, name);
	strcpy(capInput2, name2);

	struct personstruct *p;

	struct personstruct *p2;

	for(int i = 0; i < strlen(capInput); i++) {
		capInput[i] = toupper(capInput[i]);
	}

	for(int j = 0; j < strlen(capInput2); j++) {
		capInput2[j] = toupper(capInput2[j]);
	}

	int i = 0;

	int j = 0;

	p = findName(t,capInput,name);
	p2 = findName(t,capInput2, name2);

	printf("Adding %s to %s's friend list\n", name, name2);
	while(true) {
		if (p->arrayOfFriends[i] == NULL) {
			p->arrayOfFriends[i] = p2->name;
			break;
		}

		else if (strcmp(p->arrayOfFriends[i],p->name) == 0) {
			printf("These two are already friends!\n");
			break;
		}
		i++;
	}

	printf("%s\n\n",p->arrayOfFriends[i]);

	printf("Adding %s to %s's friend list\n", name, name2);
	while(true) {
		if (p2->arrayOfFriends[j] == NULL) {
			p2->arrayOfFriends[j] = p->name;
			break;
		}

		else if (strcmp(p2->arrayOfFriends[j],p->name) == 0) {
			printf("These two are already friends!\n");
			break;
		}

		j++;
	}

	printf("%s\n\n",p2->arrayOfFriends[j]);

	printf("Success! %s and %s are now friends\n", name, name2);
	return 1;
}
// Removes the specified name from the table if it can find it.
int unFriend(HashTable *t, char* name, char* name2) {
	char capInput[255];

	struct personstruct *p;

	strcpy(capInput, name);

	for(int i = 0; i < strlen(capInput); i++) {
		capInput[i] = toupper(capInput[i]);
	}

	p = findName(t,capInput,name);

	int loop = 0;
	int i = 0;
	int z = 0;

	char* newArray[50];

	while(p->arrayOfFriends[loop] != NULL) {
		if (strcmp(p->arrayOfFriends[loop],name2) == 0) {
			p->arrayOfFriends[loop] = NULL;
		} else {
			newArray[i] = p->arrayOfFriends[loop];
			i++;
		}
		loop++;
	}

	while(z < (loop-1)) {
		p->arrayOfFriends[z] = newArray[z];
		z++;
	}
	p->arrayOfFriends[z] = NULL;
	return 0;
}

void printFriends(HashTable *t, char* name) {
	char capInput[255];

	strcpy(capInput, name);

	struct personstruct *p;

	int j = 0;

	for(int i = 0; i < strlen(capInput); i++) {
		capInput[i] = toupper(capInput[i]);
	}

	p = findName(t, capInput, name);

	printf("%s's friends are: ", name);
	while (p->arrayOfFriends[j] != NULL) {
		printf("%s, ",p->arrayOfFriends[j]);
		j++;
	}
	printf("\n");
}

int main() {

	char *input = malloc(sizeof(char) * 255);
	char *token = NULL;

	char *name1 = malloc(sizeof(char) * 255);
	char *name2 = malloc(sizeof(char) * 255);

	int max = 13;
	int hash_size = 0;

	HashTable *table = NULL;

	table = createTable(max, hash_size);

	while(true) {

		printf("Command: ");
  		if(fgets(input,255,stdin)) {

  			token = strtok(input, " \n\t");
  			*token = toupper(*token);

  			if(strcmp(token,"P") == 0) {
  				if ((name1 = strtok(NULL, " \t\n")) == NULL) {printf("You need to supply one input...\n"); continue;}
  				else {
  					printf("CREATING A PERSON :)\n");
  					createPerson(table, name1);
  				}
  			}

			else if(strcmp(token,"F") == 0) {
				if ((name1 = strtok(NULL, " \t\n")) == NULL || (name2 = strtok(NULL, " \t\n")) == NULL) {printf("You need to supply two inputs...\n"); continue;}
				else {
				printf("Friending someone.\n");
				beFriend(table, name1, name2);
				}
			}

			else if(strcmp(token,"U") == 0) {
				if ((name1 = strtok(NULL, " \t\n")) == NULL || (name2 = strtok(NULL, " \t\n")) == NULL) {printf("You need to supply two inputs...\n"); continue;}
				else {
					printf("Unfriending someone.\n");
					unFriend(table, name1, name2);
				}
			}

			else if(strcmp(token,"L") == 0) {
				if ((name1 = strtok(NULL, " \t\n")) == NULL) {printf("You need to supply one input...\n"); continue;}
				else {
					printFriends(table, name1);
					printf("Printing out all friends of specified person\n");
				}
			}

			else if(strcmp(token,"Q") == 0) {
				if ((name1 = strtok(NULL, " \t\n")) == NULL || (name2 = strtok(NULL, " \t\n")) == NULL) {printf("You need to supply two inputs...\n"); continue;}
				else {
					bool answer = isFriend(table, name1, name2);
					printf("Are these two people friends?\n");
					if (answer) {
						printf("Yes they are friends.\n");
					} else {
						printf("No they are not friends.\n");
					}
				}
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

	printf("Thank you for using this hashtable!\n");

	free(input);
	free(table);
	return 0;
}