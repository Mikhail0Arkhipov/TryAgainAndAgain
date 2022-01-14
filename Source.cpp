#include <iostream>

using namespace std;

/*!
 * \brief Функция инициализации массива
 * \param size Размер массива
 */
void create(char* array, const int size);

/*!
 * \brief Функция ввывода массива на экран
 * \param size Размер массива
 */
void print(char* array, const int size);

/*!
 * \brief Функция вычисления среднего арифметического элементов массива
 * \param size Размер массива
 */
double getAverage(char* array, const int size);

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
	create(array, size);
	getAverage(array, size);
	system("pause");
}

void create(char* array, const int size)
{
	if (size < 1) return;
	array = new char[size];
	for (int i = 0; i < size; ++i)
	{
		array[i] = (char)rand();
	}
}

void print(char* array, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << static_cast<int>(array[i]) << " ";
	}
	cout << endl;
}

double getAverage(char* array, const int size)
{
	double result = 0.0;
	for (int i = 0; i < size; ++i)
	{
		result += array[i];
	}
	return result / size;
}