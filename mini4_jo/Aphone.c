// Jonathan Campana 260985613
// Jonathan.campana@mail.mcgill.ca
// department of science

#include <stdio.h>
#include <string.h>

struct PHONE_RECORD {
	char name[50];
	char birthday[12];
	char phone[15];
} ; 

int loadCSV(struct PHONE_RECORD *phonebook){
	char array[1000];
	FILE *p = fopen("phonebook.csv", "rt");
	if (p == NULL) {
		FILE *q = fopen("phonebook.csv", "wt"); // create file if does not exist
		if (q == NULL) return 1;
		fclose(q);
		return 0;
	}
	
	fgets(array, 999, p); // Read the first line of the csv and increment.

	int k = 0;
	while(k < 10 && fgets(array, 999, p) != NULL) {
			
		int i=0;
		for (; i < 50 && array[i] != ','; i++) {
			phonebook[k].name[i] = array[i];
		}
		phonebook[k].name[i] = '\0';
		i++;

		int j=0;
		for (; j < 12 && array[i] != ','; i++, j++) {
			phonebook[k].birthday[j] = array[i];
		}
		phonebook[k].birthday[j] = '\0';
		i++;

		int l = 0;
		for (l; l < 15 && array[i] != '\n' && array[i] != '\r'; i++, l++) {
			phonebook[k].phone[l] = array[i];
		}
		phonebook[k].phone[l] = '\0'; // incrementing k to add a new contact.
		k++;
	}

	
	
	fclose(p);
	return 0;
}

int saveCSV(struct PHONE_RECORD *phonebook) {
	FILE *j = fopen("phonebook.csv", "wt"); // overwriting the file with the current phonebook.
	fprintf(j, "Name,birthday,phone\n");
	for (int i = 0; i < 10; i++) {
		if (phonebook[i].name[0] != '\0') {
			fprintf(j, "%s,%s,%s\n", phonebook[i].name, phonebook[i].birthday, phonebook[i].phone);
		}
	}

	fclose(j);
	return 0;
}

int addRecord(struct PHONE_RECORD *phonebook, char nameInput[], char birthdayInput[], char phoneInput[]) {
	int i = 0;
	int filled = 0;
	while(i < 10) {
		if (phonebook[i].name[0] == '\0') {
			filled = 1; // we have found space to add a contact in the phonebook.
			
			phonebook[i].name[0] = '\0';
			strcpy(phonebook[i].name, nameInput); // remove the newline character.
			
			phonebook[i].birthday[0] = '\0';
			strcpy(phonebook[i].birthday, birthdayInput);
			
			phonebook[i].phone[0] = '\0';
			strcpy(phonebook[i].phone, phoneInput);

			break;
		}

		i++;
	}

	if (filled == 1) { // we successfully inputed the phone record.
		return 0;
	} else {
		printf("No more space in the CSV file.\n");
		return 1;
	}

}


int findRecord(struct PHONE_RECORD *phonebook, char nameFind[50]) {

	for (int i = 0; i < 10; i++) {
		if (strcmp(phonebook[i].name, nameFind) == 0) { // record exists in the phonebook.
			printf("%-20s %-15s %-15s\n", "----NAME---------", "------BIRTHDAY------", "-----PHONE-------");
			printf("%-20s %-17s %-15s\n", phonebook[i].name, phonebook[i].birthday, phonebook[i].phone); // printing the record.
			return 0;
		}
	}
	printf("Does not exist\n"); // if we got here, the contact is not in the phonebook.
	return 1;

}

int listRecords(struct PHONE_RECORD *phonebook) {
	if (phonebook[0].name[0] == '\0') {
		printf("Phonebook.csv does not exist\n");
		return 1;
	}

	printf("%-20s %-15s %-15s\n", "----NAME---------", "------BIRTH------", "-----PHONE-------"); // setting the header.
	for (int i = 0; i < 10; i++) {
		if (phonebook[i].name[0] != '\0') {
			printf("%-20s %-17s %-15s\n", phonebook[i].name, phonebook[i].birthday, phonebook[i].phone);

		}
	}
	return 0;
}















