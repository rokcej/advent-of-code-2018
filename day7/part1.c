#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN ('Z' - 'A' + 1)	

struct _Node;

typedef struct _NodeList {
	struct _Node *node;
	struct _NodeList *next;
} NodeList;

typedef struct _Node {
	char id;
	NodeList *next;
	NodeList *prev;
} Node;

Node *newNode(char id) {
	Node *n = malloc(sizeof(Node));
	n->id = id;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

NodeList *newNodeList(Node *n) {
	NodeList *nl = malloc(sizeof(NodeList));
	nl->node = n;
	nl->next = NULL;
	return nl;
}

void insertNodeList(NodeList **first, Node *n) {
	if (*first == NULL) {
		*first = newNodeList(n);
	} else {
		NodeList *nl = newNodeList(n);
		if (n->id < (*first)->node->id) {
			nl->next = *first;
			*first = nl;
		} else {
			NodeList *iter = *first;
			while (iter->next != NULL && iter->next->node->id < n->id)
				iter = iter->next;

			nl->next = iter->next;
			iter->next = nl;
		}
	}
}

int main() {
	Node *nodes[LEN] = { NULL };

	char idPred, idSucc;
	while (scanf("Step %c must be finished before step %c can begin.\n", &idPred, &idSucc) != EOF) {
		int iPred = idPred - 'A';
		int iSucc = idSucc - 'A';

		if (nodes[iPred] == NULL)
			nodes[iPred] = newNode(idPred);
		if (nodes[iSucc] == NULL)
			nodes[iSucc] = newNode(idSucc);
			
		insertNodeList(&(nodes[iPred]->next), nodes[iSucc]);
		insertNodeList(&(nodes[iSucc]->prev), nodes[iPred]);
	}

	int completed[LEN] = { 0 };
	NodeList *pending = NULL;

	for (int i = 0; i < LEN; i++) {
		if (nodes[i]->prev == NULL) {
			//printf("%c\n", nodes[i]->id);
			insertNodeList(&pending, nodes[i]);
		}
	}

	char result[LEN + 1];
	int len = 0;

	while (pending != NULL) {
		Node *n = pending->node;
		pending = pending->next;

		result[len++] = n->id;
		completed[n->id - 'A'] = 1;

		NodeList *succList = n->next;
		while (succList != NULL) {
			Node *succ = succList->node;
			
			int eligible = 1;
			NodeList *succPredList = succ->prev;
			while (succPredList != NULL) {
				int iSuccPred = succPredList->node->id - 'A';
				if (!completed[iSuccPred]) {
					eligible = 0;
					break;
				}
				succPredList = succPredList->next;
			}
			if (eligible) {
				insertNodeList(&pending, succ);
			}

			succList = succList->next;
		}

	}
	result[len++] = '\0';
	printf("Result: %s\n", result);

	return 0;
}
