
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "wset.h"

/**
 * The WordNode struct is used to represent a node in a linked
 * list of words. It is defined in this file because it is
 * used only within this file. It is used only as part of the
 implementation of a word set.
 */
typedef struct WordNode WordNode;
struct WordNode {
  int       freq;   // The frequency of the the word.
  char*     word;   // The word itself.
  WordNode* next;   // The next word node in the list.
};

/**
 * A WordSet struct is used to represent a "set". We are
 * implementing a set as a linked list of WordNodes.
 */
struct WordSet {
  int       size;   // The number of elements in the set.
  WordNode* head;   // The starting node in the set.
};

/**
 * The node_free function is used to free a WordNode object.
 */
static void node_free(WordNode* n) {
  if (n != NULL) {
    free(n->word);
    free(n);
  }
}

/**
 * The node_free_all function is used to free a list of 
 * WordNode objects.
 */
static void node_free_all(WordNode* n) {
  if (n != NULL) {
    node_free_all(n->next);
    node_free(n);
  }
}

/**
 * The node_new function is used to create a new WordNode object.
 */
static WordNode* node_new(char* word) {
  WordNode* n = (WordNode*) malloc(sizeof(WordNode));
  n->freq = 0;
  int length = strlen(word);
  n->word = (char*) malloc(length+1);
  memcpy(n->word, word, length+1);
  n->next = NULL;
  return n;
}

/**
 * The wset_new function is used to create a new WordSet object.
 */
WordSet* wset_new() {
  // TODO: Allocate a new WordSet object using `malloc`. Make sure you
  // initialize it properly to avoid possible errors or confusion.
WordSet* newnode = (WordSet*) malloc(sizeof(WordSet));
newnode->size = 0 ;
newnode->head =NULL ;
 // return NULL;
return newnode ;
}

/**
 * The wset_free function is used to free a WordSet object.
 */
void wset_free(WordSet* wset) {
  // TODO: Deallocate a WordSet object using `free`.
free(wset);
 
}

/**
 * Returns the number of distinct words in the set.
 */
int wset_size(WordSet* wset) {
  return wset->size;
}

/**
 * The wset_add function is used to add a new WordNode object to the
 * set if it does not exist. If it does not exist we create a new
 * WordNode and add it to the set - making sure to update its
 * frequency to 1. If it does exist we increment its frequency. The
 * function returns the frequency of the word.
 */
int wset_add(WordSet* wset, char* word) {
  // TODO: The goal of this function is to add the word `word` to the
  // WordSet. The set implementation is simply a linked list of
  // WordNode's. If a WordNode object does not exist for the given
  // word you must create a new WordNode object, initialize its
  // frequency to 1, and add it to the set. 
  //
  // If the word is in the set already then you simply update its
  // frequency. This function returns the frequency of the word.
  //
  // HINTS: Make sure to check for special cases such as an empty
  // set. You should use the `strncmp` function to compare words in
  // the set. Use the `man` command to learn more about this
  // function.

WordNode* b  ;
WordNode* n ;
n= wset->head ;
//b=n;
if(n == NULL){
n = node_new(word);
n->freq++;
wset->size++;
wset->head = n ;
n->word =word ;

return n->freq;

}
while(n != NULL){

//b = n;
if (strcmp( n->word, word)==0){
//	i=i+(n->freq) ;
	n->freq++ ;
		 
	return n->freq ;


	}
b=n;
n = n->next;
}


WordNode*h= node_new(word);

b->next = h;  //point head node to new node ................................................... 
h->freq++ ;
wset->size++;
h->word = word;
return h->freq;
}

/**
 * The wset_fast_add function adds a new word to the set if it does
 * not exist. In addition if the word does exist in the set it will
 * move the WordNode object to the front of the linked list. This will
 * improve performance of adding words to the set and incrementing
 * their frequency because the most frequently accessed nodes will
 * percolate to the front of the list. Thus, this will result in
 * shorter search times. The function returns the frequency of the
 * word.
 */
int wset_fast_add(WordSet* wset, char* word) {
  // TODO: Implement a fast add function. This function will also add
  // words to the set if they do not exist or update the word's
  // frequency if it is already in the set. In addition, if the word
  // already exists in the set you must move the associated WordNode
  // object to the front of the list. This will result in frequently
  // seen words residing at the beginning of the list - which will
  // reduce the amount of time it takes to find them.
  //
  // This function is used by the wordfreq-fast.c program.
  //
  // HINTS: Make sure to check for special cases such as an empty
  // set. You should use the `strncmp` function to compare words in
  // the set. Use the `man` command to learn more about this
  // function.

WordNode* b  ;
WordNode* n ;
WordNode* j;
WordNode* k ;
n= wset->head ;
//j= n->next;
b=n;
if(n == NULL){
n = node_new(word);
wset->size++;
n->freq++ ;
n->word = word;
wset->head = n ;
return n->freq ;
}



while(n != NULL){

//b = n;
if (strcmp( n->word, word)==0){
//      i=i+(n->freq) ;
        n->freq++ ;
	
//	if (n->next != NULL){
//	k= n->next;
//	b->next = k ;
//	n=wset->head;
//	return n->freq;
//	}
	k=n->next;
	b->next = k;
	wset->head = n;
//	n=wset->head;	
	return n->freq ;

        }
b=n;
n = n->next;
}


WordNode*h= node_new(word);

b->next = h;  //point head node to new node ................................................... 
h->freq++ ;
wset->size++;
h->word = word ;
return h->freq;
}


/**
 * The wset_remove function is used to remove the given word
 * from a WordSet object. It returns the frequency of the word it
 * removed or -1 if the word was not found.
 */
int wset_remove(WordSet* wset, char* word) {
  // TODO: This function must remove the word from the set. You should
  // traverse the list until you find the word and then remove it. Do
WordNode* n=NULL;
WordNode* b=NULL;
WordNode* j= NULL;
int i=0 ;
n=wset->head ;

if(n== NULL){

return -1;
}
//if(strcmp(n->word,word)==0){
//i= n->freq;
//node_free(n);
//wset->size--;
//return i;
//}
while(n != NULL){

if(strcmp(n->word, word)==0){
       
if(b == NULL){
i=n->freq;
j = wset->head;

j=n->next;
node_free(n);
wset->size--;
wset->head=j ;
return i ;

}
	i= n->freq;	
	j= n->next;	
	node_free(n);
 	b->next = j;
	       
	wset->size-- ;
        return i ;
  //    }
}

b=n;
n = n->next;
}
  // not forget to free the WordNode object or you will have a memory
  // leak! Make sure you adjust the size of the set after you remove
  // the word. Pay careful attention to edge cases such as an empty
  // set and when the word you are removing is the first element in
  // the linked list of WordNode objects.
  return -1;
}

/**
 * The wset_exists function is used to test the existence of
 * the given word in a WordSet object. It returns 1 if the word exists
 * in the set; 0 otherwise.
 */
int wset_exists(WordSet* wset, char* word) {
  // TODO: iterate through the linked list until you find the word. If
  // you do not find the word then you return 0. 
WordNode* n ;
n= wset->head ;
while(n != NULL){

if(strcmp(word,n->word)==0){
return 1;
}
n=n->next ;
}

return 0;

}

/**
 * The wset_freq function returns the frequency of the given word
 * in the WordSet object. If the word does not exist it returns 0.
 */
int wset_freq(WordSet* wset, char* word) {
  // TODO: iterate through the linked list until you find the word -
  // return its frequency. If you do not find the word then return 0.
WordNode* n ;
n= wset->head;

while(n != NULL){

if(strcmp(word,n->word)==0){
return n->freq;

}
n=n->next ;
}

return 0 ;
}

/**
 * The wset_print function prints the words and frequencies in
 * the WordSet object.
 */
void wset_print(WordSet* wset) {
  int longest = 0;
  for (WordNode* p = wset->head; p != NULL; p = p->next) {
    int len = strlen(p->word);
    if (longest < len)
      longest = len;
  }
  for (WordNode* p = wset->head; p != NULL; p = p->next) {
    printf("%-.*s : %d\n", longest, p->word, p->freq);
  }
}
