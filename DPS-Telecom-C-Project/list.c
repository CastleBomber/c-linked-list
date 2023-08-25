#include "list.h"

/**
 * Creates the whole initial linked list
 * Also allocates memory for nodes
 *
 * @param ws Pointer array of words to be added to linked list
 * @param wordCount Number of words
 * @return head Top of the linked list
 */
Node *createLinkedList(char **ws, int wordCount) {
  Node *head = NULL;
  Node *tmp = NULL;
  Node *p = NULL;
  char **_words = ws;

  for (int i = 0; i < wordCount; i++) {
    tmp = (Node *)malloc(sizeof(Node));
    tmp->wordLength = getWordLength(_words[i]);
    tmp->subName = setSubName(_words[i]);
    tmp->next = NULL;

    // Assign head at first run
    if (head == NULL) {
      head = tmp;
    } else {
      // Assign a ptr to the top
      p = head;

      // Iterate to the end of the list
      while (p->next != NULL) {
        p = p->next;
      }

      // Add the new item at the end
      p->next = tmp;
    }
  }

  return head;
}

/**
 * Creates a new node
 *
 * @param lookup Word that will be the subName of returned node
 * @return newNode New node
 */
Node *createNewNode(char *lookup) {
  Node *newNode = NULL;

  newNode = (Node *)calloc(1, (sizeof(Node)));
  newNode->subName = setSubName(lookup);
  newNode->wordLength = getWordLength(lookup);
  newNode->next = NULL;

  return newNode;
}

/**
 * Sorts linked list
 * Uses sortLinkedListPartial()
 *
 * @param _head Initial top
 * @return Head New pointer to top of linked list
 */
Node *sortLinkedList(Node *_head) {
  Node *head = NULL;
  int nodeCount = 0;

  head = _head;
  nodeCount = getNodeCount(head);

  for (int i = 0; i < nodeCount; i++) {
    head = sortLinkedListPartial(head);
  }

  return head;
}

/**
 * Only sorts partially
 * Used by sortLinkedList()
 *
 * @param _head Initial top
 * @return Head New pointer to top of linked list
 */
Node *sortLinkedListPartial(Node *_head) {
  Node *head = NULL;
  Node *curHead = NULL;
  Node *node1 = NULL;
  Node *node2 = NULL;
  Node *trail = NULL;
  Node *tmp = NULL;
  int nodeCount = 0;

  head = _head;
  curHead = _head;

  while (curHead != NULL) {
    node1 = curHead;

    while (node1->next != NULL) {
      node2 = node1->next;

      if (greaterThanCheck(node1, node2)) {
        if (node1 == head) { // Handle front node case swap
          head = node2;
        } else {               // Handle middle node case swap
          trail->next = node2; // Edit left node's next
        }

        tmp = node2; // Reassign node pointers
        node1->next = node2->next;
        node2->next = node1;
        node1 = tmp;
      }

      trail = node1;
      node1 = node1->next; // Move to next
    }

    trail = curHead;
    curHead = curHead->next; // Move to next
  }

  return head;
}

/**
 * Simply appends new word to end of list if it does not already exists
 * Will later call the sort function to put it in it proper place
 *
 * @param _head Initial top
 * @param lookup Word used to create new new node
 * @return head New pointer to top of linked list
 */
Node *addToLinkedList(Node *_head, char *lookup) {
  Node *head = NULL;
  Node *curHead = NULL;
  int alreadyExists = 0;
  Node *tmp = NULL;

  head = _head;
  curHead = _head;

  alreadyExists = searchReturnTrueFalse(head, lookup);

  if (alreadyExists) {
    printf("Word is already in the list");
  }

  // Create Node
  tmp = createNewNode(lookup);

  // Append to end of a full list
  while (curHead != NULL) {
    if (curHead->next == NULL) {
      curHead->next = tmp;
      printf("Word added successfully!\n");
      return head;
    }

    curHead = curHead->next;
  }

  // Handle case with empty list
  if (head == NULL) {
    head = tmp;
    printf("Word added successfully!\n");
    return head;
  }
}

/**
 * Frees old list, simulates starting the linked list over
 * Frees up node's allocated memory, as well as node's subname
 *
 * @param _head Initial top
 * @return newHead Fresh pointer to NULL
 */
Node *reinitializeLinkedList(Node *_head) {
  Node *newHead = NULL;
  Node *curHead = NULL;
  Node *upcoming = NULL;

  curHead = _head;

  while (curHead != NULL) {
    upcoming = curHead->next;
    free(curHead->subName);
    free(curHead);

    curHead = upcoming;
  }

  return newHead;
}

/**
 * Initial memory allocation
 *
 * @return words Pointer to newly created word's memory block
 */
char **allocateWordsMemory() {
  char **_words;
  _words = (char **)calloc(MAX_WORDS,
                           sizeof(char *)); // Space for words's rows

  for (int row = 0; row < MAX_WORDS; row++) {
    _words[row] =
        (char *)calloc(MAX_LETTERS, sizeof(char *)); // Space for words's cols
  }

  return _words;
}

/**
 *  Allocates memory for the node's subname
 *
 * @param _response Input from the user
 * @param _ws Words
 * @return subName Stored name, up to four characters
 */
char **setWords(char _response[], char **_ws) {
  char **_words = _ws;
  char *word;
  int letterPos = 0;
  int wordPos = 0;
  int r = 0;

  word = calloc(MAX_LETTERS, sizeof(char)); // Space for letters

  // Parse response for words
  while (_response[r] != '\n') {
    // Build word if letter given
    if (_response[r] != ' ') {
      word[letterPos] = _response[r];
      letterPos++;
    }

    if (_response[r] == ' ' || _response[r + 1] == '\n') {
      // Add word to words
      _words[wordPos] = word;

      // Reset word build
      word = calloc(MAX_LETTERS, sizeof(char));
      letterPos = 0;
      wordPos++;
    }

    r++;
  }

  free(word);

  return _words;
}

/**
 *  Allocates memory for the node's subname
 *
 * @param w Word
 * @return subName Stored name, up to four characters
 */
char *setSubName(char *w) {
  char *subname;
  char *word = w;
  int wordLength = 0;
  int i = 0;

  wordLength = getWordLength(w);

  subname = (char *)calloc(MAX_SUBNAME, sizeof(char));

  while ((i < wordLength) && (i < MAX_SUBNAME)) {
    subname[i] = w[i];
    i++;
  }

  return subname;
}

int getNodeCount(Node *head) {
  int count = 0;
  Node *cur = NULL;
  Node *tmp = NULL;

  cur = head;
  tmp = cur->next;

  while (cur != NULL) {
    count++;
    cur = cur->next;
  }

  return count;
}

int getWordLength(char *w) {
  int wordLength = 0;
  char *word = w;

  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == '\n') {
      word[i] = '\0';

    } else {
      wordLength++;
    }
  }

  return wordLength;
}

int getWordCount(char _response[]) {
  int count = 0;
  int r = 0;

  while (_response[r] != '\n') {
    if (_response[r] == ' ') {
      count++;
    }

    r++;

    // Catch the last word
    if (_response[r] == '\n') {
      count++;
    }
  }

  return count;
}

int greaterThanCheck(Node *_cur, Node *_tmp) {
  char *a = NULL;
  char *b = NULL;
  int aIsGreaterThanB = 0;
  int lengthA = 0;
  int lengthB = 0;
  int maxLoops = 0;
  int i = 0;

  a = _cur->subName;
  b = _tmp->subName;

  // Determine the shortest word
  lengthA = getWordLength(a);
  lengthB = getWordLength(b);
  if (lengthA < lengthB) {
    maxLoops = lengthA;
  } else if (lengthA > lengthB) {
    maxLoops = lengthB;
  } else {
    maxLoops = lengthA;
  }

  // Easy case of different first letters
  if (a[i] > b[i]) {
    aIsGreaterThanB = 1;
    return aIsGreaterThanB;
  } else if (a[i] < b[i]) {
    return aIsGreaterThanB;
  }

  // Bypasses same letters to find if greater
  for (int j = 0; j < maxLoops; j++) {
    if (a[j] > b[j]) {
      aIsGreaterThanB = 1;
      return aIsGreaterThanB;
    } else if (a[j] < b[j]) {
      return aIsGreaterThanB;
    }
  }

  // They are the same, return 0
  return aIsGreaterThanB;
}

/**
 *  Displays menu with all available options
 *
 * @param _head Initial top
 */
void displayMenu(Node *_head) {
  Node *head = NULL;
  char *word = NULL;
  char response[MAX_LETTERS] = "";
  char option = "";
  int keepGoing = 1;

  head = _head;
  word = (char *)calloc(MAX_LETTERS, sizeof(char *));

  while (keepGoing) {
    printf("\n[Menu Options]\n");
    printf("1) Lookup a word (case sensitive)\n");
    printf("2) Lookup a word (case insensitive)\n");
    printf("3) Add a word\n");
    printf("4) Reinitialize the entire list\n");

    fgets(response, MAX_LETTERS, stdin);
    option = response[0];

    switch (option) {
    case '1':
      printf("Lookup word: ");
      fgets(word, MAX_LETTERS, stdin);
      search(head, word); // sensitive, exact match
      break;
    case '2':
      printf("Lookup word: ");
      fgets(word, MAX_LETTERS, stdin);
      searchCaseInsensitive(head, word);
      break;
    case '3':
      printf("Word to add: \n");
      fgets(word, MAX_LETTERS, stdin);
      head = addToLinkedList(head, word);
      head = sortLinkedList(head);
      break;
    case '4':
      printf("Reinitializing list.\n");
      head = reinitializeLinkedList(head);
      break;
    default:
      printf("Did not recognize menu option.\n");
      printf("Please try again.\n");
    }
  }
}

/**
 * Searches for an exact match
 * Case sensitive
 * Matches first four characters
 *
 * @param _head Initial top
 * @param lookup Searched word, given by the user
 */
void search(Node *_head, char *lookup) {
  Node *cur = NULL;
  char *curSubName = NULL;
  char *lookupSubName = NULL;
  int lookupWordLenth = 0;
  int curWordLength = 0;
  int found = 0;

  cur = _head;

  lookupSubName = setSubName(lookup);
  lookupWordLenth = getWordLength(lookup);

  while (cur != NULL) {
    curSubName = cur->subName;
    curWordLength = cur->wordLength;

    if (compareWordMatch(curSubName, lookupSubName)) {
      found = 1;
      printf("Found a match!\n");
      printf("Word: %s\n", curSubName);
      printf("Length: %d\n", curWordLength);
      break;
    }

    cur = cur->next;
  }

  if (!found) {
    printf("No match found\n");
  }
}

/**
 * Searches for an exact match
 * Case sensitive
 * Matches first four characters
 *
 * @param _head Initial top
 * @param lookup Searched word, given by the user
 * @return found True if the word exists, false otherwise
 */
int searchReturnTrueFalse(Node *_head, char *lookup) {
  Node *cur = NULL;
  char *curSubName = NULL;
  char *lookupSubName = NULL;
  int lookupWordLenth = 0;
  int curWordLength = 0;
  int found = 0;

  cur = _head;

  lookupSubName = setSubName(lookup);
  lookupWordLenth = getWordLength(lookup);

  while (cur != NULL) {
    curSubName = cur->subName;
    curWordLength = cur->wordLength;

    if (compareWordMatch(curSubName, lookupSubName)) {
      return found;
    }

    cur = cur->next;
  }

  return found;
}

/**
 * Searches for a match, does not necessarilly need to be an exact match
 * Case Insensitive
 *
 * Ex:  A == a   is a match
 *
 * @param _head Initial top
 * @param lookup Searched word, given by the user
 */
void searchCaseInsensitive(Node *_head, char *lookup) {
  Node *cur = NULL;
  char *curSubName = NULL;
  char *lookupSubName = NULL;
  int lookupWordLenth = 0;
  int curWordLength = 0;
  int found = 0;

  cur = _head;

  lookupSubName = setSubName(lookup);
  lookupWordLenth = getWordLength(lookup);

  while (cur != NULL) {
    curSubName = cur->subName;
    curWordLength = cur->wordLength;

    if (compareWordMatchInsensitive(curSubName, lookupSubName)) {
      found = 1;
      printf("Found a match!\n");
      printf("Word: %s\n", curSubName);
      printf("Length: %d\n", curWordLength);
      break;
    }

    cur = cur->next;
  }

  if (!found) {
    printf("No match found\n");
  }
}

/**
 * Check if they match
 *
 * @param a First word
 * @param b Second word
 * @return matchWords Returns true if the sub names and length match
 */
int compareWordMatch(char *a, char *b) {
  int matchWords = 0;
  int matchedLetters = 0;
  int wordLengthA = 0;
  int wordLengthB = 0;
  int i = 0;

  wordLengthA = getWordLength(a);
  wordLengthB = getWordLength(b);

  // End if they are not the same legnth
  if (wordLengthA != wordLengthB) {
    return matchWords;
  }

  while (i < wordLengthA) {
    if (a[i] == b[i]) {
      matchedLetters++;
    }

    i++;
  }

  if (matchedLetters == wordLengthA) {
    matchWords = 1;
  }

  return matchWords;
}

/**
 * Checks if they match
 * Captial letters do not matter
 *
 * @param a First word
 * @param b Second word
 * @return true if the sub names and length match
 */
int compareWordMatchInsensitive(char *a, char *b) {
  int matchWords = 0;
  int matchedLetters = 0;
  int wordLengthA = 0;
  int wordLengthB = 0;
  int i = 0;

  wordLengthA = getWordLength(a);
  wordLengthB = getWordLength(b);

  // End if they are not the same legnth
  if (wordLengthA != wordLengthB) {
    return matchWords;
  }

  while (i < wordLengthA) {
    if (toupper(a[i]) == toupper(b[i])) {
      matchedLetters++;
    }

    i++;
  }

  if (matchedLetters == wordLengthA) {
    matchWords = 1;
  }

  return matchWords;
}

/**
 * Frees allocated memory from words
 *
 * @param ws Word to be freed
 */
void freePointers(char **ws) {

  for (int i = 0; i < MAX_WORDS; i++) {
    free(ws[i]);
  }

  free(ws);
}