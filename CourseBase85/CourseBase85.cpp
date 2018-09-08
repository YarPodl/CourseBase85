// CourseBase85.cpp: определяет точку входа для консольного приложения.
//

#include "code.h"
#include <iostream>
#include <windows.h>

int main()
{

	try		// Блок проверки исключений
	{
		SetConsoleCP(1251);		// установка кодировки для ввода
		SetConsoleOutputCP(1251);// установка кодировки для вывода
		int n;			// Переменная для ввода
		string fileNameBase85;
		string fileNameBinary;
		cout << "Введите название файла base85:" << endl;
		getline(cin, fileNameBase85);
		cout << "Введите название бинарного файла:" << endl;
		getline(cin, fileNameBinary);
		cout << "Введите:"
			<< endl << "1 - чтобы закодировать бинарный файл"
			<< endl << "2 - чтобы декодировать файл base85"
			<< endl;	// Вывод подсказки

		code coder(fileNameBase85, fileNameBinary);	// Инициализация объекта
		cin >> n;		// Ввод числа
		switch (n)		
		{
		case 1:
			coder.encode();		// Кодирование
			cout << "Операция проведена успешно" << endl;
			break;
		case 2:
			coder.decode();		// Декодирование
			cout << "Операция проведена успешно" << endl;
			break;
		default:
			break;
		}
	}
	catch (code::codeException &e)		// Если произошло исключение
	{
		cout << e.what() << endl;		// Вывод сообщения
	}
	Sleep(10000); // Ожидание перед закрытием программы
    return 0;
}

