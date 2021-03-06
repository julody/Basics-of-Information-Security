#include "Header.h"

cryptogram_t* initCryptogram()
{
	cryptogram_t* data = (cryptogram_t*)malloc(sizeof(cryptogram_t));
	if (data == NULL) return NULL;
	data->letter = (letter_t*)calloc(ALPHABET_SIZE, sizeof(letter_t));
	if (data->letter == NULL)
	{
		data = NULL;
		free(data);
		return NULL;
	}
	data->numOfLetters = 0;
	data->historyList = initHistoryList();
	data->wordListHead = NULL;

	FILE *f = fopen(DATA_PATH, "r");
	if ((f != NULL) && (fgetc(f) != EOF) && !(feof(f)))
	{
		initLetters(data->letter);
		initTextAndGetEncounters(data, f);
	}
	fclose(f);
	if (data->numOfLetters != NO_LETTERS)
	{
		getFrequencies(data);
		parseTextIntoWords(data);
	}
	return data;
}

void printCryptogram(cryptogram_t* data)
{
	system("cls");
	printEncryptionKey(data->letter);
	printText(data);

	printf("������� ������, ����� ��������� � ������� ����.\n");
	while (_getch() != RETURN_TO_MENU_BTN_CODE);
}

void printEncryptionKey(letter_t* letter)
{
	printf("������� ���� ����������:\n");
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		printf("%c -> ", (letter + i)->symbol);
		if ((letter + i)->replacedTo == NO_REPLACEMENT) printf("������ �� ����������");
		else printf("%c", (letter + i)->replacedTo);
		printf("\n");
	}
	printf("\n");
}

void printText(cryptogram_t* data)
{
	printf("����� ������������ � ������������ ��������:\n\n");
	char* ptr = data->text;
	while (*ptr)
	{
		if (isLetter(*ptr))
		{
			int curSymbolIndex = *(ptr)-'�';
			if ((data->letter + curSymbolIndex)->replacedTo == NO_REPLACEMENT)
				printf("%c", *ptr);
			else printf("%c", (data->letter + curSymbolIndex)->replacedTo);
		}
		else printf("%c", *ptr);
		ptr++;
	}
	printf("\n\n");
}

void cleanMemory(cryptogram_t* data)
{
	cleanWordsList(data);
	cleanHistoryList(data);

	data->text = NULL;
	free(data->text);

	data->letter = NULL;
	free(data->letter);

	data = NULL;
	free(data);
}