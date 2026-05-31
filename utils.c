#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerStringSegura(char *str, int tamanho) {
    if (fgets(str, tamanho, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}
