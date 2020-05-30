#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
namespace ext
{
	struct Data
	{
		short length;
		char* titlePtr;
	};

	struct Book
	{
		static const int BUFFER_SIZE = 20;
		//выдел€етс€ не в структурах, а в глоб. пам€ти (1 раз)
		//однако обратитьс€ надо через Book::BUFFER_SIZE;

		int Id;
		Data Title;
		Data Author;
		float Price;
		int Quantity;
	};
	void inputIntValue(string message, int& value)
	{
		cout << message;
		cin >> value;
		cin.ignore(numeric_limits<int>::max(), '\n');
	}

	void inputFloatValue(string message, float& value)
	{
		cout << message;
		cin >> value;
		cin.ignore(numeric_limits<float>::max(), '\n');
	}


	void inputData(string message, Data& data)
	{
		short count = 0;
		string text;
		cout << message;
		cin >> text;
		cin.ignore(numeric_limits<char>::max(), '\n');
		do
		{
	    ++count;
		} while (text[count] != '\0');
		data.length = count;
		data.titlePtr = new char[data.length];
		for (int i = 0; i < count; i++)
		{
			data.titlePtr[i] = text[i];
		}
	}

	void addBook(string FILENAME, ofstream& fout)
	{
		Book tempBook;
		short int currentId = 0;
		inputData("”кажите название книги: ", tempBook.Title);
		inputData("”кажите автора книги: ", tempBook.Author);
		inputFloatValue("”кажите стоимость книги", tempBook.Price);
		inputIntValue("”кажите количество книг: ", tempBook.Quantity);

		fout.write(reinterpret_cast<char*>(&tempBook.Title.length), sizeof(tempBook.Title.length));
		fout.write(reinterpret_cast<char*>(tempBook.Title.titlePtr), tempBook.Title.length);
		fout.write(reinterpret_cast<char*>(&tempBook.Author.length), sizeof(tempBook.Author.length));
		fout.write(reinterpret_cast<char*>(tempBook.Author.titlePtr), tempBook.Author.length);
		fout.write(reinterpret_cast<char*>(&tempBook.Price), sizeof(tempBook.Price));
		fout.write(reinterpret_cast<char*>(&tempBook.Quantity), sizeof(tempBook.Quantity));
		
	}
	
	void initialisateBook(ifstream& fin, Book*& book, int Id) 
	{
		book = new Book[Id];
		for (int i = 0; i < Id; i++)
		{
			book[i].Id = i;
			fin.read(reinterpret_cast<char*>(book[i].Title.length), sizeof(book[i].Title.length));
			fin.read(reinterpret_cast<char*>(book[i].Title.titlePtr), book[i].Title.length);
			fin.read(reinterpret_cast<char*>(&book[i].Author.length), sizeof(book[i].Author.length));
			fin.read(reinterpret_cast<char*>(book[i].Author.titlePtr), book[i].Author.length);
			fin.read(reinterpret_cast<char*>(&book[i].Price), sizeof(book[i].Price));
			fin.read(reinterpret_cast<char*>(&book[i].Quantity), sizeof(book[i].Quantity));
		}
	}
	
	void editBook(Book* book, int Id) {
		inputData("”кажите название книги: ", book[Id].Title);
		inputData("”кажите автора книги: ", book[Id].Author);
		inputFloatValue("”кажите стоимость книги", book[Id].Price);
		inputIntValue("”кажите количество книг: ", book[Id].Quantity);
	}





}