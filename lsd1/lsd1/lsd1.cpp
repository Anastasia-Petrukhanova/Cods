#include <iostream>
#include <time.h>
#include <cmath>

struct Node
{
	unsigned short int *val;
	Node* next;
};

struct List
{
	Node* first;
	Node* last;
};

List* Merge(List* bac, int M, int&cnt)
{
	List a;
	a.first = NULL;
	for (int i = 0; i < M; ++i)
	{
		if (bac[i].first != NULL)
		{
			if (a.first == NULL)
			{
				a = bac[i];
				++cnt;
			}
			else
			{
				a.last->next = bac[i].first;
				a.last = bac[i].last;
				cnt += 2;
			}
			bac[i].last = NULL;
			bac[i].first = NULL;
			cnt += 2;
		}
	}
	return &a;
}

int main()
{
	short int A[] = { 2, 8, 10, 16 };
	short int B[] = { 10000, 50000, 100000 };
	srand((unsigned int)time(NULL));
	for (int N1 = 0; N1 < 3; ++N1)
	{
		for (int p1 = 1; p1 <= 10; ++p1)
		{
			for (int f = 0; f < 4; ++f)
			{
				int cnt_sum = 0;
				/*int N, p, M;
				std::cin >> N >> p >> M;*/ // для ввода данных вручную
				int M = A[2];
				int p = p1 * 100;
				int N = B[N1];
				long t_sum = 0;
				for (int g = 0; g < 5; ++g)
				{
					int cnt = 0;
					List P;
					Node a;
					a.val = new unsigned short int[p];
					for (int i = 0; i < p; ++i)
					{
						a.val[i] = rand() % (M);
					}
					P.first = &a;
					Node* pa = &a;
					for (int i = 1; i < N; ++i)
					{
						Node* b = new Node;
						b->val = new short unsigned int[p];
						for (int i = 0; i < p; ++i)
						{
							b->val[i] = rand() % (M);
						}
						pa->next = b;
						pa = pa->next;
					}
					P.last = pa;
					P.last->next = NULL;
					long t = clock();
					pa = P.first;

					List* bac = new List[M]; //cоздание контейнеров
					for (int j = 0; j < M; ++j)
					{
						bac[j].first = NULL;
						bac[j].last = NULL;
						cnt += 2;
					}
					for (int i = p - 1; i >= 0; --i)
					{
						while (pa)
						{
							if (bac[pa->val[i]].first == NULL)
							{
								bac[pa->val[i]].first = pa;
								P.first = pa->next;
								bac[pa->val[i]].first->next = NULL;
								bac[pa->val[i]].last = pa;
								bac[pa->val[i]].last->next = NULL;
								cnt += 5;
							}
							else
							{
								bac[pa->val[i]].last->next = pa;
								bac[pa->val[i]].last = pa;
								P.first = pa->next;
								bac[pa->val[i]].last->next = NULL;
								cnt += 4;
							}
							pa = P.first;
							++cnt;
						}
						P = *Merge(bac, M, cnt);
						pa = P.first;
						cnt += 2;
					}
					t = clock() - t;
					t_sum += (float)t / CLOCKS_PER_SEC * 1000000;
					cnt_sum += cnt;
					//можно использовать для вывода результата
					//Node* head = P.first;
					/*while (head)
					{
						std::cout << "[ ";
						for (int i = 0; i < p; ++i)
						{
							std::cout << head->val[i] << " ";
						}
						std::cout << "]" << std::endl;
						head = head->next;
					}*/

					delete[] bac;
					Node* head = &a;
					while (head)
					{
						delete[] head->val;
						Node* d = head;
						head = head->next;
						d = NULL;
					}
					P.first = NULL;
					P.last = NULL;
				}
				std::cout << t_sum / 5 << std::endl; // микросекунды (среднее)
				std::cout << cnt_sum/5 << std::endl;
			}
		}
	}
	return 0;
}