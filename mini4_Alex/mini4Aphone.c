#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct PHONE_RECORD {
        char name[50];
        char birthdate[12];
        char phone[15];
     } phonebook[10];

int getSize(void){                                                                                                                                             
    int len=0;
    for(int i = 0 ; phonebook[i].name[0] != '\0'&& i<10 ; i++){
        len++;
    }        
    return len; 
}     

int addRecord(char name[50], char birth[12], char phone[15]){ // takes 3 strings as input representing the name, birthdate,
                                                              // and phone number of the contact. Adds a contact to the 
    int index = getSize();
    strcpy(phonebook[index].name, name);
    strcpy(phonebook[index].birthdate, birth);
    strcpy(phonebook[index].phone, phone);
    return 0;
}

int listRecords(void){ // prints the whole phone book 
    printf("Format: name, birthdate, phone; \n");
    for(int i = 0; i<getSize() ;i++){
        printf("contact # %d: \n", i+1 );
        printf("%s,%s,%s\n", phonebook[i].name, phonebook[i].birthdate, phonebook[i].phone);
    }return 0;
}

int findRecord(char name[50]){
    if(getSize()<1) return -1;
    for(int i = 0 ; i < 10; i++){
        if (strcmp(phonebook[i].name, name) == 0){
            return i; // return the index of the record
        }
    }return 11; //error code if the name wasnt found
}

int saveCSV(void){
    FILE *pFile = fopen("phonebook.csv", "w");
    

    if(pFile == NULL){ // error while opening file
        fclose(pFile);   
        return 1;
    }

    fprintf(pFile,"Name,birthdate,phone \n");

    for(int i = 0; i<getSize(); i++){ // iterate through each contact in the struct array, print to phonebook.csv in the correct format.
        fprintf(pFile,
                "%s,%s,%s\n", 
                phonebook[i].name,
                phonebook[i].birthdate,
                phonebook[i].phone);
    }
    if (ferror(pFile)){ // error while writing to file
        fclose(pFile);   
        return 1;
    }
    fclose(pFile);   
    
    return 0; 
}

int loadCSV(void){ // opens and reads the csv file, stores the info in the struct PHONE_RECORD. 
    FILE *pFile = fopen("phonebook.csv", "r"); 
    char buffer[255];
    

    // Initialize phonebook th correct way
    for(int i = 0 ; i<10 ; i ++){
        phonebook[i].name[0] = phonebook[i].birthdate[0] = phonebook[i].birthdate[0] = '\0';
    }

    if(pFile == NULL){ // Implies there was an error while loading the file
        return 1; 
    }
    for(int i = 0 ; fgets(buffer, 255, pFile) != NULL && i < 11 ; i++){
        if(i == 0) {
            continue;
        }else {
            char *token;
            token = strtok(buffer, ",");
            // strcpy(phonebook[i-1].name, token);
            token[strcspn(token, "\n")] = 0;
            strcpy(phonebook[i-1].name, token);

            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = 0;
            strcpy(phonebook[i-1].birthdate, token);

            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = 0;
            strcpy(phonebook[i-1].phone, token);

        }buffer[0] = '\0';
    }
    fclose(pFile);
    return 0;
}

