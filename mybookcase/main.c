#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char Readers[50];
	char Publishers[50];
	char Categories[50];
	char Books[50];
	char Authors[50];
} DataFile;

DataFile df = {"reader_data.txt", "publisher_data.txt", "category_data.txt", "book_data.txt", "author_data.txt"};

typedef struct {
	unsigned int ID;
	char Name[50];
	char Email[50];
	char Password[50];
} Reader;

void reader_operations();
void viewReaders(FILE *file);
void addReader(FILE *file, Reader *newReader);
void updateReader(FILE *file, int targetId, Reader *updatedReader);
void deleteReader(FILE *file, int targetId);
void saveReader(FILE *file, Reader *reader, int numReader);


typedef struct {
	unsigned int ID;
	char PublisherName[50];
} Publisher;

/*
void publisher_operations();
void viewPublishers(FILE *file);
void addPublisher(FILE *file, Publisher *newPublisher);
void updatePublisher(FILE *file, int targetId, Publisher *updatedPublisher);
void deletePublisher(FILE *file, int targetId);
void savePublisher(FILE *file, Publisher *publisher, int numPublisher);
*/

typedef struct {
	unsigned int ID;
	char CategoryName[50];
} Category;

/*
void category_operations();
void viewCategories(FILE *file);
void addCategory(FILE *file, Category *newCategory);
void updateCategory(FILE *file, int targetId, Category *updatedCategory);
void deleteCategory(FILE *file, int targetId);
void saveCategory(FILE *file, Category *category, int numCategory);
*/
typedef struct {
	unsigned int ID;
	char Name[50];
	char Description[100];
	char PublishedDate[50];
	unsigned int Edition;
	unsigned int TotalPages;
	char Languages[50];
	char ISBN[100];
} Book;

/*
void book_operations();
void viewBooks(FILE *file);
void addBook(FILE *file, Book *newBook);
void updateBook(FILE *file, int targetId, Book *updatedBook);
void deleteBook(FILE *file, int targetId);
void saveBook(FILE *file, Book *book, int numBook);
*/

typedef struct {
	unsigned int ID;
	char Name[50];
} Author;

/*
void author_operations();
void viewAuthors(FILE *file);
void addAuthor(FILE *file, Author *newAuthor);
void updateAuthor(FILE *file, int targetId, Author *updatedAuthor);
void deleteAuthor(FILE *file, int targetId);
void saveAuthor(FILE *file, Author *author, int numAuthor);
*/

int main()
{
	int choice;
	
	do {
		printf("Please select the part you want to process: \n");
		printf(" 1-Author\n 2-Book\n 3-Category\n 4-Publisher\n 5-Reader\n 6-Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice); 
		
		switch (choice) {
			case 1:
				printf("Author Process ..... \n");
				// author_operations();
				break;
			case 2:
				printf("Book Process ..... \n");
				// book_operations();
				break;
			case 3:
				printf("Category Process ..... \n");
				// category_operations();
				break;
			case 4:
				printf("Publisher Process ..... \n");
				// publisher_operations();
				break;
			case 5:
				printf("Reader Process ..... \n");
				reader_operations();
				break;
			case 6:
				printf("Exit Process ..... \n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");
		}
		
	} while(1);
	
	return 0;
}

/* ---- READER OPERATIONS ---- */

// Function to choice reader operations
void reader_operations() {
	FILE *file;
    file = fopen(df.Readers, "r+"); // Open file in append and read mode

    if(file == NULL) {
    	file = fopen(df.Readers, "w+");
	}

    printf("File reading is successful.\n");
    int choice;
    Reader newReader;
    Reader updatedReader;
    int targetId;
    
    do {
    	printf("\n1. View Readers\n2. Add Reader\n3. Update Reader\n4. Delete Reader\n5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
        	case 1:
        		viewReaders(file);
        		break;
        	case 2:
        		printf("Enter ID: ");
        		scanf("%d", &newReader.ID);
        		printf("Enter Name: ");
        		scanf("%s", &newReader.Name);
        		printf("Enter Email: ");
        		scanf("%s", &newReader.Email);
        		printf("Enter Password: ");
        		scanf("%s", &newReader.Password);
        		addReader(file, &newReader);
        		break;
			case 3:
				printf("Enter ID to update: ");
                scanf("%d", &targetId);
                printf("Enter updated Name: ");
        		scanf("%s", &updatedReader.Name);
        		printf("Enter updated Email: ");
        		scanf("%s", &updatedReader.Email);
        		printf("Enter updated Password: ");
        		scanf("%s", &updatedReader.Password);
        		updateReader(file, targetId, &updatedReader);
				break;
			case 4:
				printf("Enter ID to delete: ");
                scanf("%d", &targetId);
                deleteReader(file, targetId);
                break;
            case 5: 
            	fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
		}	
	} while(1);
}

// Function to view readers from file
void viewReaders(FILE *file) {
	
	rewind(file); // Move file pointer to the beginning
	
	Reader reader;
    printf("\nID\tName\tEmail\tPassword\n");
	while (fread(&reader, sizeof(Reader), 1, file)) {
        printf("%d\t%s\t%s\t%s\n", reader.ID, reader.Name, reader.Email, reader.Password);
    }
}

// Function to add a new reader to the file
void addReader(FILE *file, Reader *newReader) {
	
	fseek(file, 0, SEEK_END); // Move file pointer to the end
	fwrite(newReader, sizeof(Reader), 1, file);
    printf("Data added successfully.\n");
	
}

// Function to update a reader in the file
void updateReader(FILE *file, int targetId, Reader *updatedReader) {
	
	rewind(file); // Move file pointer to the beginning

    Reader reader;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records
    
    int found = 0;
    
    while (fread(&reader, sizeof(Reader), 1, file)) {
        if (reader.ID == targetId) {
			strcpy(reader.Name, updatedReader->Name);
			strcpy(reader.Email, updatedReader->Email);
			strcpy(reader.Password, updatedReader->Password);
        	fwrite(&reader, sizeof(Reader), 1, tempFile);
            printf("Data updated successfully.\n");
            found = 1;
        } else {
            fwrite(&reader, sizeof(Reader), 1, tempFile);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    remove("reader_data.txt");
    rename("temp.txt", "reader_data.txt");

    if (!found) {
        printf("Reader not found.\n");
    }
    
}


// Function to delete Reader from file
void deleteReader(FILE *file, int targetId) {
	
	rewind(file); // Move file pointer to the beginning

    Reader reader;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records

    int found = 0;

    while (fread(&reader, sizeof(Reader), 1, file)) {
        if (reader.ID == targetId) {
            printf("Data deleted successfully.\n");
            found = 1;
        } else {
            fwrite(&reader, sizeof(Reader), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("reader_data.txt");
    rename("temp.txt", "reader_data.txt");

    if (!found) {
        printf("Reader not found.\n");
    }
	
}


