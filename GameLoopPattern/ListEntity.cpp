#include "ListEntity.h"
#include<iostream>
using namespace std;


CListEntity::CListEntity()
{
}


CListEntity::~CListEntity()
{
}

node* CListEntity::addEnt(node* T, CEntity* ent)
{
	if (T == NULL)
	{

		cout << ent->getNo() << "번 소환" << endl;
		T = new node;
		cout << "addEnt속 T의 주소 : " << T << endl;
		T->entity = ent;
		T->Lchild = NULL;
		T->Rchild = NULL;
	}
	else if (T->entity->getNo() > ent->getNo())
	{
		cout << ent->getNo() << "왼쪽으로 가셈" << endl;
		T->Lchild = addEnt(T->Lchild, ent);
	}
	else {
		cout << ent->getNo() << "오른쪽으로 가셈" << endl;
		T->Rchild = addEnt(T->Rchild, ent);
	}
	// T = new node; 해서 새로만든 노드의 주소를 넘긴다.
	// 다음에 add할때는 이 새로운 주소를 넣어서 처음에 NULL if문을 건너 뛸 수 있다.(root가 NULL이 아니게 되므로) 
	return T;
}

void CListEntity::delEnt(node* T, CEntity* ent)
{
	if (T == NULL)
	{
		cout << "삭제할 노드가 없다" << endl;
	}
	else if (T->entity->getNo() > ent->getNo())
	{
		delEnt(T->Lchild, ent);
	}
	else if (T->entity->getNo() < ent->getNo())
	{
		delEnt(T->Rchild, ent);
	}
	else if (T->entity->getNo() == ent->getNo())
	{
		if (T->Lchild == nullptr && T->Rchild == nullptr)
		{
			node* temp = T;
			T = NULL;
			delete temp;
		}
		else if (T->Lchild == NULL)
		{
			node* temp = T;
			T = T->Rchild;
			delete temp;
		}
		else if (T->Rchild == NULL)
		{
			node* temp = T;
			T = T->Lchild;
			delete temp;
		}
		else {
			successorCopy(T->Rchild, *ent);
		}

	}
}

void CListEntity::preOrder(node * T)
{
	if (T != nullptr)
	{
		//cout << "preOrder" << endl;
		T->entity->update();
		preOrder(T->Lchild);
		preOrder(T->Rchild);
	}
}

void CListEntity::inOrder(node * T)
{
	if (T != nullptr)
	{
		inOrder(T->Lchild);
		T->entity->update();
		inOrder(T->Rchild);
	}
}

void CListEntity::postOrder(node * T)
{
	if (T != nullptr)
	{
		postOrder(T->Lchild);
		postOrder(T->Rchild);
		T->entity->update();
	}
}

void CListEntity::successorCopy(node * T, CEntity& ent)
{
	if (T->Lchild == NULL)
	{
		ent = *T->entity;
		node* temp = T;
		T = T->Rchild;
		delete temp;
	}
	else {
		successorCopy(T->Lchild, ent);
	}
}
