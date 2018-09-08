#pragma once
#include <fstream>
#include <string>
#include <exception>

using namespace std;


/// Класс кодирующий и декодирующий файлы в формат base85
class code
{
private:
	/// Файловый поток, для исходного файла
	ifstream inputFile;
	/// Файловый поток, для итогового файла
	ofstream outputFile;
	///	Название файла, закодированного в base85
	string fileNameBase85;
	///	Название незакодированного файла
	string fileNameBinary;
public:
	/// Закодировать файл
	void encode();
	/// Декодировать файл
	void decode();
	/// Конструктор
	/// @param fileNameBase85 Название файла, закодированного в base85
	/// @param fileNameBinary Название незакодированного файла
	code(string fileNameBase85, string fileNameBinary);
	/// Деструктор, закрытие файловых потоков
	~code();

	/// Класс исключений для класса code
	class codeException : exception
	{
	public:
		/// Конструктор
		/// @param mes Сообщение
		codeException(string mes)
		{
			message = mes; 
		}
		/// Получение сообщения
		/// @return Сообщение
		string what() 
		{ 
			return message;
		}
	private:
		/// Сообщение
		string message;
	};

};

