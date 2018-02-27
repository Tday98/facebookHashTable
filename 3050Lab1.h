#ifndef lab1_H_
#define lab1_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct personstruct{
  char* name;
  char* key;
  struct personstruct *next;
} Person;

typedef struct hTable {
  int size;
  int num_elements;
  struct personstruct **table;
} HashTable;

unsigned long hash(unsigned char *str);
HashTable* createTable(int, int);
void destroyTable(HashTable*);
char* printTable(HashTable*,char*);
void insertTable(HashTable*, unsigned char*, char*);
void createPerson(HashTable*, char*);
bool isFriend(char*, char*);
int beFriend(char*, char*);
int unFriend(char*, char*);
void printFriends(char*);

#endif