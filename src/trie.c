/*
 * NOTE:
 * See the corresponding header file for comments on non-local functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

// Length of English alphabet
#define LOF_EN_ABET 26




/* UTILITY FUNCTIONS */

void stringToLcase(char *word) {
  int i = 0;
  while (word[i]!='\0') {
    word[i] = (char)tolower(word[i]);
    i++;
  }
}

void stripString(char *word) {
    //if (word[strlen(word) - 1] == '\n') {
    //    word[strlen(word) - 1] = '\0';
    //}
    word[strcspn(word, "\n")] = 0;
}

void printTrie(node_t *root) {
    // Prints the nodes of the trie
    if (!root)
        return;
    node_t *temp = root;

    printf("%c %d -> ", temp->ltrValue, temp->isleaf);

    for (int i = 0; i < LOF_EN_ABET; i++) {
        printTrie(temp->arr[i]);
    }
}

bool checkNonalpha(char *term) {
    for (int i = 0; i < strlen(term); ++i) {
        if (isalpha(term[i]) == 0) {
            return false;
        }
    }
    return true;
}


/* LOCAL FUNCTIONS */

/* Deallocates a single node, including the char* array in it. The function is
 * oblivious to its surroundings, so if it has children, they need to be
 * taken care of.
 * TAKES:
 * node - A pointer to a tree node to deallocate.
 */
static void nodeDestroy(node_t *node) {
    free(node->arr);
    free(node);
}

static bool trieSearch(node_t *root, const char *key) {
    node_t *tmp = root;
    int index, i = 0;

    // Checks for word in trie same way as indexed.
    while (key[i]!='\0') {
        index = key[i] - 'a';

        if (tmp->arr[index]!=NULL) {
            tmp = tmp->arr[index];
        }
        else {
            return false;
        }
        i++;
    }

    return tmp->isleaf;
}


/* TRIE TREE OPERATIONS */

node_t *nodeCreate(char ltr)
{
    // NULL returns are handled by the caller
    node_t *newnode = (node_t *)malloc(sizeof(node_t));

    newnode->arr = (node_t **)malloc(sizeof(node_t *) * LOF_EN_ABET);
    if (newnode->arr == NULL) {
        return NULL;
    }

    for(int i = 0; i < LOF_EN_ABET; ++i) {
        newnode->arr[i] = NULL;
    }
    newnode->ltrValue = ltr;
    newnode->isleaf = false;

    return newnode;
}


void userSearch(node_t *root) {
    int maxlenghtQuery = 50;
    bool exists = false;
    char query[maxlenghtQuery];

    while (1) {
        // Just to make some space
        fputc('\n', stdout);
        // Get the user's query and strip newline
        printf("Enter a query (00 to quit): ");
        stripString(fgets(query, maxlenghtQuery, stdin));
        // Test if query exists in wordlist
        exists = trieSearch(root, query);

        if (strcmp(query, "00")==0) {
            return;
        }
        else {
            printf("%s %s in the wordlist\n",
                   query,
                   exists ? "does exist" : "does not exist");
        }
    }
}


void treeDestroy(node_t *root) {
    for(int i = 0; i < LOF_EN_ABET; i++) {
        if(root->arr[i] != NULL) {
            treeDestroy(root->arr[i]);
        }
    }

    nodeDestroy(root);
}
