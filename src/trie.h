#ifndef SRC_TRIE_H
#define SRC_TRIE_H

#include <stdbool.h>

/*
 * arr is 26 characters long since we are using the english alphabet.
 * isleaf is true for end of word.
 */
typedef struct node node_t;
struct node {
    node_t **arr;
    bool isleaf;
    char ltrValue;
};


/* UTILITY FUNCTIONS */

/* Converts any string to lowercase letters only.
 * TAKES:
 * word - A pointer to a string to convert
 */
void stringToLcase(char *word);

/* Aggressively replace the trailing '\n' with '\0'. In this case, we know
 * fgets leaves a trailing '\n', but there is still a need to perform a check
 * for this to make sure the very last word in the wordlist file is not
 * stripped of an actual alphabet character.
 * TAKES:
 * word - A pointer to a string to strip.
 */
void stripString(char *word);

/* Checks a word for non-alphanumeric characters. If such characters in word,
 * return true, else return false.
 * TAKES:
 * word - A pointer to a string to evaluate.
 */
bool checkNonalpha(char *word);


/* TRIE TREE OPERATIONS */

/* Creates a new trie tree node.
 * TAKES:
 * ltr - The char the node representes. Mainly used for testing, left
 * here for reference.
 * RETURNS:
 * newnode - A pointer to a new node on success, NULL if failed. Caller
 * should handle NULL returns.
 */
node_t *nodeCreate(char ltr);


/* Searches for a word in tree.
 * TAKES:
 * root - The root of the tree
 * key - A string pointer to the search word
 *
 * RETURNS:
 * tmp->isleaf - 'true' if word exists in trie, else 'false'
 */
//bool trieSearch(node_t *root, char *key);
void userSearch(node_t *root);


/* Prints all nodes in a trie, as it finds them (i.e. nodes are not organized
 * into words). Used for testing, left here for reference.
 * TAKES:
 * root - A pointer to the root of the trie tree.
 */
void printTrie(node_t *root);


/* Deallocates trie structure recursively from bottom up, left to right.
 * TAKES:
 * root - A pointer to the root of the tree
 */
void treeDestroy(node_t *root);


#endif //SRC_TRIE_H
