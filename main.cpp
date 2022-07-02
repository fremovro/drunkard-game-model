#include <iostream>
#include <string>
using namespace std;
//
struct Node
{
	int x;
	Node* next, *prev; 		
};
typedef Node* PNode;
//
void Add(int x, int y, PNode& Head, PNode& MyNode)
{
	PNode temp, temp_2;
	if (Head == nullptr)
	{
		Head = new(Node);
		MyNode = Head;
		Head->next = nullptr; Head->prev = nullptr;
	}
	else
	{
		temp = new(Node);
		MyNode->next = temp; MyNode = temp;
		Head->next = MyNode; 
        MyNode->prev = Head; MyNode->next = nullptr;
		Head = MyNode;
	}
	MyNode->x = y;
}
//
void b_enum(PNode &Head)
{
	while (Head->prev != nullptr) Head = Head->prev;
}
//
void f_enum(PNode& Head)
{
	if(Head!=nullptr)
		while (Head->next != nullptr) Head = Head->next;
}
//
void round(PNode& Head1, int x)
{
	PNode temp;
	temp = new(Node);
	b_enum(Head1);
	temp->next = Head1; temp->prev = nullptr;
	Head1->prev = temp; Head1 = Head1->prev; Head1->x = x;
	f_enum(Head1);
}
//
void game(PNode &Head1)
{
	PNode MyNode;
	if (Head1->next == nullptr && Head1->prev == nullptr) Head1 = nullptr;
	else
	{
		MyNode = Head1;
		Head1 = Head1->prev; Head1->next = nullptr;
		delete MyNode;
	}
}
//
int main()
{
	setlocale(LC_ALL, "Russian");
	PNode Head1, MyNode1, Head2, MyNode2; int x, y, res = 0;
	Head1 = nullptr; MyNode1 = nullptr; Head2 = nullptr; MyNode2 = nullptr;
	cout << "Введите номера карт первого игрока: ";
	for (int i = 0; i < 5; i++)
	{
		cin >> y;
		Add(i, y, Head1, MyNode1);
	}
	cout << "Введите номера карт второго игрока: ";
	for (int i = 0; i < 5; i++)
	{
		cin >> y;
		Add(i, y, Head2, MyNode2);
	}
	while (Head1!=nullptr && Head2!=nullptr)
	{
		if (res < 106)
		{
			res++;
			if ((Head1->x > Head2->x && Head2->x != 0) || (Head1->x == 0))
			{
				x = Head1->x;
				round(Head1, x); game(Head1);
				x = Head2->x;
				round(Head1, x); game(Head2);
			}
			else
			{
				x = Head1->x;
				round(Head2, x);
				x = Head2->x;
				game(Head2); round(Head2, x); game(Head1);
			}
		}
		else break;
	}
	if (res < 106)
	{
		if (Head2 == nullptr) cout << "first " << res;
		else cout << "second " << res;
	}
	else cout << "botva";
}