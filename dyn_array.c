#include <stdio.h>
#include <stdlib.h>

int *no_of_books;
int **no_of_pages;

int query_ask(FILE *fptr){
    int query_continue;
    printf("\n-------------------------------------------------------------------\n");
    printf("1)Add a book\n2)Exit\n");
    scanf("%d",&query_continue);
    fprintf(fptr,"%d ",query_continue);
    return query_continue;
}

void main(){
    FILE *fread,*fwrite;
    fread=fopen("library_records.txt","r");
    fwrite=fopen("library_records.txt","a+");
    if (fread == NULL || fwrite == NULL) {
        printf("The file is not opened. The program will exit now");
        exit;
    }
    int no_of_shelves;
    printf("\nEnter the number of shelves: ");
    scanf("%d",&no_of_shelves);

    no_of_books=(int*)malloc(no_of_shelves*sizeof(int));
    no_of_pages=(int**)malloc(no_of_shelves*sizeof(int*));

    for(int i=0;i<no_of_shelves;i++){
        no_of_books[i]=0;
        no_of_pages[i]=(int*)malloc((no_of_books[i]+1)*sizeof(int));
    }

    fprintf(fwrite,"%d ",no_of_shelves);
    while(query_ask(fwrite)==1){
        int x,y;
        printf("\nEnter which shelf you want to add the book to: ");
        scanf("%d",&x);
        while(x>no_of_shelves){
            printf("Invalid shelf size, Please enter a number from 1 to %d.",no_of_shelves);
            scanf("%d",&x);
        }
        x--;
        printf("Enter the pages of the book: ");
        scanf("%d",&y);
        *(*(no_of_pages+x)+*(no_of_books+x))=y;
        (*(no_of_books+x))++;
        *(no_of_pages+x)=realloc(*(no_of_pages+x),(*(no_of_books+x)+1)*sizeof(int));
        x++;
        fprintf(fwrite,"%d %d ",x,y);
    }
    fclose(fread);
    fclose(fwrite);

    if(no_of_books)
        free(no_of_books);
    for(int i=0;i<no_of_shelves;i++){
        if(no_of_pages[i])
            free(no_of_pages[i]);
    }
    if(no_of_pages)
        free(no_of_pages);
}