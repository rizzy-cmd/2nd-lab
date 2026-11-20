#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono> 
#include <limits> // для отлова ошибок ввода

using namespace std;
using namespace std::chrono;

const int n = 100;
int m[100];

// защита от ввода букв вместо чисел
int getInt() {
	int num;
	while (!(cin >> num)) {
		cin.clear(); // сбрасываем ошибку
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // чистим буфер
		cout << "Ошибка! Введите число: ";
	}
	return num;
}

// заполняем массив
void mas() {
	string s;
	cout << "Выберите способ задания массива:\n" << "Ввести свой через пробел(Введите 1)\n" << "Сгенерировать случайный(Введите 2)" << endl;
	cin >> s;
	if (s == "1") {
		cout << "Вставьте массив:\n";
		for (int i = 0; i < 100; i++) {
			m[i] = getInt();
		}
	}
	else if (s == "2") {
		mt19937 gen(random_device{}());
		uniform_int_distribution<> d(-99, 99);
		for (int i = 0; i < 100; i++) {
			m[i] = d(gen);
		}
	}
}

// сортировка пузырьком
void bubble_sort(int m[]) {
	for (int i = 0; i <= n - 2; i++) {
		bool flag = false;
		for (int j = 0; j < n - 1 - i; j++) {
			if (m[j] > m[j + 1]) {
				swap(m[j], m[j + 1]);
				flag = true;
			}
		}
		if (!flag) break;
	}
}

// сортировка вставками
void insertion_sort(int m[]) {
	for (int i = 1; i <= n - 1; i++) {
		int j = i - 1;
		int key = m[i];
		while (j >= 0 && m[j] > key) {
			m[j + 1] = m[j];
			j = j - 1;
		}
		m[j + 1] = key;
	}
}

// сортировка выбором
void selection_sort(int m[]) {
	for (int i = 0; i < n - 1; i++) {
		int minindex = i;
		for (int j = i + 1; j < n; j++) {
			if (m[j] < m[minindex]) {
				minindex = j;
			}
		}
		if (minindex != i) {
			swap(m[i], m[minindex]);
		}
	}
}

// шейкерная сортировка
void shaker_sort(int m[]) {
	int left = 0;
	int right = n - 1;
	int lastswap = left;
	while (left < right) {
		for (int i = left; i <= right - 1; i++) {
			if (m[i] > m[i + 1]) {
				swap(m[i + 1], m[i]);
				lastswap = i + 1;
			}
		}
		right = lastswap;
		for (int i = right; i >= left + 1; i--) {
			if (m[i - 1] > m[i]) {
				swap(m[i], m[i - 1]);
				lastswap = i;
			}
		}
		left = lastswap;
	}
}

// разделение для быстрой сортировки
int partition(int m[], int low, int high) {
	int pivot = m[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (m[j] < pivot) {
			i++;
			swap(m[i], m[j]);
		}
	}
	swap(m[i + 1], m[high]);
	return (i + 1);
}

// быстрая сортировка
void quickSort(int m[], int low, int high) {
	if (low < high) {
		int pi = partition(m, low, high);
		quickSort(m, low, pi - 1);
		quickSort(m, pi + 1, high);
	}
}

// вывод массива по 20 чисел
void printArray(int m[], int size) {
	for (int i = 0; i < size; i++) {
		cout << m[i] << " ";
		if ((i + 1) % 20 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

// ищем максимум перебором
int maxel(int m[]) {
	int maxl = m[0];
	for (int i = 1; i < n; i++) {
		if (m[i] > maxl) maxl = m[i];
	}
	return maxl;
}

// ищем минимум перебором
int minel(int m[]) {
	int minl = m[0];
	for (int i = 1; i < n; i++) {
		if (m[i] < minl) minl = m[i];
	}
	return minl;
}

// в отсортированном массиве максимум в конце
int maxelsort(int m[]) { return m[n - 1]; }
// в отсортированном массиве минимум в начале
int minelsort(int m[]) { return m[0]; }

// среднее значение min и max + индексы
void sr_znach(int m[]) {
	quickSort(m, 0, n - 1);
	int maxl = maxelsort(m);
	int minl = minelsort(m);
	int sr = (int)round((maxl + minl) / 2.0);
	int k = 0;
	bool flag = false;

	cout << "Среднее значение: " << sr << endl;

	// засекаем время
	auto start = steady_clock::now();

	cout << "Индексы: ";
	for (int i = 0; i < n; i++) {
		if (m[i] == sr) {
			flag = true;
			cout << i << " ";
			k++;
		}
	}
	cout << endl;

	auto end = steady_clock::now();
	auto time_us = duration_cast<microseconds>(end - start).count();

	if (!flag) {
		cout << "Элементы отсутствуют" << endl;
	}
	else {
		cout << "Количество: " << k << endl;
	}
	cout << "Время поиска: " << time_us << " мкс" << endl;
}

// сколько больше b (в отсортированном)
int coutmore(int m[], int b) {
	for (int i = 0; i < n; i++) {
		if (m[i] > b) return (n - i);
	}
	return 0;
}

// сколько меньше a (в отсортированном)
int coutless(int m[], int a) {
	for (int i = n - 1; i >= 0; i--) {
		if (m[i] < a) return (i + 1);
	}
	return 0;
}

// линейный поиск
int linearsearch(int m[], int a) {
	for (int i = 0; i < n; i++) {
		if (m[i] == a) return i;
	}
	return -1;
}

// бинарный поиск
int binarysearch(int m[], int a) {
	int left = 0;
	int right = n - 1;
	while (left <= right) {
		int med = left + (right - left) / 2;
		if (m[med] == a) return med;
		else if (a < m[med]) right = med - 1;
		else left = med + 1;
	}
	return -1;
}

// меняем элементы
void swapel(int m[], int a, int b) {
	swap(m[a], m[b]);
}

// инд задание: макс возрастающая последовательность
void maxdlina(int m[]) {
	int maxk = 1;
	int k = 1;
	int lastIndex = 0;

	for (int i = 0; i < n - 1; i++) {
		if (m[i] < m[i + 1]) {
			k++;
			if (k > maxk) {
				maxk = k;
				lastIndex = i + 1;
			}
		}
		else {
			k = 1;
		}
	}

	cout << "Макс. длина: " << maxk << endl;
	cout << "Последовательность: ";
	for (int i = lastIndex - maxk + 1; i <= lastIndex; i++) {
		cout << m[i] << " ";
	}
	cout << endl;
}

// сравнение всех сортировок
void compareSorts() {
	int temp[100];
	cout << "\n--- Сравнение сортировок (время в микросекундах) ---\n";

	// пузырек
	std::copy(m, m + n, temp);
	auto start = steady_clock::now();
	bubble_sort(temp);
	auto end = steady_clock::now();
	cout << "Bubble sort:    " << duration_cast<microseconds>(end - start).count() << " мкс\n";

	// вставками
	std::copy(m, m + n, temp);
	start = steady_clock::now();
	insertion_sort(temp);
	end = steady_clock::now();
	cout << "Insertion sort: " << duration_cast<microseconds>(end - start).count() << " мкс\n";

	// выбором
	std::copy(m, m + n, temp);
	start = steady_clock::now();
	selection_sort(temp);
	end = steady_clock::now();
	cout << "Selection sort: " << duration_cast<microseconds>(end - start).count() << " мкс\n";

	// шейкером
	std::copy(m, m + n, temp);
	start = steady_clock::now();
	shaker_sort(temp);
	end = steady_clock::now();
	cout << "Shaker sort:    " << duration_cast<microseconds>(end - start).count() << " мкс\n";

	// быстрая
	std::copy(m, m + n, temp);
	start = steady_clock::now();
	quickSort(temp, 0, n - 1);
	end = steady_clock::now();
	cout << "Quick sort:     " << duration_cast<microseconds>(end - start).count() << " мкс\n";
}

int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int choice;
	bool isSorted = false;

	while (true) {
		cout << "\n======================================\n";
		cout << "1. Создать массив (случайный или вручную)\n";
		cout << "2. Сортировка пузырьком (Bubble)\n";
		cout << "3. Сортировка вставками (Insertion)\n";
		cout << "4. Сортировка выбором (Selection)\n";
		cout << "5. Шейкерная сортировка (Shaker)\n";
		cout << "6. Быстрая сортировка (Quick)\n";
		cout << "7. Найти Max и Min + время поиска\n";
		cout << "8. Найти среднее Min/Max + индексы + время\n";
		cout << "9. Кол-во элементов < a\n";
		cout << "10. Кол-во элементов > b\n";
		cout << "11. Бинарный поиск vs Линейный поиск\n";
		cout << "12. Обмен двух элементов по индексам + время\n";
		cout << "13. Инд. задание: Макс. возрастающая последовательность\n";
		cout << "14. Сравнить все сортировки по времени\n";
		cout << "0. Выход\n";
		cout << "======================================\n";
		cout << "Выберите пункт: ";

		choice = getInt(); // защищенный ввод

		if (choice == 0) {
			cout << "Выход из программы. До встречи!\n";
			break;
		}

		switch (choice) {
		case 1:
			mas();
			printArray(m, n);
			isSorted = false;
			break;

		case 2: {
			auto start = steady_clock::now();
			bubble_sort(m);
			auto end = steady_clock::now();
			printArray(m, n);
			if (duration_cast<microseconds>(end - start).count() > 0) {
				cout << "Время сортировки: " << duration_cast<microseconds>(end - start).count() << " мкс\n";
			}
			else {
				cout << "Время сортировки: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
			}
			isSorted = true;
			break;
		}
		case 3: {
			auto start = steady_clock::now();
			insertion_sort(m);
			auto end = steady_clock::now();
			printArray(m, n);
			if (duration_cast<microseconds>(end - start).count() > 0) {
				cout << "Время сортировки: " << duration_cast<microseconds>(end - start).count() << " мкс\n";
			}
			else {
				cout << "Время сортировки: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
			}
			isSorted = true;
			break;
		}
		case 4: {
			auto start = steady_clock::now();
			selection_sort(m);
			auto end = steady_clock::now();
			printArray(m, n);
			if (duration_cast<microseconds>(end - start).count() > 0) {
				cout << "Время сортировки: " << duration_cast<microseconds>(end - start).count() << " мкс\n";
			}
			else {
				cout << "Время сортировки: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
			}
			isSorted = true;
			break;
		}
		case 5: {
			auto start = steady_clock::now();
			shaker_sort(m);
			auto end = steady_clock::now();
			printArray(m, n);
			if (duration_cast<microseconds>(end - start).count() > 0) {
				cout << "Время сортировки: " << duration_cast<microseconds>(end - start).count() << " мкс\n";
			}
			else {
				cout << "Время сортировки: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
			}
			isSorted = true;
			break;
		}
		case 6: {
			auto start = steady_clock::now();
			quickSort(m, 0, n - 1);
			auto end = steady_clock::now();
			printArray(m, n);
			if (duration_cast<microseconds>(end - start).count() > 0) {
				cout << "Время сортировки: " << duration_cast<microseconds>(end - start).count() << " мкс\n";
			}
			else {
				cout << "Время сортировки: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
			}
			isSorted = true;
			break;
		}

		case 7: {
			cout << "\n-- Неотсортированный массив --\n";
			auto start = steady_clock::now();
			int mx = maxel(m);
			int mn = minel(m);
			auto end = steady_clock::now();
			cout << "Max: " << mx << ", Min: " << mn << "\n";
			cout << "Время поиска: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";

			quickSort(m, 0, n - 1);

			cout << "\n-- Отсортированный массив --\n";
			start = steady_clock::now();
			int mx_s = maxelsort(m);
			int mn_s = minelsort(m);
			end = steady_clock::now();
			cout << "Max: " << mx_s << ", Min: " << mn_s << "\n";
			cout << "Время поиска: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
			break;
		}

		case 8:
			sr_znach(m);
			isSorted = true;
			break;

		case 9: {
			int a;
			cout << "Введите число a: ";
			a = getInt();
			cout << "Элементов меньше " << a << ": " << coutless(m, a) << "\n";
			break;
		}
		case 10: {
			int b;
			cout << "Введите число b: ";
			b = getInt();
			cout << "Элементов больше " << b << ": " << coutmore(m, b) << "\n";
			break;
		}

		case 11: {
			int x;
			cout << "Введите число для поиска: ";
			x = getInt();

			auto start = steady_clock::now();
			int resLin = linearsearch(m, x);
			auto end = steady_clock::now();
			auto timeLin = duration_cast<nanoseconds>(end - start).count();

			start = steady_clock::now();
			int resBin = binarysearch(m, x);
			end = steady_clock::now();
			auto timeBin = duration_cast<nanoseconds>(end - start).count();

			cout << "\n-- Результаты поиска --\n";
			cout << "Линейный: ";
			if (resLin != -1) cout << "найдено на индексе " << resLin; else cout << "не найдено";
			cout << " (" << timeLin << " нс)\n";

			cout << "Бинарный: ";
			if (resBin != -1) cout << "найдено на индексе " << resBin; else cout << "не найдено";
			cout << " (" << timeBin << " нс)\n";

			if (timeLin > 0) {
				cout << "Бинарный быстрее в " << (double)timeLin / (timeBin > 0 ? timeBin : 1) << " раз(а).\n";
			}
			break;
		}

		case 12: {
			int idx1, idx2;
			cout << "Введите два индекса (0-99): ";
			idx1 = getInt();
			idx2 = getInt();

			if (idx1 >= 0 && idx1 < n && idx2 >= 0 && idx2 < n) {
				auto start = steady_clock::now();
				swapel(m, idx1, idx2);
				auto end = steady_clock::now();
				cout << "Обмен выполнен.\n";
				cout << "Время обмена: " << duration_cast<nanoseconds>(end - start).count() << " нс\n";
				printArray(m, n);
			}
			else cout << "Ошибка: индексы вне диапазона!\n";
			break;
		}

		case 13:
			maxdlina(m);
			break;

		case 14:
			compareSorts();
			break;

		default:
			cout << "Нет такого пункта!\n";
		}
	}
	return 0;
}