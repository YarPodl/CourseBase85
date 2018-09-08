#include "code.h"







void code::encode()
{
	inputFile.open(fileNameBinary, ios::binary);	// Открытие файла
	if (!inputFile.is_open())	// Проверка открылся ли файл
	{
		throw codeException("Не удалось открыть файл " + fileNameBinary);	// Возбудить исключение
	}
	outputFile.open(fileNameBase85);	// Открытие файла
	if (!outputFile.is_open())	// Проверка открылся ли файл
	{
		throw codeException("Не удалось открыть файл " + fileNameBase85);	// Возбудить исключение
	}
	unsigned int blockBinary;		// Блок бинарных данных
	char *blockBase85 = new char[5];// Блок даннах закодированных в base85
	char oneByte;	// Переменная, в которую читается один байт
	int countNotBytes = 0;	// Количество байт, которых не хватает для блока
	while (!inputFile.eof())	// Пока не конец файла
	{
		blockBinary = 0;
		for (int i = 3; i > -1; i--)	// Чтение 4 байт
		{
			if (!(inputFile.get(oneByte)))	// Прочитать байт 
			{
				// Если не удалось (файл кончился)
				oneByte = 0;		// обнулить его
				countNotBytes++;	// Увеличить счетчик непрочитанных байт
			}
			blockBinary += oneByte << i * 8;	// Записать байт в блок бинарных данных
		}

		if (countNotBytes == 4) break;	// Если не прочитано не одного байта, выйти из цикла

		for (int i = 4; i > -1; i--, blockBinary /= 85)	// Преобразование из бинарного вида в Base85
		{
			blockBase85[i] = blockBinary % 85 + 33;
		}
		outputFile.write(blockBase85, (5 - countNotBytes) * sizeof(char));	// Запись блока base85 в файл
	}
}

void code::decode()
{
	inputFile.open(fileNameBase85);	// Открытие файла
	if (!inputFile.is_open())	// Проверка открылся ли файл
	{
		throw codeException("Не удалось открыть файл " + fileNameBase85);	// Возбудить исключение
	}
	outputFile.open(fileNameBinary, ios::binary);	// Открытие файла
	if (!outputFile.is_open())	// Проверка открылся ли файл
	{
		throw codeException("Не удалось открыть файл " + fileNameBinary);	// Возбудить исключение
	}
	unsigned int blockBinary;		// Блок бинарных данных
	char oneChar;	// Переменная, в которую читается один байт
	char *blockBase85 = new char[5];// Блок даннах закодированных в base85
	int countNotChars = 0;	// Количество символов, которых не хватает для блока
	while (!inputFile.eof())	// Пока не конец файла
	{
		blockBinary = 0;
		for (int i = 0; i < 5; i++)		// Чтение 5 символов
		{
			if (!(inputFile.get(oneChar)))	// Чтение одного символа
			{
				// Если не удалось (файл кончился)
				oneChar = 'u';		// заменить его на 'u'
				countNotChars++;	// Увеличить счетчик непрочитанных сиволов
			}
			// Если символ принадлежит диапазону base85
			if ((oneChar >= '!') && (oneChar <= 'u'))
			{
				blockBinary += (oneChar - 33) * (int) pow(85.0, 4 - i);	// Преобразовать в бинарный вид
			}
			else	// Иначе
			{
				if (isspace(oneChar))	// Если пробельный символ
				{
					// Пропустить символ
					i--;
				}
				else // Если постронний символ
				{
					throw codeException("Встречен постронний символ");	// Возбудить исключение
				}
			}
		}

		if (countNotChars == 5) break;	// Если не прочитано ни одного символа, закончить цикл

		for (int i = 0; i < 4 - countNotChars; i++)	// Запись байт в файл
		{
			char t = blockBinary >> (3 - i) * 8;	// Выделение байта для записи
			outputFile.write(&t, sizeof(char));		// Запись байта
		}
	}
}

code::code(string fNameBase85, string fNameBinary)
{
	// Присвоение
	fileNameBinary = fNameBinary;
	fileNameBase85 = fNameBase85;
}


code::~code()
{
	// Закрытие файлов
	inputFile.close();
	outputFile.close();
}


