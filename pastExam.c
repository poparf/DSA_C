////#define _CRT_SECURE_NO_WARNINGS
////#include "main.h"
////#include "DataUtil.h"
////#include "PastSubject.h"
////#define LINE_SIZE 256
////
////
////
////void main2()
////{
////	Arrival* root = NULL;
////
////
////	FILE* pFile = fopen("Data.txt", "r");
////	if (pFile)
////	{
////		char delimiter[] = ",";
////		char* token = NULL;
////		float income; int index = 0;
////		unsigned short reference;
////		char buffer[LINE_SIZE], name[LINE_SIZE];/
////		while (fgets(buffer, sizeof(buffer), pFile))
////		{
////			token = strtok(buffer, delimiter);
////			strcpy(name, token);
////			token = strtok(NULL, delimiter);
////			income = atof(token);
////			token = strtok(NULL, delimiter);
////			reference = atoi(token);
////			Student* stud = createStudent(name, income, reference);
////			// Insert
////			
////		}
////		// DS operation
////		// Delete and print
////
////
////	}
////}