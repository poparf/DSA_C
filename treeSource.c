//#define _CRT_SECURE_NO_WARNINGS
//#include "DataUtil.h"
//#include "GraphUtil.h"
//#define LINE_SIZE 256
//
//void main3()
//{
//	Student* students[10]; 
//	memset(students, 0, sizeof(students));
//	int i = 0;
//	
//	Node* graphList = NULL;
//
//	FILE* pFile = fopen("Data.txt", "r");
//	if (pFile)
//	{
//		char delimiter[] = ",";
//		char* token = NULL;
//		float income; int index = 0;
//		unsigned short reference;
//		char buffer[LINE_SIZE], name[LINE_SIZE];
//		while (fgets(buffer, sizeof(buffer), pFile))
//		{
//			token = strtok(buffer, delimiter);
//			strcpy(name, token);
//			token = strtok(NULL, delimiter);
//			income = atof(token);
//			token = strtok(NULL, delimiter);
//			reference = atoi(token);
//			Student* stud = createStudent(name, income, reference);
//			// Insert
//			students[i++] = stud;
//		}
//		// DS operation
//		// Delete and print
//		
//		addEdge(&graphList, students[0], students[3]);
//		addEdge(&graphList, students[0], students[5]);
//		addEdge(&graphList, students[1], students[2]);
//		addEdge(&graphList, students[1], students[4]);
//		addEdge(&graphList, students[2], students[3]);
//		addEdge(&graphList, students[3], students[4]);
//		addEdge(&graphList, students[4], students[5]);
//		addEdge(&graphList, students[5], students[6]);
//
//		displayGraph(graphList);
//		int nrElem = 7;
//		MatNode** adjacencyMatrix = NULL;
//		adjacencyMatrix = (MatNode**)malloc(sizeof(MatNode*) * nrElem);
//		
//		for (int i = 0; i < nrElem; i++)
//		{
//			adjacencyMatrix[i] = (MatNode*)malloc(sizeof(MatNode) * nrElem);
//			memset(adjacencyMatrix[i], 0, sizeof(MatNode) * nrElem);
//		}
//			convertListToMat(graphList, adjacencyMatrix, nrElem);
//
//	}
//}