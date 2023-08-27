#include "patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"


const int MAX_NAME_LEN = 30;

struct patient {
    int id;
    char* name;
};

struct patient *patient_read(void) {
    struct patient* p = malloc(sizeof(struct patient));
    p->id = 0;
    p->name = malloc(sizeof(char) * (MAX_NAME_LEN + 1));
    int retval1 = scanf("%d", &p->id);
    int retval2 = scanf("%s", p->name);
    if (retval1 == 1 && retval2 == 1) {
        return p;
    } else {
        return NULL;
    }
}

struct patient *patient_clone(const struct patient *p) {
    assert(p);
    struct patient* new_p = malloc(sizeof(struct patient));
    new_p->name = malloc(sizeof(char) * (MAX_NAME_LEN + 1));
    new_p->id = p->id;
    strcpy(new_p->name, p->name);
    return new_p;
}

void patient_destroy(struct patient *p) {
    assert(p);
    free(p->name);
    free(p);
}

void patient_print(const struct patient *p) {
    assert(p);
    printf("(%d) %s\n", p->id, p->name);
}