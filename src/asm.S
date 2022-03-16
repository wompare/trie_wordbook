#include "asmdef.h"

.extern stringToLcase
.extern nodeCreate
.extern exit

.section .data

.section .text
DECLARE_GLOBAL(asm_function)


################################################################################
# name:         asm_function
# action:	Indexing a trie data structure.
# in:		node_t *node, char *key
#
# out:		none.
# modifies:	node_t *node
# notes:	Does not modify isleaf.
################################################################################
FUNC(asm_function):
indexer:
    # Initialize stack and get arguments.
    pushl %ebp				# stack: retval
    movl %esp, %ebp			# ebp = stack

    subl $8, %esp			# esp: 8 ... retval
    subl $4, %esp			# esp: 12 ... retval

    movl 8(%ebp), %eax			# eax = node
    movl 12(%ebp), %esi			# ebx = key

    # Calls on extern function stringToLcase with key
    # to make all charactrers lower case.
    pushl %eax				# stack: node retval
    pushl %esi				# stack: key node retval
    call stringToLcase
    popl %esi				# stack: node retval
    popl %eax				# stack: retval

    movl $0, %ecx			# i = 0

    # Loops while not at end of word.
loop:
    movzbl (%esi, %ecx), %edx		# edx = key[i]
    pushl %ecx				# stack: i retval

    movl %edx, %edi			# edi = key[i]
    subl $97, %edx			# index = key[i] - a
    cmp $0, %edx			# if index < 0
    jl isleaf				#	goto isleaf

    movl (%eax), %ecx			# ecx = node->arr
    movl (%ecx, %edx, 4), %eax		# eax = node->arr[index]

    cmp $0, %eax			# if node->arr[index] != NULL
    jne L1				# 	goto L1

    # Calls on nodeCreate with key[i] 
    # to create a new node.
    pushl %edx				# stack: index i retval
    pushl %ecx				# stack: node->arr index i retval
    pushl %esi				# stack: key node->arr index i retval
    pushl %edi				# stack: key[i] key node->arr index i retval

    call nodeCreate			# newnode = nodeCreate(key[i])
    cmp $0, %eax			# if newnode = NULL
    je error				# 	goto error

    popl %edi				# stack: key node->arr index i retval
    popl %esi				# stack: node->arr index i retval
    popl %ecx				# stack: index i retval
    popl %edx				# stack: i retval
    movl %eax, (%ecx, %edx, 4)		# node->arr[index] = newnode

    # Moves to node->arr on index and 
L1:
    movl (%ecx, %edx, 4), %eax		# eax = node->arr[index]
    popl %ecx				# stack: retval
    addl $1, %ecx			# i++

    cmp $0, %edi			# if key[i] != \0
    jne loop				# 	goto loop
isleaf:
    movb $1, 4(%eax)			# node->isleaf = 1

    # Finnishing up and returning
end:
    movl $1, %eax			# eax = 1
    movl %ebp, %esp			# esp = ebp
    popl %ebp				# stack:
    ret					# return eax

error:
    pushl $1				# stack: 1
    call exit				# exit(1)

