#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define Max_Size_Q 1000

// ������� ���������� ��������, ��������
void spstore(int x);

char find_el[256];
struct node *get_struct(int x); // ������� �������� ��������

struct node *head = NULL, *last = NULL, *f = NULL; // ��������� �� ������ � ��������� �������� ������

struct node
{
	int vertex; // ����� �������
	struct node *next; // ������ �� ��������� ������� 
};


struct node *get_struct(int x)
{
	struct node *p = NULL;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	p->vertex = x;

	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

/* ���������������� ���������� � ������ �������� (� �����)*/
void spstore(int x)
{
	struct node *p = NULL;
	p = get_struct(x);
	if (head == NULL && p != NULL)	// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // ������ ��� ����, �� ��������� � �����
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
			printf("������ ����\n");
		}
		for(int i = 0; i < m; i++)
		{
			if (k[x - 1][i] == 1 && D[i] == 0)
			{
				spstore(i + 1);
				D[i] = 1;
			}
		}

		if (head == NULL) // ���� ������ ������ ����� NULL, �� ������ ����
		{
			printf("������ ����\n");
			return;
		}
		head = struc->next; // ������������� ������ �� ��������� �������
		free(struc);  // ������� ������ �������
		struc = head; // ������������� ��������� ��� ����������� ������
		
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

	clock_t start, end; // ��������� ���������� ��� ����������� ������� ����������
	int m;
	int l = 0;
	int x; // �������

	srand(time(NULL));

	printf("������� ������ �������\n");
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
		D[i] = 0;	//������ ������
	}

	printf("������� ����� ������� - ");
	scanf("%d", &l);
	while (l <= 0 || l > m)
	{
		printf("������� ����� ������� ��� ��� - ");
		scanf("%d", &l);
	}
	x = l;

	start = clock(); // � ���������� start ���������� ����� �� ������ ������� ���������

	find_och(x, k, m, D);

	end = clock(); // � ���������� end ���������� ����� �� ������ ������� ���������
	double time = (end - start) * 1000.0 / CLOCKS_PER_SEC; // ��������� ��������(�.�. �����, ����������� �� ��������� ������)

	printf("%lf ms\n", time); // ������� ��������� ������ ��������� � ��������

	//_____________________________________________

	for (int i = 0; i < m; i++)
	{
		D[i] = 0;	//������ ������
	}

	x = l;

	start = clock(); // � ���������� start ���������� ����� �� ������ ������� ���������

	find_och(x, k, m, D);

	end = clock(); // � ���������� end ���������� ����� �� ������ ������� ���������
	time = (end - start) * 1000.0 / CLOCKS_PER_SEC; // ��������� ��������(�.�. �����, ����������� �� ��������� ������)

	printf("%lf ms\n", time); // ������� ��������� ������ ��������� � ��������
	
	free(D);
	//_____________________________________________

	
	getchar();getchar();
	return 0;
}