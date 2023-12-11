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

void publisher_operations();
void viewPublishers(FILE *file);
void addPublisher(FILE *file, Publisher *newPublisher);
void updatePublisher(FILE *file, int targetId, Publisher *updatedPublisher);
void deletePublisher(FILE *file, int targetId);
void savePublisher(FILE *file, Publisher *publisher, int numPublisher);

typedef struct {
	unsigned int ID;
	char CategoryName[50];
} Category;


void category_operations();
void viewCategories(FILE *file);
void addCategory(FILE *file, Category *newCategory);
void updateCategory(FILE *file, int targetId, Category *updatedCategory);
void deleteCategory(FILE *file, int targetId);
void saveCategory(FILE *file, Category *category, int numCategory);

typedef struct {
	unsigned int ID;
	char Name[50];
	char Description[100];
	char PublishedDate[50];
	unsigned int Edition;
	unsigned int TotalPages;
	char Language[50];
	char ISBN[100];
} Book;


void book_operations();
void viewBooks(FILE *file);
void addBook(FILE *file, Book *newBook);
void updateBook(FILE *file, int targetId, Book *updatedBook);
void deleteBook(FILE *file, int targetId);
void saveBook(FILE *file, Book *book, int numBook);


typedef struct {
	unsigned int ID;
	char Name[50];
} Author;


void author_operations();
void viewAuthors(FILE *file);
void addAuthor(FILE *file, Author *newAuthor);
void updateAuthor(FILE *file, int targetId, Author *updatedAuthor);
void deleteAuthor(FILE *file, int targetId);
void saveAuthor(FILE *file, Author *author, int numAuthor);


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
				author_operations();
				break;
			case 2:
				printf("Book Process ..... \n");
				book_operations();
				break;
			case 3:
				printf("Category Process ..... \n");
				category_operations();
				break;
			case 4:
				printf("Publisher Process ..... \n");
				publisher_operations();
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
    file = fopen(df.Readers, "r+"); // Open file in read mode

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

    remove(df.Readers);
    rename("temp.txt", df.Readers);

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

    remove(df.Readers);
    rename("temp.txt", df.Readers);

    if (!found) {
        printf("Reader not found.\n");
    }
	
}

void saveReader(FILE *file, Reader *reader, int numReader) {

}

/* ---- PUBLISHER OPERATIONS ---- */

// Function to choice publisher operations
void publisher_operations() {
	FILE *file;
    file = fopen(df.Publishers, "r+"); // Open file in read mode

    if(file == NULL) {
    	file = fopen(df.Publishers, "w+");
	}

    printf("File reading is successful.\n");
    int choice;
    Publisher newPublisher;
    Publisher updatedPublisher;
    int targetId;
    
    do {
    	printf("\n1. View Publishers\n2. Add Publisher\n3. Update Publisher\n4. Delete Publisher\n5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
        	case 1:
        		viewPublishers(file);
        		break;
        	case 2:
        		printf("Enter ID: ");
        		scanf("%d", &newPublisher.ID);
        		printf("Enter Publisher Name: ");
        		scanf("%s", &newPublisher.PublisherName);
        		addPublisher(file, &newPublisher);
        		break;
			case 3:
				printf("Enter ID to update: ");
                scanf("%d", &targetId);
                printf("Enter updated Publisher Name: ");
        		scanf("%s", &updatedPublisher.PublisherName);
        		updatePublisher(file, targetId, &updatedPublisher);
				break;
			case 4:
				printf("Enter ID to delete: ");
                scanf("%d", &targetId);
                deletePublisher(file, targetId);
                break;
            case 5: 
            	fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
		}	
	} while(1);

}

// Function to view publishers from file
void viewPublishers(FILE *file) {

	rewind(file); // Move file pointer to the beginning
	
	Publisher publisher;
    printf("\nID\tPublisher_Name\n");
	while (fread(&publisher, sizeof(Publisher), 1, file)) {
        printf("%d\t%s\n", publisher.ID, publisher.PublisherName);
    }
}

// Function to add a new publisher to the file
void addPublisher(FILE *file, Publisher *newPublisher) {
	
	fseek(file, 0, SEEK_END); // Move file pointer to the end
	fwrite(newPublisher, sizeof(Publisher), 1, file);
    printf("Data added successfully.\n");
}

// Function to update a publisher in the file
void updatePublisher(FILE *file, int targetId, Publisher *updatedPublisher) {

	rewind(file); // Move file pointer to the beginning

    Publisher publisher;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records
    
    int found = 0;
    
    while (fread(&publisher, sizeof(Publisher), 1, file)) {
        if (publisher.ID == targetId) {
			strcpy(publisher.PublisherName, updatedPublisher->PublisherName);
        	fwrite(&publisher, sizeof(Publisher), 1, tempFile);
            printf("Data updated successfully.\n");
            found = 1;
        } else {
            fwrite(&publisher, sizeof(Publisher), 1, tempFile);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    remove(df.Publishers);
    rename("temp.txt", df.Publishers);

    if (!found) {
        printf("Publisher not found.\n");
    }

}

// Function to delete Publisher from file
void deletePublisher(FILE *file, int targetId) {

	rewind(file); // Move file pointer to the beginning

    Publisher publisher;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records

    int found = 0;

    while (fread(&publisher, sizeof(Publisher), 1, file)) {
        if (publisher.ID == targetId) {
            printf("Data deleted successfully.\n");
            found = 1;
        } else {
            fwrite(&publisher, sizeof(Publisher), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(df.Publishers);
    rename("temp.txt", df.Publishers);

    if (!found) {
        printf("Publisher not found.\n");
    }

}

void savePublisher(FILE *file, Publisher *publisher, int numPublisher) {

}

/* ---- CATEGORY OPERATIONS ---- */

// Function to choice category operations
void category_operations() {

	FILE *file;
    file = fopen(df.Categories, "r+"); // Open file in read mode

    if(file == NULL) {
    	file = fopen(df.Categories, "w+");
	}

    printf("File reading is successful.\n");
    int choice;
    Category newCategory;
    Category updatedCategory;
    int targetId;
    
    do {
    	printf("\n1. View Categories\n2. Add Category\n3. Update Category\n4. Delete Category\n5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
        	case 1:
        		viewCategories(file);
        		break;
        	case 2:
        		printf("Enter ID: ");
        		scanf("%d", &newCategory.ID);
        		printf("Enter Category Name: ");
        		scanf("%s", &newCategory.CategoryName);
        		addCategory(file, &newCategory);
        		break;
			case 3:
				printf("Enter ID to update: ");
                scanf("%d", &targetId);
                printf("Enter updated Category Name: ");
        		scanf("%s", &updatedCategory.CategoryName);
        		updateCategory(file, targetId, &updatedCategory);
				break;
			case 4:
				printf("Enter ID to delete: ");
                scanf("%d", &targetId);
                deleteCategory(file, targetId);
                break;
            case 5: 
            	fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
		}	
	} while(1);

}

// Function to view categories from file
void viewCategories(FILE *file) {

	rewind(file); // Move file pointer to the beginning
	
	Category category;
    printf("\nID\tCategory_Name\n");
	while (fread(&category, sizeof(Category), 1, file)) {
        printf("%d\t%s\n", category.ID, category.CategoryName);
    }

}

// Function to add a new category to the file
void addCategory(FILE *file, Category *newCategory) {

	fseek(file, 0, SEEK_END); // Move file pointer to the end
	fwrite(newCategory, sizeof(Category), 1, file);
    printf("Data added successfully.\n");
}

// Function to update a category in the file
void updateCategory(FILE *file, int targetId, Category *updatedCategory) {

	rewind(file); // Move file pointer to the beginning

    Category category;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records
    
    int found = 0;
    
    while (fread(&category, sizeof(Category), 1, file)) {
        if (category.ID == targetId) {
			strcpy(category.CategoryName, updatedCategory->CategoryName);
        	fwrite(&category, sizeof(Category), 1, tempFile);
            printf("Data updated successfully.\n");
            found = 1;
        } else {
            fwrite(&category, sizeof(Category), 1, tempFile);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    remove(df.Categories);
    rename("temp.txt", df.Categories);

    if (!found) {
        printf("Category not found.\n");
    }

}

// Function to delete category from file
void deleteCategory(FILE *file, int targetId) {

	rewind(file); // Move file pointer to the beginning

    Category category;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records

    int found = 0;

    while (fread(&category, sizeof(Category), 1, file)) {
        if (category.ID == targetId) {
            printf("Data deleted successfully.\n");
            found = 1;
        } else {
            fwrite(&category, sizeof(Category), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(df.Categories);
    rename("temp.txt", df.Categories);

    if (!found) {
        printf("Category not found.\n");
    }
}

void saveCategory(FILE *file, Category *category, int numCategory) {

}

/* ---- BOOK OPERATIONS ---- */

// Function to choice book operations
void book_operations() {

    FILE *file;
    file = fopen(df.Books, "r+"); // Open file in read mode

    if(file == NULL) {
    	file = fopen(df.Books, "w+");
	}

    printf("File reading is successful.\n");
    int choice;
    Book newBook;
    Book updatedBook;
    int targetId;
    
    do {
    	printf("\n1. View Books\n2. Add Book\n3. Update Book\n4. Delete Book\n5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
        	case 1:
        		viewBooks(file);
        		break;
        	case 2:
        		printf("Enter ID: ");
        		scanf("%d", &newBook.ID);
        		printf("Enter Book Name: ");
        		scanf("%s", &newBook.Name);
                printf("Enter Description about Book: ");
                scanf("%s", &newBook.Description);
                printf("Enter Published Date: ");
                scanf("%s", &newBook.PublishedDate);
                printf("Enter Book Edition: ");
                scanf("%d", &newBook.Edition);
                printf("Enter Book's Total Pages: ");
                scanf("%d", &newBook.TotalPages);
                printf("Enter Book Language: ");
                scanf("%s", &newBook.Language);
                printf("Enter Book ISBN: ");
                scanf("%s", &newBook.ISBN);
        		addBook(file, &newBook);
        		break;
			case 3:
				printf("Enter ID to update: ");
                scanf("%d", &targetId);
                printf("Enter Updated Book Name: ");
        		scanf("%s", &updatedBook.Name);
                printf("Enter Updated Description about Book: ");
                scanf("%s", &updatedBook.Description);
                printf("Enter Updated Published Date: ");
                scanf("%s", &updatedBook.PublishedDate);
                printf("Enter Updated Book Edition: ");
                scanf("%d", &updatedBook.Edition);
                printf("Enter Updated Book's Total Pages: ");
                scanf("%d", &updatedBook.TotalPages);
                printf("Enter Updated Book Language: ");
                scanf("%s", &updatedBook.Language);
                printf("Enter Updated Book ISBN: ");
                scanf("%s", &updatedBook.ISBN);
        		updateBook(file, targetId, &updatedBook);
				break;
			case 4:
				printf("Enter ID to delete: ");
                scanf("%d", &targetId);
                deleteBook(file, targetId);
                break;
            case 5: 
            	fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
		}	
	} while(1);
}

// Function to view books from file
void viewBooks(FILE *file) {

    rewind(file); // Move file pointer to the beginning
	
	Book book;
    printf("\nID\tName\tDescription\tPublished_Date\tEdition\tTotal_Pages\tLanguage\tISBN\n");
	while (fread(&book, sizeof(Book), 1, file)) {
        printf("\n%d\t%s\t%s\t%s\t%d\t%d\t%s\t%s\n", book.ID, book.Name, book.Description, book.PublishedDate, book.Edition, book.TotalPages, book.Language, book.ISBN);
    }
}

// Function to add a new book to the file
void addBook(FILE *file, Book *newBook) {

    fseek(file, 0, SEEK_END); // Move file pointer to the end
	fwrite(newBook, sizeof(Book), 1, file);
    printf("Data added successfully.\n");
}

// Function to update a book in the file
void updateBook(FILE *file, int targetId, Book *updatedBook) {

    rewind(file); // Move file pointer to the beginning

    Book book;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records
    
    int found = 0;
    
    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.ID == targetId) {
			strcpy(book.Name, updatedBook->Name);
            strcpy(book.Description, updatedBook->Description);
            strcpy(book.PublishedDate, updatedBook->PublishedDate);
            strcpy(book.Edition, updatedBook->Edition);
            strcpy(book.TotalPages, updatedBook->TotalPages);
            strcpy(book.Language, updatedBook->Language);
            strcpy(book.ISBN, updatedBook->ISBN);
        	fwrite(&book, sizeof(Book), 1, tempFile);
            printf("Data updated successfully.\n");
            found = 1;
        } else {
            fwrite(&book, sizeof(Book), 1, tempFile);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    remove(df.Books);
    rename("temp.txt", df.Books);

    if (!found) {
        printf("Book not found.\n");
    }
}

// Function to delete book from file
void deleteBook(FILE *file, int targetId) {

    rewind(file); // Move file pointer to the beginning

    Book book;
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file to store non-deleted records

    int found = 0;

    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.ID == targetId) {
            printf("Data deleted successfully.\n");
            found = 1;
        } else {
            fwrite(&book, sizeof(Book), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(df.Books);
    rename("temp.txt", df.Books);

    if (!found) {
        printf("Book not found.\n");
    }

}

void saveBook(FILE *file, Book *book, int numBook) {

}

