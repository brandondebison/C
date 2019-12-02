#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Programmer - Brandon Debison
// Progject 2007 - Movie Store

// need to fix the sort function to notes. 
// need to add previous to the structs 

#define MAX 10

int count = 0;
int fileStarted = 0;
char filename[] = "movies.txt";
//struct movie *m_movies, *current, *move, *begin, *last, *new2;
struct movie *move, *last, *new2;


struct movie 
{
    char movieName[35];
    char director[35];
    char releaseDate[15]; // day - month- year no spacing 
    int rating; // 1-5
    double costPerRental;
    int numberOfViews;    
    int rentedToId;
    int rentalReturnDate;
    struct movie *next;

};

// Function Section
        struct movie addNewMovie(struct movie *first);
    // 2. function to browse entries 
        void printToScreen(struct movie *first);
        void search(struct movie* first);
        void modifymovie(struct movie *match);
        // this needs to be updated to free the memory 
        void deletemovie(struct movie *previous, struct movie *move);
        void calculate(struct movie *first);
        struct movie *sortmovies(struct movie *first);
        struct movie *readFile(struct movie *first);
    // Function to print to screen
        void print_struct(struct movie *print_file);
    // Function to malloc
        struct movie *make_structure(void);
        void write_toFile(struct movie *first);
        void savefunction(struct movie *first);
        int counterOfMovies(struct movie *first);

        struct movie *swapA(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right);
        struct movie *swapB(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right);
        struct movie *swapC(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right);
        struct movie *swapD(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right);



int main () {

    int leave = 1;
    int ch;
    int sectionSelector =0;
    int selectData = 0;

    struct movie *m_movies, *first;
    first = make_structure();
    m_movies = make_structure();

    first = m_movies;

    if (m_movies == NULL)
    {
        puts("Malloc error ");
        exit(1);
    }
    
    puts("Would you like to Load Previously Stored Data or Start with New Data?\n");
    puts("1. Load Previously Stored Data\n");
    puts("2. Start New Data\n");

    scanf("%d", &selectData);
    while ((ch=getchar()) != '\n' && ch != EOF);  

    switch (selectData)
            {
                case 1: readFile(first);break; // Call function 
                case 2: puts("Start New Data");break;//call function
                default: return 0;
            }           

    while(leave == 1){

        // display the choices 
        puts("Please select one of the following choices by entering the section number.\n");
        
        puts("1. Add New Movie");
        puts("2. Browse Movie Library");
        puts("3. Search");               
        puts("4. Calculate and Display Current Month Earnings");
        puts("5. Sort Movies");
        puts("6. EXIT SYSTEM\n");

        puts("Please select the choices by entering the section number.\n");

        
        
        scanf("%d", &sectionSelector);
        while ((ch=getchar()) != '\n' && ch != EOF);            

        
        switch (sectionSelector)
        {
            case 1: addNewMovie(first); break;
            case 2: printToScreen(first) ;break;
            case 3: search(first);break;
            case 4: calculate(first);break;
            case 5: first = sortmovies(first); /*savefunction(first);*/ break; 
            case 6: puts("Thank you for using Movie Tracker 2.0"); exit(1);break;
            case 7: printf("%s = first  %s = second  %s \n", m_movies->movieName, first->next->movieName, first->movieName);break;
            case 8: for (int x = 0; x < 6; x++) {
                            printf("getting to end %d ,%s \n", x, first->movieName);
                            first = first->next;
                    }; break;
            default: return 0;
        }       
    }
    return 0;
}

// 1. function to add new entries

    struct movie addNewMovie(struct movie *first) 
    {
        struct movie *start, *current; 
        start = first;
        char keep = 'y';
        int ch;
        
        while(keep == 'y')
        {
            if (fileStarted == 0)
            {                
                if (start == NULL)
                {
                    puts("Memory Allocation Error");
                    exit(1);
                }
                
                fileStarted ++;
                
                puts("\nPlease enter the movie name");
                scanf("%s", start->movieName);
                while ((ch=getchar()) != '\n' && ch != EOF);  

                puts("\nPlease enter the Director"); 
                scanf("%s", start->director);
                while ((ch=getchar()) != '\n' && ch != EOF);    

                puts("\nPlease enter the Release Date, no spaces");
                scanf("%s", start->releaseDate);
                while ((ch=getchar()) != '\n' && ch != EOF); 

                puts("\nPlease enter the rating");
                scanf("%d", &start->rating);
                while ((ch=getchar()) != '\n' && ch != EOF); 

                puts("\nPlease enter the cost per rental");
                scanf("%lf", &start->costPerRental);
                while ((ch=getchar()) != '\n' && ch != EOF); 

                puts("\nPlease enter the number of views");
                scanf("%d", &start->numberOfViews);
                while ((ch=getchar()) != '\n' && ch != EOF);

                puts("\nPlease enter the renters ID");
                scanf("%d", &start->rentedToId);
                while ((ch=getchar()) != '\n' && ch != EOF);

                puts("\nPlease enter the number of days until returned");
                scanf("%d", &start->rentalReturnDate);
                while ((ch=getchar()) != '\n' && ch != EOF);

                start->next = NULL;
                last = start;
                
                write_toFile(start);          

            }
            else
            {
                current = make_structure();
                if (current == NULL)
                {
                    puts("Memory Allocation Error");
                    exit(1);
                }
                last->next = current;
                count ++;
                

                puts("\nPlease enter the movie name");
                scanf("%s", current->movieName);
                while ((ch=getchar()) != '\n' && ch != EOF);  

                puts("\nPlease enter the Director"); 
                scanf("%s", current->director);
                while ((ch=getchar()) != '\n' && ch != EOF);    

                puts("\nPlease enter the Release Date");
                scanf("%s", current->releaseDate);
                while ((ch=getchar()) != '\n' && ch != EOF); 

                puts("\nPlease enter the rating");
                scanf("%d", &current->rating);
                while ((ch=getchar()) != '\n' && ch != EOF); 

                puts("\nPlease enter the cost per rental");
                scanf("%lf", &current->costPerRental);
                while ((ch=getchar()) != '\n' && ch != EOF); 

                puts("\nPlease enter the number of views");
                scanf("%d", &current->numberOfViews);
                while ((ch=getchar()) != '\n' && ch != EOF);

                puts("\nPlease enter the renters ID");
                scanf("%d", &current->rentedToId);
                while ((ch=getchar()) != '\n' && ch != EOF);

                puts("\nPlease enter the number of days until returned");
                scanf("%d", &current->rentalReturnDate);
                while ((ch=getchar()) != '\n' && ch != EOF);

                write_toFile(current);

                current->next = NULL;
                last = current;
            }

            puts("Enter new data?");
            scanf("%c", &keep);
            while ((ch=getchar()) != '\n' && ch != EOF); 
        }

        return *first;
    }

// 2. function to browse entries     

    void printToScreen(struct movie *first)
    {
        struct movie *move;
        move = first;
        puts("\n");

        while(move->next!=NULL) 
        {
            printf("Movie Name = %s     Director Name= %s       Release Date = %s       Rating = %d     Cost = %.2lf    Number of Views = %d    Rented To Id = %d     Days Until Returned = %d \n", 
            move->movieName, move->director, move->releaseDate, move->rating, move->costPerRental, move->numberOfViews, move->rentedToId, move->rentalReturnDate);
            move = move->next;
        }
            printf("Movie Name = %s     Director Name= %s       Release Date = %s       Rating = %d     Cost = %.2lf    Number of Views = %d    Rented To Id = %d     Days Until Returned = %d \n", 
            move->movieName, move->director, move->releaseDate, move->rating, move->costPerRental, move->numberOfViews, move->rentedToId, move->rentalReturnDate);

        puts("End");
        puts("\n");   

    }


// 3. Search

void search(struct movie* first)
{

    struct movie *move;
    struct movie *previous;
    move = first;
    char teststatement[35];
    struct movie *match;
    int searchmatch;
    int ch;
    int matchtest = 0;

        
        puts("\n");

        puts("\nPlease enter the movie name");
        scanf("%s", teststatement);
        while ((ch=getchar()) != '\n' && ch != EOF);
               

        while(move->next!=0) 
        {
            if (strcmp(teststatement, move->movieName)==0)
            {
                puts("We have found a match!");   
                matchtest = 1; 
                match = move; 

                puts("Do you want to modify press 1 or delete it press 2, press 3 to return");
                scanf("%d", &searchmatch);
                while ((ch=getchar()) != '\n' && ch != EOF);            

                
                switch (searchmatch)
                {
                    case 1: modifymovie(match); savefunction(first); break;
                    case 2: deletemovie(previous, move); savefunction(first); readFile(first); break;
                    case 3: return;
                    default: break;
                }   

            } else {
                previous = move;
                move = move->next;                
            }                
                      
            
        }

        if (matchtest == 0)
            {
                puts("There was no match");
                return;
            }        
}


// 3.1 function to modify entries 

void modifymovie(struct movie* match)
{
    //struct movie *move;
    //move = match;
    int ch;
    char tempc[35];
    int tempi;
    double tempd;
    
    puts("\nPlease enter the movie name");
    scanf("%s", match->movieName);
    while ((ch=getchar()) != '\n' && ch != EOF);  

    puts("\nPlease enter the Director"); 
    scanf("%s", match->director);
    while ((ch=getchar()) != '\n' && ch != EOF);    

    puts("\nPlease enter the Release Date");
    scanf("%s", match->releaseDate);
    while ((ch=getchar()) != '\n' && ch != EOF); 

    puts("\nPlease enter the rating");
    scanf("%d", &match->rating);
    while ((ch=getchar()) != '\n' && ch != EOF); 

    puts("\nPlease enter the cost per rental");
    scanf("%lf", &match->costPerRental);
    while ((ch=getchar()) != '\n' && ch != EOF); 

    puts("\nPlease enter the number of views");
    scanf("%d", &match->numberOfViews);
    while ((ch=getchar()) != '\n' && ch != EOF);

    puts("\nPlease enter the renters ID");
    scanf("%d", &match->rentedToId);
    while ((ch=getchar()) != '\n' && ch != EOF);

    puts("\nPlease enter the number of days until returned");
    scanf("%d", &match->rentalReturnDate);
    while ((ch=getchar()) != '\n' && ch != EOF);
   
    
}

// 3.2 function to delete entry 
    
void deletemovie(struct movie *previous,struct movie *move)
{    
    struct movie *next;
    previous->next = move->next;

   
    //need to free() the data 
    
    return;
}
 


// 4. function to calculate the months earnings 

void calculate(struct movie* first)
{

    struct movie *move;
    move = first;
    double price = 0;
    double views = 0;
    double earnings = 0;

    puts("\n");

    while(move->next!=0) 
    {
         price = move->costPerRental;
         views = move->numberOfViews;

        earnings = earnings + (price * views); 
        
        move = move->next;
    }
        printf("Earnings = %.2f \n", earnings);

}

// 5. function to sort and call into the other functions 

int counterOfMovies(struct movie *first) {
        printf("Made it to counter\n");
    
    int counter = 1;
    struct movie *i;
    i = first;

    while (i->next != NULL)
    {
        counter = counter + 1;
        i = i->next;
        
    }

    return counter;
}


    struct movie *sortmovies(struct movie *first)
    {
        printf("Made it to sort\n");
        
    

        struct movie *next, *left, *last_left, *right, *last_right, *end, *start;
        //start = first;
        int counter = counterOfMovies(first);
        printf("Made it past counter\n");
        printf("counter is %d \n", counter);
        printf("first name is %s, second is %s \n", first->movieName, first->next->movieName);
        end = first;
        while (end->next !=NULL){
            end = end->next;
        }
        printf("end name is %s end next is %s\n", end->movieName, end->next->movieName);

        /*for (int x = 0; x < counter; x++) {
            printf("getting to end %d ,%s \n", x, end->movieName);
            end = end->next;

                }*/

        //for (int x = 0; x < counter; x++) {end = first->next;}
        //left = start;
        left = first;
        //last_left = start;
        last_left = first;

        last_right = left;
        right = left;
        printf("left is %s and right is %s", left->movieName, right->movieName);

        //bool swap = false;

       /* while(current->next != NULL)
        {
            counter++;
            current = current->next;
        }*/

        for (int i = 1; i < counter -1; i++){
            for (int j = i+1; j < counter; j++) {

                printf("Made it to buble sort\n");
               /* for (int x = 0; x < counter; x++) {end = first->next;
        printf("getting to end %s\n", first->movieName);
                }*/


                last_right = right;
                right = right->next;
                printf("right is now right-next = %s\n" , right->movieName);
                //if (strcmp(left->movieName, right->movieName) > 0){swap = true;};
/*
                if(swap==true && left==start && right==end) {
                    *start = swapA(start, end, left, right, last_left, last_right);
                } else if (swap==true && left==start && right!=end) {
                    *start = swapB(start, end, left, right, last_left, last_right);
                } else if (swap==true && left!=start && right==end) {
                    *start = swapC(start, end, left, right, last_left, last_right);
                } else if (swap==true && left!=start && right!=end) {
                    *start = swapD(start, end, left, right, last_left, last_right);
                } */

                if((strcmp(left->movieName, right->movieName) != 0) && left==first && right==end) {
                    first = swapA(first, end, left, right, last_left, last_right);
                } else if ((strcmp(left->movieName, right->movieName) != 0) && left==first && right!=end) {
                    first = swapB(first, end, left, right, last_left, last_right);
                } else if ((strcmp(left->movieName, right->movieName) != 0) && left!=first && right==end) {
                    first = swapC(first, end, left, right, last_left, last_right);
                } else if ((strcmp(left->movieName, right->movieName) != 0) && left!=first && right!=end) {
                    first = swapD(first, end, left, right, last_left, last_right);
                }
                
                printf("last left = %s, left = %s, and right = %s \n", last_left->movieName, left->movieName, right->movieName);
                last_left = left;
                left = left->next;
                right = left;   
                printf("last left = %s, left = %s, and right = %s \n", last_left->movieName, left->movieName, right->movieName);

            }
        }



        return first;
    }




struct movie *swapA(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right) 
{
        printf("in Swap A, first is = %s\n", first->movieName);
        struct movie *start;
        //next = next;
        left = left;
        last_left = last_left;
        right = right;
        last_right = last_right; 
        end = end; 
        start = first;

        right->next = left->next; 
        last_right->next = left;
        left->next = NULL;
        start = right;
    

    return first;
}

struct movie *swapB(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right) {
    //struct movie *start, *next, *left, *last_left, *right, *last_right, *end;
        struct movie *temp, *start;
        printf("in Swap B, first is = %s\n",first->movieName);

       /* next = next;
        left = left;
        last_left = last_left;
        right = right;
        last_right = last_right; 
        end = end; 
        start = first; */

        temp = right->next;
        right->next = left->next;
        left->next = temp;
        last_right->next = left;
        start = right;

        printf("%s first \n", start->movieName);

    return start;
}
struct movie *swapC(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right) {
    //struct movie *start, *next, *left, *last_left, *right, *last_right, *end;
        //next = next;
        struct movie *start;
        printf("in Swap C\n first is = %s \n",first->movieName);
/*
        left = left;
        last_left = last_left;
        right = right;
        last_right = last_right; 
        end = end; 
        start = first;*/

        last_left->next = right;
        right->next = last_right;
        last_right->next = left;
        left->next = NULL;


    return start;
}
struct movie *swapD(struct movie *first,struct movie *end,struct movie *left,struct movie *right,struct movie *last_left,struct movie *last_right) {
        //struct movie *start, *next, *left, *last_left, *right, *last_right, *end;
        struct movie *temp;
        struct movie *start;
        printf("in Swap D\n");
        printf("first is %s, first next is %s\n", first->movieName, first->next->movieName);
    start = first;
                /*next = next;
                //left = left;
                last_left = last_left;
                right = right;
                last_right = last_right; 
                end = end; 
                start = first;*/

                last_left->next = right;
                temp = right->next;
                right->next = left->next;
                last_right->next = left;
                left->next = temp;
        printf("bottom of Swap D\n");
        printf("start = %s, first = %s\n", start->movieName, first->movieName);

    return start;
}

// Read File function 
        struct movie *readFile(struct movie *first)
    {        
        
        FILE *fp;
        struct movie *current;
        current = first;
        //first = make_structure();
        int firstLine = 0;
        fileStarted = 1;

        if ( (fp = fopen(filename, "r")) == NULL)
        {
            puts("Error Opening File");
            exit(1);
        }
        
        count = 0;
        int success = 1;
        while(!feof(fp))
        {
            current->next = make_structure();
            current = current->next;
            success = fscanf(fp,"%s%s%s%d%lf%d%d%d", 
                current->movieName,current->director, current->releaseDate, 
                &current->rating, &current->costPerRental, 
                &current->numberOfViews, &current->rentedToId, &current->rentalReturnDate);                
            if (firstLine == 0) {first = current; firstLine++;};
            if(success == -1){break;}
            
            print_struct(current);      
            count++;
        }
        last = current;
        fclose(fp);

    return first;
    }
        
    
    
// Function to print screen
void print_struct(struct movie* print_file)
{       

    printf("\n"); 
    printf("%s\n", print_file->movieName );
    printf("%s\n", print_file->director );
    printf("%s\n", print_file->releaseDate );
    printf("%d\n", print_file->rating);
    printf("%1.2f\n", print_file->costPerRental);
    printf("%d\n", print_file->numberOfViews);
    printf("%d\n", print_file->rentedToId);
    printf("%d\n", print_file->rentalReturnDate);
    printf("\n");
}
        

// function to malloc
struct movie *make_structure(void)
{
    struct movie *a;

    a=(struct movie *)malloc(sizeof(struct movie));
    if(a==NULL)
    {
        puts("Mallox Error");
        exit(1);
    }
    return(a);
}

// Fucntion to write to file
void write_toFile(struct movie *first)
{       
    struct movie *current;
    current = first;
    char empty[]= "";
    
    FILE *fp;
               
        if ( (fp = fopen(filename, "a")) == NULL)
        {
            puts("Error Opening File");
            exit(1);
        }

    feof(fp);
    
    fprintf(fp, "%s ", current->movieName );
    fprintf(fp, "%s ", current->director );
    fprintf(fp, "%s ", current->releaseDate );
    fprintf(fp, "%d ", current->rating);
    fprintf(fp, "%1.2f ", current->costPerRental);
    fprintf(fp, "%d ", current->numberOfViews);
    fprintf(fp, "%d ", current->rentedToId);
    fprintf(fp, "%d ", current->rentalReturnDate);
    fprintf(fp, "\n");

    fclose(fp);
    return ;
}

// Function to overwrite file
void savefunction(struct movie *first)
    {
        struct movie *move;
        move = first;
        //char empty[]= {" "};

        FILE *fp;
        fp = fopen("movies.txt", "w");
        puts("made if to save");
       
            while(move->next!=NULL) 
            {
                
                    fprintf(fp, "%s ", move->movieName );
                    fprintf(fp, "%s ", move->director );
                    fprintf(fp, "%s ", move->releaseDate );
                    fprintf(fp, "%d ", move->rating);
                    fprintf(fp, "%1.2f ", move->costPerRental);
                    fprintf(fp, "%d ", move->numberOfViews);
                    fprintf(fp, "%d ", move->rentedToId);
                    fprintf(fp, "%d ", move->rentalReturnDate);
                    fprintf(fp, "\n");

                move = move->next;
            }
                

                fprintf(fp, "%s ", move->movieName );
                fprintf(fp, "%s ", move->director );
                fprintf(fp, "%s ", move->releaseDate );
                fprintf(fp, "%d ", move->rating);
                fprintf(fp, "%1.2f ", move->costPerRental);
                fprintf(fp, "%d ", move->numberOfViews);
                fprintf(fp, "%d ", move->rentedToId);
                fprintf(fp, "%d ", move->rentalReturnDate);
                fprintf(fp, "\n");
                          

        fclose(fp);
        return;    

    }