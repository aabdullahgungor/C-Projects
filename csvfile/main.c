#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CSV: Comma-Separated Values

int main() {
	char buffer[1000]; // We need a buffer for reading data
	char *data; // We need a pointer for each of tokens
	printf("\n===================================\n");
	FILE *dataFile = fopen("data.csv", "r");
	
	if (dataFile == NULL) // If the file is not find or not open, we send this message below.
	{
		printf("Error: could not open file\n");
		exit(-1);
	}
	printf("I was able to open the file\n");
	
	
	// Reading in the rest of the lines
	while(fgets(buffer, sizeof(buffer), dataFile)) {
		
		printf("%s\n", buffer);
		
		// Parsing	
		data = strtok(buffer, ","); // We get first unit of the buffer.
		
		while (data != NULL) {
			
			printf(" %s\n", data);
			data = strtok(NULL, ",");
			
		}
		
		printf("\n");
		
		
	}
	
		

	
	// Close File
	fclose(dataFile);
	
	
	printf("\n===================================\n");
}

//  Other Methods //

	/* Parsing
			data = strtok(buffer, ","); // We get first unit of the buffer.
			printf("First token is %s\n", data);
			
			// How do we get second unit of the buffer
			data = strtok(NULL, ","); 
			printf("Second token is %s\n", data);
		
			// How do we get third unit of the buffer
			data = strtok(NULL, ","); 
			printf("Third token is %s\n", data);
		
	*/
	
	/*
	
	// Reading in the first line
	fgets(buffer, sizeof(buffer), dataFile);
	printf("%s\n",buffer);
	
	*/
	
	/*
	
	// Reading in the second line
	fgets(buffer, sizeof(buffer), dataFile);
	printf("%s\n",buffer);
	
	*/
	
	
