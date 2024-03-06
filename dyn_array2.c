#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Array to store the number of books in each shelf
int *no_of_books;

//Structure to store the details of the book
typedef struct{
    char book_name[50];
    int book_page;
    int book_price;
}book;

/*
    A 2D array that stores the address of each book structure
    1st dereference -> Address of structure
    2nd dereference -> Value of structure
*/
book** book_info;

//A function to ask for the required query
int query_ask(FILE *fread, FILE *fwrite)
{
    int query_continue;
    //Read until EOF after which the user input is taken
    if (fscanf(fread, "%d", &query_continue) != EOF)
    {
        fprintf(fwrite, "\n%d\n\n", query_continue);
        return query_continue;
    }
    else
    {
        printf("\n-------------------------------------------------------------------\n");
        printf("1)Add a book\n2)Check for the information of books on nth shelf\n"
               "3)Check for information on the required book\n4)Exit\n");
        printf("-------------------------------------------------------------------\n");
        scanf("%d", &query_continue);
        if (query_continue != 1)
        {
            return query_continue;
        }
        fprintf(fwrite, "\n%d\n\n", query_continue);
        return query_continue;
    }
}

//A function to ask for the shelf number
int ask_shelf_no()
{
    int shelf_number;
    printf("\nEnter the shelf number: ");
    scanf("%d",&shelf_number);
    return shelf_number;
}

//A function to ask for the shelf number
int ask_book_no()
{
    int book_number;
    printf("Enter the book number: ");
    scanf("%d",&book_number);
    return book_number;
}

void main()
{
    FILE *fread, *fwrite;
    /*
        library_records.txt file stores all the user input data so that it can be used to
        simulate the input so that data is retained the next time the program is run
    */
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
        printf("\n\nThe number of shelves is %d.\n\n", no_of_shelves);
    }

    //no_of_books stores integer values so we allocate size_of_array*size_of_int
    no_of_books = (int *)malloc(no_of_shelves * sizeof(int));
    //book_info stores address/pointer values so we allocate size_of_array*size_of_int*
    book_info = (book **)malloc(no_of_shelves * sizeof(int *));

    for (int i = 0; i < no_of_shelves; i++)
    {
        no_of_books[i] = 0;
        //book_info[i] stores each structure so we allocate the size of structure book
        book_info[i] = (book *)malloc((no_of_books[i] + 1) * sizeof(book));
    }

    fprintf(fwrite, "%d ", no_of_shelves);
    int query_terminate = query_ask(fread, fwrite);
    //condition for termination is 4
    while (query_terminate != 4)
    {
        int shelf_number, book_number, page_number, price_number;
        char name_of_book[50];
        if (query_terminate == 1)
        {
            if (fscanf(fread, "%d", &shelf_number) != EOF)
            {
                shelf_number--;
                /*
                    The fscanf functions simulate user input by taking all the data from library_records.txt
                    as "user input"
                */
                //printf("Enter shelf number: ");
                fscanf(fread,"%d", &shelf_number);
               // printf("Enter the name of the book: ");
                fscanf(fread," %[^\n]*s",name_of_book);
                //printf("Enter the pages of the book: ");
                fscanf(fread,"%d", &page_number);
                //printf("Enter the price of the book: ");
                fscanf(fread,"%d", &price_number);

                /* These can also be written as:
                    strcpy((book_info[shelf_number][no_of_books[shelf_number]]).book_name,name_of_book);
                    book_info[shelf_number][no_of_books[shelf_number]].book_price = price_number;
                    book_info[shelf_number][no_of_books[shelf_number]].book_price = page_number;
                */
                strcpy((*(*(book_info + shelf_number) + *(no_of_books + shelf_number))).book_name,name_of_book);
                (*(*(book_info + shelf_number) + *(no_of_books + shelf_number))).book_price = price_number;
                (*(book_info + shelf_number) + *(no_of_books + shelf_number))->book_page = page_number;
                (*(no_of_books + shelf_number))++;
                *(book_info + shelf_number) = (book*)realloc(*(book_info + shelf_number), (*(no_of_books + shelf_number) + 1) * sizeof(book));
                shelf_number++;
                /*All the user input data is written into the file so the next time the program simulates
                    the user input to read the data*/
                fprintf(fwrite, "%d\n%s\n%d %d", shelf_number , name_of_book, page_number, price_number);
            }
            else
            {
                shelf_number=ask_shelf_no();
                while (shelf_number > no_of_shelves)
                {
                    printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                    scanf("%d", &shelf_number);
                }
                shelf_number--;
                printf("Enter the name of the book: ");
                scanf(" %[^\n]*s",name_of_book);
                printf("Enter the pages of the book: ");
                scanf("%d", &page_number);
                printf("Enter the price of the book: ");
                scanf("%d", &price_number);
                /* These can also be written as:
                    strcpy((book_info[shelf_number][no_of_books[shelf_number]]).book_name,name_of_book);
                    book_info[shelf_number][no_of_books[shelf_number]].book_price = price_number;
                    book_info[shelf_number][no_of_books[shelf_number]].book_price = page_number;
                */
                strcpy((*(*(book_info + shelf_number) + *(no_of_books + shelf_number))).book_name,name_of_book);
                (*(*(book_info + shelf_number) + *(no_of_books + shelf_number))).book_price = price_number;
                (*(book_info + shelf_number) + *(no_of_books + shelf_number))->book_page = page_number;
                (*(no_of_books + shelf_number))++;
                *(book_info + shelf_number) = realloc(*(book_info + shelf_number), (*(no_of_books + shelf_number) + 1) * sizeof(book));
                /*All the user input data is written into the file so the next time the program simulates
                    the user input to read the data*/
                fprintf(fwrite, "%d\n%s\n%d %d", shelf_number , name_of_book, page_number, price_number);
            }
        }
        //Simple query to print the information of books in the nth shelf
        if (query_terminate == 2)
        {
            shelf_number=ask_shelf_no();
            shelf_number--;
            while (shelf_number+1> no_of_shelves)
            {
                printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                shelf_number=ask_shelf_no();
                shelf_number--;
            }
            if(no_of_books[shelf_number]<=book_number || book_number<0){
                printf("\nBook not found, There are %d books in this shelf\n",no_of_books[shelf_number]);
            }
            else{
                for(int i=0;i<no_of_books[shelf_number];i++){
                    printf("\n-------------------------------------------------------------------\n");
                    printf("|\tBook name = %s\n|\tNumber of pages = %d\n|\tPrice = %d\n", book_info[shelf_number][i].book_name, \
                    book_info[shelf_number][i].book_page, book_info[shelf_number][i].book_price);
                    printf("-------------------------------------------------------------------\n");
                }
            }
        }
        //Query to print the information of the nth book of the mth shelf
        if (query_terminate == 3)
        {
            shelf_number=ask_shelf_no();
            shelf_number--;
            while (shelf_number+1> no_of_shelves)
            {
                printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                shelf_number=ask_shelf_no();
                shelf_number--;
            }
            book_number=ask_book_no();
            book_number--;
            if(no_of_books[shelf_number]<=book_number || book_number<0){
                printf("\nBook not found, There are %d books in this shelf\n",no_of_books[shelf_number]);
            }
            else{
                while(book_number>no_of_books[shelf_number])
                {
                    printf("Shelf %d only contains %d books.\n",shelf_number+1,no_of_books[shelf_number]+1);
                    printf("Please enter a number from 1 to %d.", no_of_books[shelf_number]+1);
                    scanf("%d",&book_number);
                    book_number--;
                }
                printf("\n-------------------------------------------------------------------\n");
                printf("|\tBook name = %s\n|\tNumber of pages = %d\n|\tPrice = %d\n", book_info[shelf_number][book_number].book_name, \
                    book_info[shelf_number][book_number].book_page, book_info[shelf_number][book_number].book_price);
                printf("-------------------------------------------------------------------\n");
            }
        }
        /* A sample for addition of another query
       if (query_terminate == 3)
        {
            shelf_number=ask_shelf_no();
            shelf_number--;
            while (shelf_number+1> no_of_shelves)
            {
                printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                shelf_number=ask_shelf_no();
                shelf_number--;
            }
            book_number=ask_book_no();
            book_number--;
            if(no_of_books[shelf_number]<=book_number || book_number<0){
                printf("\nBook not found, There are %d books in this shelf\n",no_of_books[shelf_number]);
            }
            else{
                while(book_number>no_of_books[shelf_number])
                {
                    
            }
        }*/
        query_terminate = query_ask(fread, fwrite);
    }
    /*library_records_backup.txt is used as a new file to store the previous and new data 
        which is then renamed to library_records.txt*/
    rename("library_records_backup.txt", "library_records.txt");
    fclose(fread);
    fclose(fwrite);

    if (no_of_books)
        free(no_of_books);
    for (int i = 0; i < no_of_shelves; i++)
    {
        if (book_info[i])
            free(book_info[i]);
    }
    if (book_info)
        free(book_info);
}