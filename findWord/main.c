#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function that finds the location of the searched word
void findWord(FILE *file, const char *searchWord) {

    char line[256];
    int lineNumber = 0;

    while ((fgets(line, sizeof(line), file) != NULL)) {

        lineNumber++;

        // Find the location if the word appears in the file
        char *pos = strstr(line, searchWord);
        if (pos != NULL) {
            // Calculate the word location
            long position = pos - line;

            // Go to the beginning of the file and calculate the total number of characters up to the line
            fseek(file, 0, SEEK_SET);
            long totalChars = 0;
            for (int i=0; i < lineNumber-1; i++) {
                fgets(line, sizeof(line), file);
                totalChars += strlen(line);
            }

            // Write the position
            printf("The word '%s' was found in the %ld. character on the %d. line of the file.\n", searchWord, totalChars + position, lineNumber);

            return;
        }
    }

}

int main() {
    
    FILE *file = fopen("text.txt", "r");

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