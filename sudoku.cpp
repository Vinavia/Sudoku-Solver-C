// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include <fcntl.h>
#include <string.h>

int checkConstraints(int sudBoard[9][9], int i, int j)
{
	int index = sudBoard[i][j];
	int arrLeft[9];
	int k;
	int l;
	int indexToRemove;
	int count = 0;
	int max = 0;


	if (index != 0)
		return index;

	for (k = 0; k < 9; k++)
	{
		arrLeft[k] = (k + 1);
	}

	for (k = 0; k < 9; k++)
	{
		if (sudBoard[i][k] != 0)
		{
			indexToRemove = sudBoard[i][k];
			arrLeft[indexToRemove - 1] = 0;
		}
		if (sudBoard[k][j] != 0)
		{
			indexToRemove = sudBoard[k][j];
			arrLeft[indexToRemove - 1] = 0;
		}
	}

	for (k = 0; k < 3; k++)
	{
		for (l = 0; l < 3; l++)
		{
			if (sudBoard[k + ((i / 3) * 3)][l + ((j / 3) * 3)] != 0)
			{
				indexToRemove = sudBoard[k + ((i / 3) * 3)][l + ((j / 3) * 3)];
				arrLeft[indexToRemove - 1] = 0;
			}
		}
	}
	for (k = 0; k < 9; k++)
	{
		if (arrLeft[k] != 0)
		{
			count++;
			if (arrLeft[k] > max)
				max = arrLeft[k];
		}
	}

	if (count > 1 || count == 0)
		return 0;

	return max;

}
int solveAcThree(int sudBoard[9][9])
{
	int i;
	int j;
	int index;
	int change;
	int proxy;

	while (1 == 1)
	{
		change = 0;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				proxy = sudBoard[i][j];
				index = checkConstraints(sudBoard, i, j);
				sudBoard[i][j] = index;
				if (proxy != index)
					change = 1;
			}
		}
		if (change == 0)
			break;
	}
	/*
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d", sudBoard[i][j]);
		}
	}
	*/
	return 1;
}

int solveOther(int sudBoard[9][9])
{

	return 0;
}

void sudFromFile(char* file, int sudBoard[9][9]){
	FILE* fp;
	if ((fp = fopen(file, "r")) == NULL){
		printf("Could not open file");
		exit(1);
	}

	int i;
	int lineNum = 0;
	char line[11];
	while (fgets(line, sizeof(line), fp) != NULL && lineNum < 10){

		printf("line num %d  individual input: ", lineNum);
		for (i = 0; i < 9; i++){
			
			sudBoard[lineNum][i] = (line[i] - '0');
			printf("%d", (line[i] - '0'));
			
		}
		printf("\n");
		lineNum++;
		
	}

	fclose(fp);

}

void sudToFile(int sudBoard[9][9]){
	
	//Read save file
	FILE* fpIncRead;
	
	if ((fpIncRead = fopen("sudokuInc.txt", "r")) == NULL){
		printf("Could not read file");
		//exit(1);
	}
	char line[8];
	int increment = 0;
	fgets(line, sizeof(line), fpIncRead);
	increment = atoi(line);
	fclose(fpIncRead);

	//Write save file
	FILE* fpIncWrite;
	if ((fpIncWrite = fopen("sudokuInc.txt", "w")) == NULL){
		printf("Could not write file");
		exit(1);
	}
	fprintf(fpIncWrite, "%d", ++increment);
	fclose(fpIncWrite);



	FILE* fp;
	char fileName[32];
	sprintf_s(fileName, sizeof(char) * 32, "puzzles/sudoku%i.txt", increment);
	if ((fp = fopen(fileName, "w")) == NULL){
		printf("Could not write file");
		exit(1);
	}

	int j;
	int i;
	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			fprintf(fp, "%d",sudBoard[i][j]);
		}
		fprintf(fp, "\n");
	}
	
	fclose(fp);
}
int** generateSudBoard(){
	int sBoard[9][9];
	int j;
	int i;
	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			sBoard[i][j] = 0;
		}
	}

	return 0;

}
void printSud(int sudBoard[9][9]){
	int i;
	int j;
	for (i = 0; i < 9; i++)
	{
		printf("\n");
		
		if (i % 3 == 0){
			printf("  -----------------\n");
		}
		for (j = 0; j < 9; j++)
		{
			if (j % 3 == 0){
				printf(" | ");
			}
			printf("%d", sudBoard[i][j]);
		}
		printf(" |");
	}
	printf("\n  -----------------\n");
}

int main()
{
	int arrSudokuBoard[9][9];
	int sBoard[9][9];
	int solveable;
	int j;
	int i;

	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			arrSudokuBoard[i][j] = 0;
		}
	}

	arrSudokuBoard[0][2] = 3;
	arrSudokuBoard[0][4] = 2;
	arrSudokuBoard[0][6] = 6;
	arrSudokuBoard[1][0] = 9;
	arrSudokuBoard[1][3] = 3;
	arrSudokuBoard[1][5] = 5;
	arrSudokuBoard[1][8] = 1;
	arrSudokuBoard[2][2] = 1;
	arrSudokuBoard[2][3] = 8;
	arrSudokuBoard[2][5] = 6;
	arrSudokuBoard[2][6] = 4;
	arrSudokuBoard[3][2] = 8;
	arrSudokuBoard[3][3] = 1;
	arrSudokuBoard[3][5] = 2;
	arrSudokuBoard[3][6] = 9;
	arrSudokuBoard[4][0] = 7;
	arrSudokuBoard[4][8] = 8;
	arrSudokuBoard[5][2] = 6;
	arrSudokuBoard[5][3] = 7;
	arrSudokuBoard[5][5] = 8;
	arrSudokuBoard[5][6] = 2;
	arrSudokuBoard[6][2] = 2;
	arrSudokuBoard[6][3] = 6;
	arrSudokuBoard[6][5] = 9;
	arrSudokuBoard[6][6] = 5;
	arrSudokuBoard[7][0] = 8;
	arrSudokuBoard[7][3] = 2;
	arrSudokuBoard[7][5] = 3;
	arrSudokuBoard[7][8] = 9;
	arrSudokuBoard[8][2] = 5;
	arrSudokuBoard[8][4] = 1;
	arrSudokuBoard[8][6] = 3;
	char* path = "puzzles/sudoku2.txt";
	sudFromFile(path, sBoard);

	printSud(arrSudokuBoard);
	//solveable = solveAcThree(arrSudokuBoard);
	//printf("\n Solvable: %d", solveable);
	printSud(arrSudokuBoard);


	printf("\n\n Before Solve: \n");
	printSud(sBoard);
	
	solveable = solveAcThree(sBoard);
	printf("\n Solvable: %d", solveable);
	printf("\n\n After Solve: \n");
	printSud(sBoard);
	sudToFile(sBoard);
	system("pause");
	return 0;
}