#include <iostream>

using namespace std;

/*!
 * Функция инициализации массива
 */
void create(char* array, int size);

/*!
 * Функция ввывода массива на экран
 */
void print(char* array, int size);

/*!
 * Функция вычисления среднего арифметического элементов массива
 */
double getAverage(char* array, int size);

/*!
 * Функция вывода среднего арифметического элементов массива на экран
 */
void print_result(char* array, int size);

int main()
{
	setlocale(0, "");
	int size = 1;
	char* array;
	cout << "Введите размер масива : ";
	cin >> size;
	if (size < 1)
	{
		cout << "Размер масива доджен быть больше 1!\n";
		cout << "Размер масива изменен на 2!\n";
		size = 2;
	}
	create(&array, size);
	print_result(array, size);
	system("pause");
}

void create(char* array, int size)
{
	if (size < 1) return;
	*array = new char[size];
	/*!
	* Заполнение массивва случайными данными
	*/
	for (int i = 0; i < size; ++i)
	{
		(*array)[i] = (char)rand();
	}
}

void print(char* array, int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << (int)array[i] << " ";
	}
	cout << endl;
}

double getAverage(char* array, int size)
{
	double result = 0.0;
	for (int i = 0; i < size; ++i)
	{
		result += array[i];
	}

	return result / size;
}

void print_result(char* array, int size)
{
	cout << "Массив : \n";
	print(array, size);
	cout << "Среднее арифметическое в созданном массиве : " <<
		getAverage(array, size) << endl;
}