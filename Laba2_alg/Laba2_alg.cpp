#include <iostream>
#include <fstream>
#include <clocale>
using namespace std;

struct Elem
{
	int data;
	Elem *next, *prev;
};

Elem* Head = NULL, * Tail = NULL;
int DelAll(int);
int DelTail(int);
int AddTail(int, int);
void Print(int);
void PrintToFile(int);
void Search(int, int*, int);

int main()
{
	setlocale(LC_ALL, "russian");
	ifstream f("input.txt");
	int e, n=-1, Count = 0, a[20] = { 0 };
	while (n != 0) {
		cout << "1: Создать список;" << endl
			 << "2: Вывести список;" << endl
			 << "3: Удалить последний элемент;" << endl
			 << "4: Добавить элемент в конец;" << endl
			 << "5: Поиск элемента(ов);" << endl
			 << "6: Очистка списка;" << endl
			 << "0: Выход;" <<endl
			 << "Введите номер операции: ";
		cin >> n;
		switch (n)
		{
		case 1:
			while (!f.eof())						//Создание
			{
				f >> e;
				Count = AddTail(e, Count);
			}
			f.close();
			Print(Count);
			PrintToFile(Count);
			break;
		case 2:
			Print(Count);							//Печать
			PrintToFile(Count);
			break;
		case 3:
			Count = DelTail(Count);					//Удаление конца
			Print(Count);
			PrintToFile(Count);
			break;
		case 4:
			cout << "Введите элемент, который нужно добавить: "; //Запись в конец
			cin >> n;
			Count = AddTail(n, Count);
			Print(Count);
			PrintToFile(Count);
			break;
		case 5:
			Print(Count);						//Поиск
			PrintToFile(Count);
			cout << "Введите элемент, который нужно найти: ";
			cin >> e;
			Search(e, a, Count);
			if (a[0] != 0)
			{
				cout << "Ключ "<<e<<" найден на ";
				for (int i = 0; i < Count; i++)
				{
					if (a[i] != 0)
						cout << a[i] << " ";
				}
				cout << "индексе\n\n";
			}
			else cout << "Ключ не найден!!!\n\n";
			break;
		case 6:
			Count = DelAll(Count);				//Очистка списка
			Print(Count);
			PrintToFile(Count);
			break;
		case 0: break;
		default:
			cout << endl << "Вы ввели неверное значение" << endl << endl; break;
		}

	}
	system("pause");
	return 0;
}

int AddTail(int n, int Count)
{
	Elem* temp = new Elem;
	temp->next = Head;
	temp->data = n;
	temp->prev = Tail;
	if (Tail != NULL)
	{
		Tail->next = temp;
		Head->prev = temp;
	}
	if (Count == 0)
		Head = Tail = temp;
	else
		Tail = temp;
	Count++;
	return Count;
}

int DelTail(int Count)
{
	if (Tail != NULL) {
		Elem* Del = Tail;
		Elem* PrevDel = Del->prev;
		Elem* AfterDel = Del->next;

		PrevDel->next = AfterDel;
		Tail = PrevDel;

		delete Del;
		Count--;
	}
	return Count;
}

void Print(int Count)
{
	int i = 0;
	if (Count != 0 && Head!=NULL)
	{
		cout << "\nСписок:\n";
		Elem* temp = Head;
		while (temp->next!=Head)
		{
			cout << i << ": " << temp->data << endl;;
			temp = temp->next;
			i++;
		}
		cout <<i<<": "<<temp->data << endl << endl;
	}
	else cout << "\nСписок пустой!!\n\n";
}

int DelAll(int Count)
{
	Elem  *Del, *PrevDel, *AfterDel;
	while (Count != 0) 
	{
		Del = Head;
		PrevDel = Del->prev;
		AfterDel = Del->next;

		if (AfterDel != 0 && Count != 1)
			AfterDel->prev = PrevDel;

		Head = AfterDel;
		delete Del;
		Count--;
	}
	return Count;
}

void PrintToFile(int Count)
{
	ofstream f("output.txt");
	int i = 0;
	Elem* temp = Head;
	if (Head != NULL)
	{
		while (i!=Count)
		{
			f << i << ": " << temp->data << endl;;
			temp = temp->next;
			i++;
		}
		f << i << ": " << temp->data << endl << endl;
	}
	else f << "Список пустой!!!";
}

void Search(int Key, int* a,int Count)
{
	int i = 0, j = 0;
	if (Head != NULL) {
		Elem* temp = Head;
		while (i != Count)
		{
			if (temp->data == Key)
			{
				a[j] = i;
				j++;
			}
			i++;
			temp = temp->next;
		}
	}
}