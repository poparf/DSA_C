#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include "CrackingGraphs.h"


void main()
{
	Student* studs[100];
	Node* mainVertex = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		float income; int index = 0;
		unsigned short reference;
		char buffer[LINE_SIZE], name[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			reference = atoi(token);
			Student* stud = createStudent(name, income, reference);
			// Insert
			studs[index++] = stud;
		}
		// DS operation
		// Delete and print
	
		addEdge(&mainVertex, studs[0], studs[1]);
		addEdge(&mainVertex, studs[0], studs[2]);
		addEdge(&mainVertex, studs[1], studs[2]);
		addEdge(&mainVertex, studs[1], studs[3]);
		addEdge(&mainVertex, studs[1], studs[5]);
		addEdge(&mainVertex, studs[2], studs[6]);
		addEdge(&mainVertex, studs[3], studs[4]);
		addEdge(&mainVertex, studs[5], studs[6]);
		// Root node is 6
		BFS(mainVertex);
	}
}