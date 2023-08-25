#ifndef MAIN_H_
#define MAIN_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Row vs Col
#define MAX_WORDS 20
#define MAX_LETTERS 20
#define MAX_SUBNAME 4

// Linked list dictionary for all the given words
typedef struct Node {
  int wordLength;
  char *subName;
  struct Node *next;
} Node;

Node *createLinkedList(char **ws, int wordCount);
Node *createNewNode(char *lookup);
Node *sortLinkedList(Node *_head);
Node *sortLinkedListPartial(Node *_head);
Node *addToLinkedList(Node *_head, char *lookup);
Node *reinitializeLinkedList(Node *_head);
char **allocateWordsMemory();
char **setWords(char _response[], char **_ws);
char *setSubName(char *w);
int getNodeCount(Node *head);
int getWordLength(char *w);
int getWordCount(char _response[]);
int greaterThanCheck(Node *_cur, Node *_tmp);
void displayMenu();
void search(Node *_head, char *lookup);
int searchReturnTrueFalse(Node *_head, char *lookup);
void searchCaseInsensitive(Node *_head, char *lookup);
int compareWordMatch(char *a, char *b);
int compareWordMatchInsensitive(char *a, char *b);
void freePointers(char **ws);
void add();
void del();

#endif