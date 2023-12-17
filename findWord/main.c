#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findWord(FILE *file, const char *searchWord) {

}

int main() {
    
    FILE *file = fopen("text.txt", "r+");

    if (file == NULL) {
        perror("File opening error");
        return 1;
    }

    char word[50];

    printf("Please enter the word to search: ");

    scanf("%s", word);

    findWord(file, word);

    fclose(file);

}