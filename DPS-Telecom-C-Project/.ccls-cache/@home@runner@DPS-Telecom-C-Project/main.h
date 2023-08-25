#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#define MAX 100

class LinkedList {
  struct Node {
    char wordLength[MAX];
    char firstFour[4];

    const char *key;
    int value;
  };
};

typedef struct node {
  int data;

  struct node *next;
} node;

void createLinkedList();
void add();
void del();

#endif