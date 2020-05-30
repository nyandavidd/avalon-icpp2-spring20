#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "bookFunctions.h";
using namespace std;
using namespace ext;


//extern const float PI; - напомнили о константе из другого файла
// static const подгружать нельзя!

const string BOOK_FILE_NAME = "book.bin";
const string ID_FILE_NAME = "idList.txt";



int main()
{
    setlocale(LC_ALL, "RU");
    // First\0\0\0\0\0\0...

    ofstream fout;
    fout.open(BOOK_FILE_NAME, ios::binary | ios::in | ios::ate);
    ifstream fin;
    fin.open(BOOK_FILE_NAME, ios::binary);
    ifstream finId;
    finId.open("idList.txt");
    ofstream foutId;
    foutId.open("idList.txt");


    if (!( fout.is_open() && fin.is_open() && finId.is_open() && foutId.is_open()))
    {
        cerr << "file didnt open!\n";
        return 1;
    }
    
    int maxId;
    finId >> maxId;
    finId.ignore(numeric_limits<int>::max(), '\n');
    //Book* listOfBooks = new Book[maxId];
    finId.clear();


    Book* tempBook;
    addBook(BOOK_FILE_NAME, fout);
    maxId = maxId + 111;
    foutId << maxId;


    fin.clear();
    fin.seekg(ios::beg);
    initialisateBook(fin, tempBook, 2);

    cout << tempBook[1].Author.titlePtr;

    fout.close();
    fin.close();
    finId.close();
    foutId.close();
}