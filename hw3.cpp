﻿// hw3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Debug/Extention.hpp"
using namespace std;
using namespace ext;
const int N = 10;
int main()
{
	setlocale(LC_ALL, "RU");
	const int N = 10;
	int agents[N][12];
	for (int i = 0; i < N; i++){
		for (int j = 0; j < 12; j++) {
			bool IsWorking = GetRandomValue(0, 1);
			if (IsWorking == 0 || agents[i][j - 1] == -1 && agents[i][j - 2] != -1) {
				agents[i][j] = -1;
			}
			if(IsWorking == 1 || agents[i][j - 1] != -1 && agents[i][j - 2] == -1) agents[i][j] = GetRandomValue(1000, 100000);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%5d ", agents[i][j]);
		}
		cout << endl;
	}
	cout << endl;
	for (int k = 0; k < N; k++) {      // сортирует верно! но у последнего агента почему-то появлялось мусорное значение -8124924.....
		for (int i = 0; i < 12; i++) {
			bool hasSwamp = false;
			for (int j = 0; j < 12; j++) {
				if (agents[k][j] > agents[k][j + 1]) {
					int temp = agents[k][j];
					agents[k][j] = agents[k][j + 1];
					agents[k][j + 1] = temp;
					hasSwamp = true;
				}
			}
			if (!hasSwamp) break;
		}
	}
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%5d ", agents[i][j]);
		}
		cout << endl;
	}*/
	int mediana[N] = {};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 12; j++) {
			if (agents[i][j] > -1) {
				if (j % 2 == 0) {
					mediana[i] = (agents[i][j - 1 + (12 - j) / 2] + agents[i][j + (12 - j) / 2]) / 2;
				}
				else mediana[i] = agents[i][j + (12 - j) / 2];
				break;
			}
			
		}
	}
	cout << "Вывод медианных значений з/п агентов: " << endl;
	for (int i = 0; i < N; i++) {
		cout << "агент №" << i+1 << ": " << mediana[i] << endl;
	}
}
