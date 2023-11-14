#include <stdio.h>

typedef struct {
	unsigned int ID;
	char PublisherName[50];
} Publisher;

typedef struct {
	unsigned int ID;
	char CategoryName[50];
} Category;

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

typedef struct {
	unsigned int ID;
	char Name[50];
} Author;

int main()
{
	while (1)
	{
		int process;
		
		printf("Please select the part you want to process: \n");
		printf(" 1-Author\n 2-Book\n 3-Category\n 4-Publisher\n 5-Reader\n 6-Exit\n");
		scanf("%d", &process); 
		
		if (process == 6) 
		{
			break;
		}
		
		else 
		{
			if (process == 1)
			{
				printf("Author Process ..... \n");
			}
			else if (process == 2)
			{
				printf("Book Process ..... \n");
			}
			else if (process == 3)
			{
				printf("Category Process ..... \n");
			}
			else if (process == 4)
			{
				printf("Publisher Process ..... \n");
			}
			else if (process == 5)
			{
				printf("Reader Process ..... \n");
			}
			else 
			{
				printf("Wrong Choice !!! \n");
			}
		}
	}
}
