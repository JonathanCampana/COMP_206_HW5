#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct PHONE_RECORD {
        char name[50];
        char birthdate[12];
        char phone[15];
     }*phonebook;

struct PHONE_RECORD* makeArray(int size){
    phonebook = (struct PHONE_RECORD*)calloc(size,sizeof(struct PHONE_RECORD));
    return phonebook;
}    

int getSize(int size){                                                                                                                                             
    int len=0;
    
    for(int i = 0 ; phonebook[i].name[0] != '\0'&& i<size ; i++){
        len++;
    }        
    return len; 
}     

int addRecord(char name[50], char birth[12], char phone[15], int size){ 
                                                // takes 3 strings as input representing the name, birthdate,
                                                // and phone number of the contact. Adds a contact to the 
                                                // phoneBook, or returns 1 if it is full. 
    int index = getSize(size);

    strcpy(phonebook[index].name, name);
    strcpy(phonebook[index].birthdate, birth);
    strcpy(phonebook[index].phone, phone);
    return 0;
}

int listRecords(int size){ // prints the whole phone book 
    printf("Format: name, birthdate, phone; \n");
    for(int i = 0; i<getSize(size) ;i++){
        printf("contact # %d: \n", i+1 );
        printf("%s,%s,%s\n", phonebook[i].name, phonebook[i].birthdate, phonebook[i].phone);
    }return 0;
}

int findRecord(char name[50], int size){
    for(int i = 0 ; i < size; i++){
        if (strcmp(phonebook[i].name, name) == 0){
            return i; // return the index of the record
        }
    }return 11; //error code if the name wasnt found
}

int saveCSV(int size){
    FILE *pFile = fopen("phonebook.csv", "w");

    if(pFile == NULL){ // error while opening file
        fclose(pFile);   
        return 1;
    }
    fprintf(pFile,"Name,birthdate,phone \n");

    for(int i = 0; i<getSize(size); i++){ // iterate through each contact in the struct array, print to phonebook.csv in the correct format.
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

int loadCSV(int size){ // opens and reads the csv file, stores the info in the struct PHONE_RECORD. 
    struct PHONE_RECORD *x = makeArray(size);
    if(x == NULL) return 2; // array too big.
    
    FILE *pFile = fopen("phonebook.csv", "r"); 
    char buffer[255];
    
    // Initialize phonebook th correct way
    for(int i = 0 ; i<size ; i ++){
        phonebook[i].name[0] = phonebook[i].birthdate[0] = phonebook[i].birthdate[0] =0;
    }

    if(pFile == NULL){ 
        return 1; 
    }
    
    for(int i = 0 ; fgets(buffer, 255, pFile) != NULL && i <= size ; i++){
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

