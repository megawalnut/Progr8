#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define Max_Size_Q 1000

// Функции добавления элемента, удаления
void spstore(int x);

char find_el[256];
struct node *get_struct(int x); // функция создания элемента

struct node *head = NULL, *last = NULL, *f = NULL; // указатели на первый и последний элементы списка

struct node
{
	int vertex; // номер вершины
	struct node *next; // ссылка на следующий элемент 
};


struct node *get_struct(int x)
{
	struct node *p = NULL;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	p->vertex = x;

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(int x)
{
	struct node *p = NULL;
	p = get_struct(x);
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}


void find_och(int x, int** k, int m, int* D)
{
	spstore(x);
	D[x - 1] = 1;

	while (x != 0)
	{
		struct node *struc = head;
		if (head == NULL)
		{
			printf("Список пуст\n");
		}
		for(int i = 0; i < m; i++)
		{
			if (k[x - 1][i] == 1 && D[i] == 0)
			{
				spstore(i + 1);
				D[i] = 1;
			}
		}

		if (head == NULL) // если голова списка равна NULL, то список пуст
		{
			printf("Список пуст\n");
			return;
		}
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
		
		if(struc != 0)
			x = struc->vertex;
		else
			x = 0;
	}
}

void find_Q(int x, int** k, int m, int* D)
{
	int Q[Max_Size_Q] = { 0 };
	int n = 0;
	int j = 0;
	Q[j] = x;
	D[x - 1] = 1;

	while (x != 0)
	{
		for(int i = 0; i < m; i++)
		{
			if (k[x - 1][i] == 1 && D[i] == 0)
			{
				n++;
				Q[n] = i + 1;
				D[i] = 1;
			}
		}
		j++;
		x = Q[j];
	}
}

int main () 
{
	setlocale(LC_ALL, "rus");

	clock_t start, end; // объявляем переменные для определения времени выполнения
	int m;
	int l = 0;
	int x; // Вершина

	srand(time(NULL));

	printf("Введите размер матрицы\n");
	scanf("%d", &m);

	int** k = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++)
	{
		k[i] = (int*)malloc(m * sizeof(int));
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{	
			k[i][j] = 0;
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int t = rand() % 2;
			k[i][j] = t;
			k[j][i] = t;
			k[i][i] = 0;
		}

	}

	//_____________________________________________

	int* D = (int*)malloc(m * sizeof(int));

	for (int i = 0; i < m; i++)
	{
		D[i] = 0;	//Массив вершин
	}

	printf("Введите номер вершины - ");
	scanf("%d", &l);
	while (l <= 0 || l > m)
	{
		printf("Введите номер вершины еще раз - ");
		scanf("%d", &l);
	}
	x = l;

	start = clock(); // в переменную start записываем время от начала запуска программы

	find_och(x, k, m, D);

	end = clock(); // в переменную end записываем время от начала запуска программы
	double time = (end - start) * 1000.0 / CLOCKS_PER_SEC; // вычисляем разность(т.е. время, затраченное на умножение матриц)

	printf("%lf ms\n", time); // выводим результат работы программы в секундах

	//_____________________________________________

	for (int i = 0; i < m; i++)
	{
		D[i] = 0;	//Массив вершин
	}

	x = l;

	start = clock(); // в переменную start записываем время от начала запуска программы

	find_och(x, k, m, D);

	end = clock(); // в переменную end записываем время от начала запуска программы
	time = (end - start) * 1000.0 / CLOCKS_PER_SEC; // вычисляем разность(т.е. время, затраченное на умножение матриц)

	printf("%lf ms\n", time); // выводим результат работы программы в секундах
	
	free(D);
	//_____________________________________________

	
	getchar();getchar();
	return 0;
}