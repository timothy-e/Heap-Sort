/////////////////////////////////////////////////////////////////////////////
// INTEGRITY INSTRUCTIONS

// Explicitly state the level of collaboration on this question
// Examples:
//   * I discussed ideas with classmate(s) [include name(s)]
//   * I worked together with classmate(s) in the lab [include name(s)]
//   * Classmate [include name] helped me debug my code
//   * I consulted website [include url]
//   * None
// A "None" indicates you completed this question entirely by yourself
// (or with assistance from course staff)
/////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT:
// I received help from the following sources:

// None

// Name: Timothy Elgersma
// login ID: trelgers
/////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "minheap.h"

struct minheap *minheap_create(void) {
  struct minheap *h = malloc(sizeof(struct minheap));
  h->len = 0;
  h->maxlen = 1;
  h->data = malloc(sizeof(int));
  return h;
}


bool minheap_is_empty(const struct minheap *h) {
  return h->len == 0;
}

// minheap_grow(h) mutates h so that the array is twice as long, and updates
//   the maxlen parameter to match. 
// effects: mutates h and h->data
// time: O(n), n is h->len
void minheap_grow(struct minheap *h) {
  if (h->len == 0) {
    h->maxlen = 1;
    h->data = realloc(h->data, sizeof(int));
    return;
  }
  int len = h->len;
  h->maxlen = len * 2;
  int *newdata = malloc(sizeof(int) * h->maxlen);
  for(int i = 0; i < len; i++) {
    newdata[i] = h->data[i];
  }
  int *backup = h->data;
  h->data = newdata;
  free(backup);
}

// swap(a[], pos1, pos2) mutates a[] so that the values stored at a[pos1] and
//   a[pos2] are swapped
// effects: mutates a[]
// time: O(1)
void swap(int a[], int pos1, int pos2) {
  int backup = a[pos1];
  a[pos1] = a[pos2];
  a[pos2] = backup;
}


void minheap_insert(int i, struct minheap *h) {
  if (h->len >= h->maxlen) minheap_grow(h);
  h->data[h->len] = i;
  h->len++;
  int pos = h->len - 1;
  int parent_pos = (pos - 1) / 2;
  while(pos > 0 && h->data[pos] < h->data[parent_pos]) {
    swap(h->data, pos, parent_pos);
    pos = parent_pos;
    parent_pos = (pos - 1) / 2;
  }
}


int minheap_top(const struct minheap *h) {
  return h->data[0];
}


int minheap_remove(struct minheap *h) {
  int ret = minheap_top(h);
  h->data[0] = h->data[h->len - 1]; //out of place node copied to root
  h->len--; //"removes" the last node from the tree
  int pos = 0;
  int left_child = 1;
  int right_child = 2;
  int len = h->len;
  while(left_child < len && 
        (h->data[pos] > h->data[left_child] || h->data[pos] > right_child)) {
    if (h->data[left_child] <= h->data[right_child]) {
      swap(h->data, pos, left_child);
      pos = left_child;
    } else {
      swap(h->data, pos, right_child);
      pos = right_child;
    }
    left_child = 2 * pos + 1;
    right_child = 2 * pos + 2;
  }
  return ret;
}


void minheap_destroy(struct minheap *h) {
  free(h->data);
  free(h);
}


void heapsort(int a[], int len) {
  struct minheap *h = minheap_create();
  for(int i = 0; i < len; i++) {
    minheap_insert(a[i], h);
  }
  for(int i = 0; i < len; i++) {
    a[i] = minheap_remove(h);
  }
  minheap_destroy(h);
}
