#include <stdio.h>
#include <stdbool.h>

extern void initialize();
extern char* highlight(const char* code, bool start);

int main() {
    initialize();
    printf("initialized\n");
}

