#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
  int flag;
  struct Trie *children[26];
} Trie;

void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

void insert(struct Trie **ppTrie, char *word) {
  if (*ppTrie == NULL) {
    return;
  }

  Trie *temp = *ppTrie;
  int length = strlen(word);

  for (int i = 0; i < length; i++) {
    int index = word[i] - 'a';
    if (temp->children[index] == NULL) {
      temp->children[index] = calloc(1, sizeof(Trie));
    }
    temp = temp->children[index];
  }
  temp->flag++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
  Trie *temp = pTrie;
  int length = strlen(word);

  for (int i = 0; i < length; i++) {
    int index = word[i] - 'a';
    if (temp->children[index] == NULL) {
      return 0;
    }
    temp = temp->children[index];
  }
  return temp->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
  if (pTrie == NULL) {
    return NULL;
  }
  for (int i = 0; i < 26; i++) {
    deallocateTrie(pTrie->children[i]);
  }
  free(pTrie);
  return NULL;
}

int main(void) {
  Trie *trie = (Trie *)calloc(1, sizeof(Trie));
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  int nWords = sizeof(pWords) / sizeof(pWords[0]);

  for (int i = 0; i < 5; i++) {
    insert(&trie, pWords[i]);
  }
  for (int i = 0; i < 5; i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
  }
  trie = deallocateTrie(trie);
  if (trie != NULL)
    printf("There is an error in this program\n");
  return 0;
}