#include <stdio.h>
#include <string.h>

typedef struct{
	char name[50];
	char address[100];
	char phone_number[50];
} Record;


void writeRecordFile(char* file_name, Record* record_array, int numRecords);
void deleteRecord(int recordNum, int* numRecords, Record* record_array);
int readRecordFileRight(char* file_name, Record* record_array);

int main() {
	
	Record record_array[1000]; //might need to make dynamic in case more than 1000 records are stored

	char c;
	int i;
	int j;
	char file_name[50];
	char user_input[50];
	char command[10];
	char command_check[10];
	int flag = 1;
	char argument[50];
	int numRecords = 0; //default so if user writes before inputting records you wont get an error

	 do
	 {
		 printf("Enter a command: ");
		 scanf("%s", command);
		 fgets(argument, BUFSIZ, stdin);
		 sscanf(argument, "%s", argument); //trimming whitespace
		 strcpy(command_check, "read");
		 if (0 == strcmp(command, command_check))
		 {			
			 numRecords = readRecordFileRight(argument, record_array);
		 }

		 strcpy(command_check, "write");
		 if (0 == strcmp(command, command_check))
		 {
			 writeRecordFile(argument, record_array, numRecords);
		 }

		 strcpy(command_check, "print");
		 if (0 == strcmp(command, command_check))
		 {
			 for (int recordIndex = 0; recordIndex < numRecords; ++recordIndex)
			 {

				 printf("%d ", recordIndex + 1);
				 printf("%s\t", record_array[recordIndex].name);
				 printf("%s\t", record_array[recordIndex].address); 
				 printf("%s", record_array[recordIndex].phone_number); 
			 }
			 printf("\n");
		 }

		 strcpy(command_check, "delete");
		 if (0 == strcmp(command, command_check))
		 {
			 int recordNum = i = atoi(argument); //b/c argument is a string, we want to pass the int argument represents
			 deleteRecord(recordNum, &numRecords, record_array);
		 }
		 strcpy(command_check, "quit");
		 if (0 == strcmp(command, command_check))
		 {
			 flag = 0;
		 }
	 } while (1 == flag);

 
	return 0;
}



void writeRecordFile(char* file_name, Record* record_array, int numRecords)
{
	FILE * filePointer;

	filePointer = fopen(file_name, "w+");

	for (int i = 0; i < numRecords; ++i)
		fprintf(filePointer, "%s\t%s\t%s", record_array[i].name, record_array[i].address, record_array[i].phone_number);

	fclose(filePointer);

}

void deleteRecord(int recordNum, int* numRecords, Record* record_array)
{

	if (*numRecords <= 0)
	{
		printf("No records to delete.\n");
		return;
	}

	if( (recordNum > *numRecords) || (recordNum <= 0) )
	{
		printf("Invalid argument, try again\n");
			return;
	}
		

	int positionInArray = recordNum - 1;

	for (int i = positionInArray; i < *numRecords; ++i)
	{
		strcpy(record_array[i].name, record_array[i+1].name);
		strcpy(record_array[i].address, record_array[i + 1].address);
		strcpy(record_array[i].phone_number, record_array[i + 1].phone_number);
	}
	--(*numRecords);
	return;

}

//Reads a record file from disk and represents its contents in memory in a Record array
//Each element of the record array represents one line in the record file
//returns number of records read

int readRecordFileRight(char* file_name, Record* record_array)
{
	int recArrayIndex = -1;
	char* name;
	char* address;
	char* phone_number;
	char line[100000];
	int i;

	FILE *filePointer;

	
	filePointer = fopen(file_name, "r"); //opening the file for reading
	if (filePointer == NULL)
	{
		printf("Couldn't open file, exiting program");
		exit(1);
	}

	//read file a line at a time until empty, split the line up into 3 parts (name, addr, phone#) and store them in the RecordArray
	while (fgets(line, sizeof line, filePointer) != NULL)
	{

		if(0 == strcmp(line,"\n"))
		{
			break;
		}
		++recArrayIndex; //it starts at -1 so when it first enters itll be 0
		name = strtok(line, "\t");
		address = strtok(NULL, "\t");
		phone_number = strtok(NULL, "\t");
		strcpy(record_array[recArrayIndex].name, name);
		strcpy(record_array[recArrayIndex].address, address);
		strcpy(record_array[recArrayIndex].phone_number, phone_number);
	}

	fclose(filePointer);
	return (recArrayIndex + 1);
}
