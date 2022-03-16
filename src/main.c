#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trie.h"
#include "asmdef.h"


// Declaring that assembly function is provided elsewhere
extern void asm_function(node_t *treeroot, char *word);

// This should be the C equivalent to the assembly implementation
void c_function(node_t *treeroot, char *word) 
{
    // Traversing begins at the root.
    node_t *active_node = treeroot;
    // Make sure word is lowercase letters only. Also, the word was read from
    // the dictionary file with 'fgets'. This leaves a '\n' character which
    // needs to be stripped.
    stringToLcase(word);

    /*
     * Operations on active node
     */
    int index; // The index in the active array.
    int i = 0; // The index of the string currently being processed.

    // Traverse and determine if character already exists as child. If so, move
    // to next. If not, create new node. Strip newline characters.
    while (word[i]!='\0') {
        // Find the appropriate index for the active character in the children
        // array of active node.
        index = word[i] - 'a';
        // If node for active character does not exist in active node's children
        // array, create node and assign.
        if (active_node->arr[index]==NULL) {
            active_node->arr[index] = nodeCreate(word[i]);
            // NULL-check
            if (active_node->arr[index]==NULL) {
                exit(1);
            }
        }
        // Move down the tree, to the appropriate child of active node, as the
        // active character is registered in the active node (either it already
        // existed or it has just been added).
        active_node = active_node->arr[index];
        // Move forward in string.
        i++;
    }
    // At end of the loop, end of string is reached. The active node now
    // represents the end of a word and should be marked.
    active_node->isleaf = true;
}

int main(int argc, char **argv) {
    // Check if mandatory file argument is supplied.
    if (argc > 3 || argc < 2) {
        printf("Exactly 1 argument is expected!\n");
        printf("Usage: %s <-language> <path/relative/to program file> / <name "
               "of datafile>\n", argv[0]);
        exit(0);
    }

    // Choose between c or asm function.
    // Defaults to asm function.
    void (*func_ptr)(node_t *wordtreeRoot, char *word);
    if (strcmp(argv[1], "-c") == 0)
    {
        func_ptr = &c_function;
        printf("Using c function.\n");
    } else {
        func_ptr = &asm_function;
        printf("Using asm function.\n");
    }

    // Open wordlist file in read only mode.
    FILE  *fp = fopen(argv[argc-1], "r");
    if(fp == NULL) {
        printf("Could not open \"%s\"\n", argv[argc-1]);
        exit(1);
    }

    /* PREPARE FOR INDEXING */

    // Holds words read from the wordlist file. Apparently the longest word
    // in an English dictionary is 45 characters long:
    // https://en.wikipedia.org/wiki/Longest_word_in_English
    char word[50];


    // The root of the trie tree
    node_t *wordtreeRoot = nodeCreate('\0');
    if (wordtreeRoot == NULL) {
        printf("Could not allocate space for a root node\n");
        exit(1);
    }

    /* PERFORM INDEXING */

    clock_t time = clock();
    // Read from file, line by line, and index until reached eof. Along the
    // way, remove trailing newlines left by 'fgets'. If a word contains a
    // non-alphanumerical character, the word is skipped.
    int wordcount = 0;

    while (fgets(word, sizeof(word), fp)) {
        // Strip newline character left by fgets
        stripString(word);
        // If not contains non-alphanumeric characters, pass word to indexer
        if (checkNonalpha(word)) {
            //c_function(wordtreeRoot, word);
            //asm_function(wordtreeRoot, word);
            func_ptr(wordtreeRoot, word);
            wordcount++;
        }
    }
    time = clock() - time;

    printf("\nTotal indexing time in seconds: %f\n", (double)
    time/CLOCKS_PER_SEC);

    // No need for the wordlist text file anymore
    fclose(fp);

    userSearch(wordtreeRoot);

    treeDestroy(wordtreeRoot);
}
