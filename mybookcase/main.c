#include <stdio.h>

typedef struct {
	char Readers[50];
	char Publishers[50];
	char Categories[50];
	char Books[50];
	char Authors[50];
} DataFile;

DataFile df = {"reader_data.csv", "publisher_data.csv", "category_data.csv", "book_data.csv", "author_data.csv"};

typedef struct {
	unsigned int ID;
	char Name[50];
	char Email[50];
	char Password[50];
} Reader;

void reader_operations();

typedef struct {
	unsigned int ID;
	char PublisherName[50];
} Publisher;

void publisher_operations();

typedef struct {
	unsigned int ID;
	char CategoryName[50];
} Category;

void category_operations();

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

void book_operations();

typedef struct {
	unsigned int ID;
	char Name[50];
} Author;

void author_operations();

int main()
{
	int choice;
	
	do {
		printf("Please select the part you want to process: \n");
		printf(" 1-Author\n 2-Book\n 3-Category\n 4-Publisher\n 5-Reader\n 6-Exit\n");
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



