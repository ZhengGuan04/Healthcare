#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

struct pqueue {
    int len;
    int cap;
    struct patient** arr;
};

struct pqueue *pqueue_create() {
    struct pqueue* pq = malloc(sizeof(struct pqueue));
    pq->len = 0;
    pq->cap = 1;
    pq->arr = malloc(sizeof(struct patient*));
    return pq;
}

void pqueue_destroy(struct pqueue *pq) {
    assert(pq);
    for (int i = 0; i < pq->len; i++) { 
        patient_destroy(pq->arr[i]);
    }
    free(pq->arr);
    free(pq);
}

void pqueue_enqueue(struct pqueue *pq, struct patient *p) {
    assert(pq);
    assert(p);
    if (pq->len == pq->cap) {
        pq->cap *= 2;
        pq->arr = realloc(pq->arr, sizeof(struct patient*) * pq->cap);
    }
    pq->arr[pq->len] = p;
    pq->len += 1;
}

struct patient *pqueue_dequeue(struct pqueue *pq) {
    assert(pq);
    struct patient* p = patient_clone(pq->arr[0]);
    patient_destroy(pq->arr[0]);
    for (int i = 0; i < pq->len - 1; i++) {
        pq->arr[i] = patient_clone(pq->arr[i + 1]);
        patient_destroy(pq->arr[i + 1]);
    }
    pq->len -= 1;
    return p;
}

struct patient *pqueue_front(const struct pqueue *pq) {
    assert(pq);
    struct patient* cp = patient_clone(pq->arr[0]);
    return cp;
}

bool pqueue_empty(const struct pqueue *pq) {
    assert(pq);
    return pq->len == 0;
}

void pqueue_print(const struct pqueue *pq) {
    assert(pq);
    if (!pqueue_empty(pq)) {
        printf("Patient queue");
        for (int i = 0; i < pq->len; i++) {
            printf(" -> ");
            patient_print(pq->arr[i]);
        }
        printf("\n");
    }
}