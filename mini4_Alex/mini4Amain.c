#include <stdio.h> // #include for each library 
#include "mini4Aphone.c"
#include <string.h>
#include <stdlib.h>

int menu(void){      
    char option[2];  
    
    while(1) // loop until the if-statement evaluates to false and a return statement exits the loop.
    {       
    printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit> ");  // display options
    fgets(option, 2, stdin); // get user input
                             
    char c;
    while((c = getc(stdin)) != '\n' && c != EOF);// clear stdin buffer

    if (*option!='1'&&*option!='2' && *option != '3' && option[0] != '4'){// check if input is valid
        printf("Invalid input, try again. \n");
    }
    else{
        return atoi(option);
    }
    }
}

int main(){
 
    int x = loadCSV();
    
    char phone[15];
    char birth[12];
    char name[50];
    char c;  
    int i;
    
    while(1)
    {
    int j = menu();
    switch(j){
        case 1:
            printf("You chose ADD\n");
            if(getSize()>=10){
                printf("Cannot add to phonebook, already full.\n");
                break;
            }            
            printf("Name:");
            
//            while((c = getc(stdin)) != '\n' && c != EOF); // To remove any newline character from the stdin buffer;
            
            fgets(name, 50, stdin); 
            
            printf("Birthdate:");
            fgets(birth, 12, stdin);
            
            printf("Phone Number:");
            fgets(phone, 15, stdin);
            
            name[strcspn(name,"\n")] = 0; // Remove trailing newline character from the strings
            birth[strcspn(birth,"\n")] = 0;
            phone[strcspn(phone,"\n")] = 0;
            
            addRecord(name, birth, phone); 
            
            name[0] = 0; // free up the memory of the strings for the other iterations. 
            phone[0] = 0;
            birth[0] = 0;
            
            break;
        case 2:
            printf("You chose FIND\n");
            if(getSize()<1){
                printf("The file \"phonebook.csv\" is empty. \n");
                break;
            }
            
            printf("Enter the name of a contact you wish to find:");
            
//          while((c = getc(stdin)) != '\n' && c != EOF); // to remove any newline character from the stdin buffer
            
            fgets(name, 50, stdin);
            
            name[strcspn(name,"\n")] = 0;
            
            i = findRecord(name);
            
            if(i == 11){
                printf("This name is not in the phonebook. \n");
            }else{
                printf("%s is at index %d of the phonebook. \n", name, i);
            }
            name[0] = 0; // clear memory
            break;

        case 3:
            printf("You chose LIST\n");
            
            if(getSize()<1){ // means the file doesnt exist
                printf("The file \"phonebook.csv\" is empty.\n");
                break;
            }
            
            listRecords();
            break;
        case 4:
            printf("You chose QUIT\n");
            
            i = saveCSV();
            
            if(i!=0) {
                printf("Error while writing to file \"phonebook.csv\" \n"); 
                exit(1);
            }
            printf("End of the program.\n");  
            exit(0);
        }

    }
}

