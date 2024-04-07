#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define rows 5
#define characters 129
#define words 5

char Letters[] = "QqwWeErRtTyYuUiIoOpPaAsSdDfFgGhHjJkKlLzZxXcCvVbBnNmMm";
char* userArray[rows][characters];
unsigned int wordCounter = 0;

int main()
{
	input();

	output();

	consonantCounter();

	return 0;
}

int input(void) // rows <= 20; letters <= 128; 2 <=  words <= 20; enter -> next string; 'esc' -> end of input;
{
	char character;

	for (int i = 0; i < rows; i++)
	{
		wordCounter = 0;

		for (int j = 0; j < characters; j++)
		{
			character = getch();

			if (character != 13 && character != 27)
			{
				if (character != 8) //если нажат не enter, не escape и не backspace
				{
					userArray[i][j] = character;
					fprintf(stdout, "%c", character);

					if (j != 0) // если не первый элемент
					{
						if (isWord(i, j - 1) == 0 && (userArray[i][j] == ' ' || userArray[i][j] == '\t')) // если нажат пробел или таб - проверка на слово
						{
							wordCounter += 1;

							if (wordCounter == words) //если счетчик равен лимиту 
							{
								printf("\n");
								break;
							}
						}
					}
				}
				else //если нажат backspace
				{
					if (j >= 2) //если это не первый символ в строке
					{
						//если последний символ буква, а предпоследний символ пробел или таб, то счетчик слов -1
						if ((strchr(Letters, userArray[i][j - 1]) != NULL) && (userArray[i][j - 2] == " " || userArray[i][j - 2] == "\t"))
						{
							if (wordCounter > 0)
								wordCounter -= 1;
						} //если последний символ пробел, а предпоследний буква, то счетик слов -1
						else if ((userArray[i][j - 1] == ' ' || userArray[i][j - 1] == '\t') && (strchr(Letters, userArray[i][j - 2]) != NULL))
						{
							if (wordCounter > 0)
								wordCounter -= 1;
						}

						userArray[i][j - 1] = '\0'; //последний напечатанный символ заменяем на конец строки

						printf("\b \b");

						j = j - 2; // уменьшаем j на 2, предыдущий символ + нулевой символ
					}
					else if (0 < j < 2)
					{
						if ((strchr(Letters, userArray[i][0]) != NULL) && (userArray[i][1] == " " || userArray[i][1] == "\t"))
						{
							if (wordCounter > 0)
								wordCounter -= 1;
						}

						userArray[i][0] = ' '; //maybe not \0 but ' '; yeah ' ' is alright (at least it works)

						printf("\b \b");

						j = 0; 
					}
				}
			}
			else if (character == 27 && wordCounter >= 2) //нажат esc и введено хотя бы 2 слова
			{
				return 0;
			}
			else if (character == 13 && wordCounter >= 2) //нажат enter и введено хотя бы 2 слова
			{
				printf("\n");
				break;
			}
			else
			{
				//не введено хотя бы 2 слова
			}
		}
	}
}

int isWord(int i, int j) //если в последовательности символов есть хотя бы одна буква до первого пробела, то это слово
{
	int thereIsALetter = 0; // флаг опущен

	for (j; j >= 0; j--)
	{
		if (userArray[i][j] != ' ' && userArray[i][j] != '\t') // не пробел и не таб /!/
		{
			for (int k = 0; k < strlen(Letters); k++) //по буквам 
			{
				if (userArray[i][j] == Letters[k]) // является ли символ буквой
				{
					thereIsALetter = 1; // поднятие флага
				}
			}
		}
		else
		{
			break;
		}
	}

	if (thereIsALetter != 0) // если флаг поднят
	{
		return 0; //это слово
	}
	else
	{
		return 1; //не слово
	}
}

int output(void)
{
	printf("\n\nText:\n");
	for (int i = 0; i < rows; i++)
	{
		if (userArray[i][0] != '\0') //если первый символ строки не равен \0, т.е. строка не пуста
		{
			for (int j = 0; j < characters; j++) //то выводим все символы этой строки
			{
				printf("%c", userArray[i][j]);
			}
		}
		else //если строка все-таки пуста, то переходим к следующей строке
		{
			break;
		}

		printf("\n");
	}
}

int consonantCounter(void)
{
	char MyStr[100], ModString[250];
	char EnDisowels[] = "qwrtpsdfghjklzxcvbnmQWRTPSDFGHJKLZXCVBNM";
	int CountDisowels = 0;

	int i = 0;

	printf("\nModified text:\n");

	for (i; i < rows; i++)
	{
		CountDisowels = 0;

		for (int j = 0; j < characters; j++)
		{
			for (int k = 0; k < strlen(EnDisowels); k++) // по согласным
			{
				if (userArray[i][j] == EnDisowels[k]) // является ли буква согласной
				{
					CountDisowels++;
					break;
				}
			}
		}

		sprintf(ModString, "%d %c", CountDisowels, ' '); // колво согласных и пробел

		CountDisowels = 0;

		if (userArray[i][0] != '\0') // если первый элемент не пустой
		{
			printf("%s", ModString);

			for (int c = 0; c < characters; c++) //вывод всех символов
			{
				printf("%c", userArray[i][c]);
			}
		}
		else
		{
			CountDisowels = 0;
			break; // если пустая, то следующая 
			//               test temp

		}

		printf("\n");
	}
}
