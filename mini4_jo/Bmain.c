// Jonathan Campana 260985613
// Jonathan.campana@mail.mcgill.ca
// Department of science
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "mini4Bphone.c"


int option() {

	printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit>");	
	int choiceInt;
	scanf("%d", &choiceInt);
	return choiceInt;
}

void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

}



int menu(struct PHONE_RECORD *phonebook, int size) {
	loadCSV(phonebook, size);
	int choiceInt = option();

		switch (choiceInt) {

			case 1:
				char nameInput[50];
				char birthdayInput[12];
				char phoneInput[15];
				printf("Name: ");
				clearBuffer();
				fgets(nameInput, 50, stdin);
				nameInput[strcspn(nameInput, "\n")] = '\0';
				
				printf("Birthday: ");
				fgets(birthdayInput, 12, stdin);
				birthdayInput[strcspn(birthdayInput, "\n")] = '\0';
				
				printf("Phone: ");
				fgets(phoneInput, 15, stdin);
				phoneInput[strcspn(phoneInput, "\n")] = '\0';

				addRecord(phonebook, nameInput, birthdayInput, phoneInput, size);
				menu(phonebook, size);
				break;

			case 2:
				char findName[50];
				printf("Find name: ");
				clearBuffer();
				fgets(findName, 50, stdin);

				findName[strcspn(findName, "\n")] = '\0';

				findRecord(phonebook, findName, size);
				menu(phonebook, size);
				break;
			

			case 3:
				listRecords(phonebook, size);
				menu(phonebook, size);
				break;

			case 4:
				saveCSV(phonebook, size);
				printf("End of phonebook program\n");
				free(phonebook);
				exit(0);
			
			default:
				menu(phonebook, size);
				break;
		}
		return 0;
}

int main() {
	int size;
	printf("Size of the phonebook: ");
	scanf("%d", &size);
	struct PHONE_RECORD *phonebook = malloc(size * sizeof(struct PHONE_RECORD));
	if (phonebook == NULL) {
		printf("Array to large! Program terminated.\n");
		exit(1);
	}

	memset(phonebook, 0, sizeof(struct PHONE_RECORD) * 10);	
	menu(phonebook, size);
}
