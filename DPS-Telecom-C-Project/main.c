/**
 * Author: Richie CastleBomber
 * Date: June 26th, 2023
 *
 * DPS Telecom
 * Programming Challenge: Overview and Spec
 *
 * Notes
 * Replit
 * Menu - cmd+j
 * Code folding - Toggle all folds from menu option
 *
 */

#include "list.h"

int main(void) {
  // FILE *fp;
  char response[MAX_WORDS * MAX_LETTERS] = "";
  char **words;
  int wordCount;

  //  Takes in a sentence || Open file and get response
  printf("What's words would you like stored?: ");
  // fp = fopen("input.txt", "r");
  // fgets(response, MAX_WORDS * MAX_LETTERS, fp);
  fgets(response, MAX_WORDS * MAX_LETTERS, stdin);
  // fclose(fp);

  // Set Words
  words = allocateWordsMemory();
  words = setWords(response, words);
  wordCount = getWordCount(response);

  // Create linked list and sort
  Node *root = NULL;
  root = createLinkedList(words, wordCount);
  root = sortLinkedList(root);

  // Display Menu
  displayMenu(root);

  freePointers(words);

  return 0;
}