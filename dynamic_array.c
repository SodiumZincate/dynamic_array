#include <stdio.h>
#include <stdlib.h>

int *no_of_books;
int **no_of_pages;

int query_ask(FILE *fread, FILE *fwrite)
{
    int query_continue;
    if (fscanf(fread, "%d", &query_continue) != EOF)
    {
        fprintf(fwrite, "%d ", query_continue);
        return query_continue;
    }
    else
    {
        printf("\n-------------------------------------------------------------------\n");
        printf("1)Add a book\n2)Check for number of books on nth shelf\n"
               "3)Check for number of pages of the required book\n4)Exit\n");
        printf("-------------------------------------------------------------------\n");
        scanf("%d", &query_continue);
        if (query_continue == 4)
        {
            return query_continue;
        }
        fprintf(fwrite, "%d ", query_continue);
        return query_continue;
    }
}

void main()
{
    FILE *fread, *fwrite;
    fwrite = fopen("library_records_backup.txt", "a+");
    fread = fopen("library_records.txt", "r");
    if (fread == NULL || fwrite == NULL)
    {
        printf("The file is not opened. The program will exit now");
        exit;
    }
    int no_of_shelves;
    if (fscanf(fread, "%d", &no_of_shelves) == EOF)
    {
        printf("\nEnter the number of shelves: ");
        scanf("%d", &no_of_shelves);
    }
    else
    {
        printf("\nThe number of shelves is %d.\n\n", no_of_shelves);
    }

    no_of_books = (int *)malloc(no_of_shelves * sizeof(int));
    no_of_pages = (int **)malloc(no_of_shelves * sizeof(int *));

    for (int i = 0; i < no_of_shelves; i++)
    {
        no_of_books[i] = 0;
        no_of_pages[i] = (int *)malloc((no_of_books[i] + 1) * sizeof(int));
    }

    fprintf(fwrite, "%d ", no_of_shelves);
    int query_terminate = query_ask(fread, fwrite);
    while (query_terminate != 4)
    {
        int x, y;
        if (query_terminate == 1)
        {
            if (fscanf(fread, "%d", &x) != EOF)
            {
                x--;
                // printf("Enter the pages of the book: ");
                fscanf(fread, "%d", &y);
                *(*(no_of_pages + x) + *(no_of_books + x)) = y;
                (*(no_of_books + x))++;
                *(no_of_pages + x) = realloc(*(no_of_pages + x), (*(no_of_books + x) + 1) * sizeof(int));
                x++;
                fprintf(fwrite, "%d %d ", x, y);
            }
            else
            {
                printf("\nEnter which shelf you want to add the book to: ");
                scanf("%d", &x);
                while (x > no_of_shelves)
                {
                    printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                    scanf("%d", &x);
                }
                x--;
                printf("Enter the pages of the book: ");
                scanf("%d", &y);
                *(*(no_of_pages + x) + *(no_of_books + x)) = y;
                (*(no_of_books + x))++;
                *(no_of_pages + x) = realloc(*(no_of_pages + x), (*(no_of_books + x) + 1) * sizeof(int));
                fprintf(fwrite, "%d %d ", x + 1, y);
            }
        }
        if (query_terminate == 2)
        {
            printf("\nEnter the shelf number: ");
            scanf("%d", &x);
            x--;
            printf("The number of books in shelf %d is %d.\n", x + 1, no_of_books[x]);
        }
        if (query_terminate == 3)
        {
            printf("\nEnter the shelf number: ");
            scanf("%d", &x);
            printf("\nEnter the book number: ");
            scanf("%d", &y);
            x--;
            y--;
            printf("The number of pages in book number %d of shelf %d is %d.\n", y + 1, x + 1, no_of_pages[x][y]);
        }
        query_terminate = query_ask(fread, fwrite);
    }
    rename("library_records_backup.txt", "library_records.txt");
    fclose(fread);
    fclose(fwrite);

    if (no_of_books)
        free(no_of_books);
    for (int i = 0; i < no_of_shelves; i++)
    {
        if (no_of_pages[i])
            free(no_of_pages[i]);
    }
    if (no_of_pages)
        free(no_of_pages);
}
