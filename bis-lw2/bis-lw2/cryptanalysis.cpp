/*�������:
����� �� ������� ������ ����� ������� �����
�� ������ ���� �������������� ������
"�������������� �� ������ ������ �����" ��� ��������
������� ������� ������� � �� ��� ������ ���� ������
���������� �� ������ ����� ������������� �����
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

#define SIZE_OF_STRING_TO_COPY 1000
#define ALPHABET_SIZE 32
#define NO_REPLACEMENTS 0
#define EMPTY_TEXT 0
#define DATA_PATH "input.txt"
#define LETTERS_IN_ORDER_BY_FREQUENCY_DESC "��������������������������������"
#define ALPHABET "��������������������������������"

#define INVALID_DATA_MESSAGE "���������� ������ �� �������� ��� �����������: ����������� �����.\n"
#define SUCESS_INIT_MESSAGE "�������� ����� ������������ ������� ��������.\n"

typedef enum 
{
	NULL_OPERATION,              //�������� ��� �������������
	ANALYZE,                     //������ ������� ���� �� ������� ����� � ����� �������������� ����� � ����������� � ��������� ������������� ���� �������� ��������
	PRINT_WORDS_BY_LENGTH,       //����� �� ����� ���� ����, ��������������� �� ���������� ����
	PRINT_WORDS_BY_UNDECIPHERED, //����� �� ����� ���� ����, ��������������� �� ���������� ���������������� �� ������ ������ ����
	PRINT_BUF,                   //����������� ������������ � ��������� ��������������� �� ������ ������ ������
	REPLACE_LETTERS,             //����������� ������ ���� � ������������
	REVERT,                      //�������� � ����� ������� ������ ���� � ������������
	AUTOREPLACEMENT,             //�������������� ������ ����
	EXIT 
} OPERATION_CODE;

typedef enum Bool
{ 
	FALSE, 
	TRUE 
} BOOL;

typedef struct Letter
{
	int encounteredInSrcText; //������� ��� ���������� � ������ - ��� ������������ �������
	float frequencyInSrcText; //���������� ��� ������������� - � ������ �������
	char replacedTo;
} LETTER;

typedef struct Cryptogram
{
	char* text; //����� � �������� �������� ��� ������
	LETTER* letter;
} CRYPTOGRAM;

void initLetters(LETTER* letter)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		(letter + i)->encounteredInSrcText = 0;
		(letter + i)->frequencyInSrcText = 0;
		(letter + i)->replacedTo = NO_REPLACEMENTS;
	}
}

BOOL isLetter(char item)
{
	if (item <= '�' && item <= '�') return TRUE;
	else return FALSE;
}

void swap(char* a, char* b)
{
	char* temp = a;
	a = b;
	b = temp;
}

void handleDataFromNewString(CRYPTOGRAM* data, char* str)
{
	int sizeOfOldText = 0; 
	char* sav = data->text; //��������� ���������
	while (*(data->text)) //�������� �����, ��� ������ ���������
	{
		sizeOfOldText++;
		data->text++;
	}

	data->text = sav;
	data->text = (char*) realloc(data->text, (sizeOfOldText + SIZE_OF_STRING_TO_COPY) * sizeof(char)); //��������� ������
	
	sav = data->text;
	data->text += sizeOfOldText;
	while (*str) //���������� �������
	{
		*(data->text) = *str;
		if (isLetter(*(data->text))) (data->letter + (*(data->text) - 'A'))->encounteredInSrcText++;
		(data->text)++;
		str++;
	}
	*(data->text) = '\0';
	data->text = sav;
}

void initTextAndCalculateEncounters(CRYPTOGRAM* data, FILE* f)
{
	fclose(f);
	f = fopen(DATA_PATH, "r");
	char* temp = (char*) calloc(SIZE_OF_STRING_TO_COPY, sizeof(char));
	while (fgets(temp, SIZE_OF_STRING_TO_COPY * sizeof(char), f) != NULL) handleDataFromNewString(data, temp);
	free(temp);
}

CRYPTOGRAM* initCryptogram()
{
	CRYPTOGRAM* data = malloc(sizeof(char*) + sizeof(LETTER*));
	data->text = malloc(sizeof(char));
	data->letter = (LETTER*)calloc(ALPHABET_SIZE, sizeof(LETTER));
	*(data->text) = EMPTY_TEXT;

	FILE *f = fopen(DATA_PATH, "r");
	if ((f != NULL) && (fscanf(f, "%s") != EOF))
	{
		initLetters(data->letter);
		initTextAndCalculateEncounters(data, f);
	}
	fclose(f);
	return data;
}

void printMainMenu()
{
	printf("��� ������������ ���������, ����������� ������� ����������� ���������������. ��������� ��������:\n");
	printf("1. ������������� ������� ���� � ���������� ������\n");
	printf("2. ������� �����, ��������������� �� ���������� ����\n");
	printf("3. ������� �����, ��������������� �� ���������� ���������������� ����\n");
	printf("4. ���������� ������������\n");
	printf("5. �������� �����\n");
	printf("6. �������� ���� �� ��������� �����\n");
	printf("7. ���������� �������������� ������\n");
	printf("8. �����\n");
	printf("������� ��� ������ ������� (����� ���, ����� �������������, ����� ��������������): ");
}

void suggestReplacementsBasingOnFrequencyAnalysis(CRYPTOGRAM* data)
{
	//TODO
}

void printWordsInOrderByLength(char* text)
{
	//TODO
}

void printWordsInOrderByUndeciphered(char* text)
{
	//TODO
}

void printText(char* text)
{
	//�������� �����
    //���������� ��������� � ��������� ��������
	//������� ������������
	//�������� ����� ��� ����������� � ����
}

void handleReplacementMenu(CRYPTOGRAM* data)
{
	//TODO
}

void handleRevertMenu(CRYPTOGRAM* data)
{
	//TODO
	//������� ������ ���������� ����� � ���������� ����������� ������
}

void replaceLettersAutomatically(CRYPTOGRAM* data)
{
	//TODO
}

void printCryptoInfo(CRYPTOGRAM* data)
{
	char* symbolPtr = data->text; //���������� ������������
	while (*symbolPtr)
	{
		printf("%c", *symbolPtr);
		symbolPtr++;
	}
	//���������� ���� ����� - ���������� ������, �������� replacedTo
}

void handleMainCycle(CRYPTOGRAM* data)
{
	OPERATION_CODE operationCode = NULL_OPERATION;
	do 
	{
		system("cls");
		printCryptoInfo(data); //�������
		printMainMenu();
		scanf("%i", &operationCode);
		switch (operationCode)
		{
		case ANALYZE: suggestReplacementsBasingOnFrequencyAnalysis(data); break;
		case PRINT_WORDS_BY_LENGTH: printWordsInOrderByLength(data->text); break;
		case PRINT_WORDS_BY_UNDECIPHERED: printWordsInOrderByUndeciphered(data->text); break;
		case PRINT_BUF: printText(data->text); break;
		case REPLACE_LETTERS: handleReplacementMenu(data); break;
		case REVERT: handleRevertMenu(data); break;
		case AUTOREPLACEMENT: replaceLettersAutomatically(data); break;
		case EXIT: break;
		default: break;
		}
	} while (operationCode != EXIT);
}

int main(void)
{
	setlocale(LC_ALL, "rus");

	CRYPTOGRAM* data = initCryptogram();
	if (data->text == EMPTY_TEXT) //� ���������� ������ ��� ����
	{
		printf(INVALID_DATA_MESSAGE);
		_getch();
	}
	else handleMainCycle(data);
	free(data);
	return 0;
}