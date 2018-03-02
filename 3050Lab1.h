#ifndef lab1_H_
#define lab1_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct personstruct{
  char* name;
  char* key;
  char* arrayOfFriends[50];
} Person;

typedef struct hTable {
  int size;
  int num_elements;
  struct personstruct **table;
} HashTable;

unsigned long hash(unsigned char *str);
HashTable* createTable(int, int);
Person* findName(HashTable*,char*,char*);
void insertTable(HashTable*, unsigned char*, char*);
void createPerson(HashTable*, char*);
bool isFriend(HashTable*, char*, char*);
int beFriend(HashTable*, char*, char*);
int unFriend(HashTable*, char*, char*);
void printFriends(HashTable*, char*);

#endif