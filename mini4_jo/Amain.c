// Jonathan Campana
// Jonathan.campana@mail.mcgill.ca
// department of science

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "mini4Aphone.c"


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



int menu(struct PHONE_RECORD *phonebook) {
	loadCSV(phonebook);
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
				if (strlen(nameInput) > 49) {
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					nameInput[49] = '\0'; // cap the string to 50 characters.
				}

				printf("Birthday: ");
				fgets(birthdayInput, 12, stdin);
				birthdayInput[strcspn(birthdayInput, "\n")] = '\0';
				if (strlen(birthdayInput) > 11) {
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					birthdayInput[11] = '\0';
				}
				
				printf("Phone: ");
				fgets(phoneInput, 15, stdin);
				phoneInput[strcspn(phoneInput, "\n")] = '\0';
				if (strlen(phoneInput) > 14) {
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					phoneInput[14] = '\0';
				}

				addRecord(phonebook, nameInput, birthdayInput, phoneInput);
				menu(phonebook);
				break;

			case 2:
				char findName[50];
				printf("Find name: ");
				clearBuffer();
				fgets(findName, 50, stdin);

				findName[strcspn(findName, "\n")] = '\0';

				findRecord(phonebook, findName);
				menu(phonebook);
				break;
			

			case 3:
				listRecords(phonebook);
				menu(phonebook);
				break;

			case 4:
				saveCSV(phonebook);
				printf("End of phonebook program\n");
				exit(0);
			
			default:
				menu(phonebook);
				break;
		}
		return 0;
}

int main() {
	
	struct PHONE_RECORD phonebook[10];
	memset(phonebook, 0, sizeof(struct PHONE_RECORD) * 10);	
	menu(phonebook);
}
