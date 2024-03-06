#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <stdbool.h>

//Array to store the number of books in each shelf
int *no_of_books;

typedef enum{false,true}bool;

//Structure to store the details of the book
typedef struct{
    char book_name[50];
    int book_page;
    float book_price;
}book;

/*
    A 2D array that stores the address of each book structure
    1st dereference -> Address of structure
    2nd dereference -> Value of structure
*/
book** book_info;

char* string_lower(char* text_string){
    for(int i=0;text_string[i];i++){
        text_string[i]=tolower(text_string[i]);
    }
    return text_string;
}

//Function for checking password
int passowrd_check()
{
    char input_password[50],password[50]="Prasiddha";
    printf("\nThis query requires a password.\n");
    printf("\nPlease enter the password: ");
    scanf("%s",input_password);
    return strcmp(input_password,password);
}

//A function to ask for the required query
int query_ask()
{
    int query_continue;
    printf("\n-------------------------------------------------------------------\n");
    printf("0)Find a book\n1)Add a book\n2)Display all the books information\n3)Check for the information of books on nth shelf\n"
            "4)Check for information on the required book\n5)Delete a book\n6)Change the number of shelves\n"
            "7)Exit\n");
    printf("-------------------------------------------------------------------\n");\
    scanf("%d", &query_continue);
    return query_continue;
}

//A function to ask for the shelf number
int ask_shelf_no()
{
    int shelf_number;
    printf("\nEnter the shelf number: ");
    scanf("%d",&shelf_number);
    return shelf_number;
}

//A function to ask for the book number
int ask_book_no()
{
    int book_number;
    printf("Enter the book number: ");
    scanf("%d",&book_number);
    return book_number;
}

void main()
{
    float price_number;
    int no_of_shelves,shelf_number,i,j,book_number, page_number;
    char name_of_book[50],tmp_book_name[50],tmp_search_name[50];
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

    for (i = 0; i < no_of_shelves; i++)
    {
        no_of_books[i] = 0;
        //book_info[i] stores each structure so we allocate the size of structure book
        book_info[i] = (book *)malloc((no_of_books[i] + 1) * sizeof(book));
    }

    while(fscanf(fread,"%d",&shelf_number)!=EOF){
        //printf("Enter the book number: ");
        fscanf(fread, " %d", &book_number);
        //printf("Enter the name of the book: ");
        fscanf(fread, " %[^\n]*s", name_of_book);
        //printf("Enter the pages of the book: ");
        fscanf(fread,"%d", &page_number);
        //printf("Enter the price of the book: ");
        fscanf(fread,"%f", &price_number);
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
    }
    int query_terminate = query_ask(),count=0;
    //This while loop will automatically exit after 100 queries to avoid any infinite looping
    while (query_terminate != 7 && count <100)
    {
        //Query to add a new book to the end of the nth shelf
        if (query_terminate == 1)
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
            while(page_number<=0){
                printf("Please enter a valid number of pages: ");
                scanf("%d",&page_number);
            }
            printf("Enter the price of the book: ");
            scanf("%f", &price_number);
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
        }
        //Simple query to print the information of all the books in all shelves
        else if (query_terminate == 2)
        {
            for(i=0;i<no_of_shelves;i++){
                for(j=0;j<no_of_books[i];j++){
                    if(book_info[i][j].book_page!=0){
                        printf("\n-------------------------------------------------------------------\n");
                        printf("|\tShelf Number = %d\n|\tBook Number = %d\n|\tBook name = %s\n|\tNumber of pages = %d\n|\tPrice = %0.2f\n"\
                            ,i+1,j+1, book_info[i][j].book_name, \
                        book_info[i][j].book_page, book_info[i][j].book_price);
                        printf("-------------------------------------------------------------------\n");
                    }
                }
            }
        }
        //Query to find if the entered book is available, if yes: print its information
        else if (query_terminate == 0)
        {
            bool book_found = false;
            printf("\nEnter the book name: ");
            scanf(" %[^\n]*s",tmp_book_name);

            for(i=0;i<no_of_shelves;i++){
                for(j=0;j<no_of_books[i];j++){
                    strcpy(tmp_search_name,book_info[i][j].book_name);
                    string_lower(tmp_search_name);
                    string_lower(tmp_book_name);
                    if(book_info[i][j].book_page!=0 && strcmp(tmp_search_name,tmp_book_name)==0){
                        printf("\n-------------------------------------------------------------------\n");
                        printf("|\tShelf Number = %d\n|\tBook Number = %d\n|\tBook name = %s\n|\tNumber of pages = %d\n|\tPrice = %0.2f\n"\
                            ,i+1,j+1, book_info[i][j].book_name, \
                        book_info[i][j].book_page, book_info[i][j].book_price);
                        printf("-------------------------------------------------------------------\n");
                        book_found=true;
                    }
                }
            }
            if(!book_found){
                printf("\nThe required book was not found.");
            }
        }
        //Simple query to print the information of books in the nth shelf
        else if (query_terminate == 3)
        {
            shelf_number=ask_shelf_no();
            shelf_number--;
            while (shelf_number+1> no_of_shelves)
            {
                printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                shelf_number=ask_shelf_no();
                shelf_number--;
            }
            if(no_of_books[shelf_number]==0){
                printf("\nBook not found, There are %d books in this shelf\n",no_of_books[shelf_number]);
            }
            else{
                for(i=0;i<no_of_books[shelf_number];i++){
                    printf("\n-------------------------------------------------------------------\n");
                    printf("|\tBook number = %d\n|\tBook name = %s\n|\tNumber of pages = %d\n|\tPrice = %0.2f\n",i+1 \
                    ,book_info[shelf_number][i].book_name, book_info[shelf_number][i].book_page, book_info[shelf_number][i].book_price);
                    printf("-------------------------------------------------------------------\n");
                }
            }
        }
        //Query to print the information of the nth book of the mth shelf
        else if (query_terminate == 4)
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
                printf("\nBook not found, There are %d books in this shelf\n",no_of_books[shelf_number]-1);
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
                printf("|\tBook name = %s\n|\tNumber of pages = %d\n|\tPrice = %0.2f\n", book_info[shelf_number][book_number].book_name, \
                    book_info[shelf_number][book_number].book_page, book_info[shelf_number][book_number].book_price);
                printf("-------------------------------------------------------------------\n");
            }
        }
        //Query to delete the nth book of the mth shelf
        else if (query_terminate == 5)
        {
            shelf_number=ask_shelf_no();
            shelf_number--;
            while (shelf_number+1> no_of_shelves)
            {
                printf("Invalid shelf size, Please enter a number from 1 to %d.", no_of_shelves);
                shelf_number=ask_shelf_no();
                shelf_number--;
            }
            printf("\nEnter the book name to be deleted: ");
            scanf(" %[^\n]*s",tmp_book_name);
            
            for(i=0;i<no_of_books[shelf_number];i++){
                strcpy(tmp_search_name,book_info[shelf_number][i].book_name);
                string_lower(tmp_search_name);
                string_lower(tmp_book_name);
                if(strcmp(tmp_book_name,tmp_search_name)==0){
                    printf("\nBook named %s deleted successfully.\n",book_info[shelf_number][i].book_name);
                    //memove() function moves the address of the all the succeding books the to nth book thus deleting the nth book
                    memmove(&(book_info[shelf_number][i]),&(book_info[shelf_number][i+1]),(no_of_books[shelf_number]-i)*sizeof(book));
                    no_of_books[shelf_number]--; 
                }
            }
        }
        //Query to change the number of shelves, It only allows increasing of shelves as not to delete any books by removing some shelves
        else if(query_terminate == 6)
        {
            if(passowrd_check()==0){
                int no_of_new_shelves;
                printf("\nEnter new number of shelves: ");
                scanf("%d",&no_of_new_shelves);
                while(no_of_new_shelves<=no_of_shelves){
                    printf("\nNew shelf size greater than old shelf size, Please enter a number greater than %d:\n",no_of_shelves);
                    scanf("%d",&no_of_new_shelves);
                }
                //no_of_books stores integer values so we allocate size_of_array*size_of_int
                no_of_books = (int *)realloc(no_of_books,no_of_new_shelves * sizeof(int));
                //book_info stores address/pointer values so we allocate size_of_array*size_of_int*
                book_info = (book **)realloc(book_info,no_of_new_shelves * sizeof(int *));

                for (i = no_of_shelves; i < no_of_new_shelves; i++)
                {
                    no_of_books[i] = 0;
                    //book_info[i] stores each structure so we allocate the size of structure book
                    book_info[i] = (book *)realloc(book_info[i],(no_of_books[i] + 1) * sizeof(book));
                }
                no_of_shelves=no_of_new_shelves;
                printf("\n\nThe number of shelves is %d.\n\n", no_of_shelves);
            }
        }

        /* A sample for addition of another query
       if (query_terminate == 0)
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
        count++;
        query_terminate = query_ask();
    }

    fprintf(fwrite,"%d\n",no_of_shelves);
    for(i=0;i<no_of_shelves;i++){
        for(j=0;j<no_of_books[i];++j){
            fprintf(fwrite, "%d %d %s\n%d %0.2f\n", i ,j, book_info[i][j].book_name, book_info[i][j].book_page, book_info[i][j].book_price);
        }
    }
    /*library_records_backup.txt is used as a new file to store the previous and new data 
        which is then renamed to library_records.txt*/
    rename("library_records_backup.txt", "library_records.txt");
    fclose(fread);
    fclose(fwrite);

    if (no_of_books)
        free(no_of_books);
    for (i = 0; i < no_of_shelves; i++)
    {
        if (book_info[i])
            free(book_info[i]);
    }
    if (book_info)
        free(book_info);
    if(count==100){
        printf("\nPlease enter a number from 1-7\n");
    }
}