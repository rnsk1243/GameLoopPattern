#include "ListEntity.h"
#include<iostream>
using namespace std;

CQueueNo* CEntity::queueKey = new CQueueNo();
CQueueNo* CEntity::seveKey = new CQueueNo();

CListEntity::CListEntity()
{
}


CListEntity::~CListEntity()
{
}

node* CListEntity::addEnt(node* T, CEntity* ent)
{
	// seveKeyť�� Ʈ���� �������ִ� ��� key�� ���� �� �ֵ��� postOrder�޼ҵ� ȣ����.
	postOrder(T);
	//cout << "seveKey->getCount() = " << CEntity::seveKey->getCount() << endl;
	// seveKey�� ��� Ű��� ���� �������� Ű�� �� 
	for (int i = 0; i <= CEntity::seveKey->getCount();/*Ʈ���� ��� Ű ����*/ i++)
	{
		//cout << "seveKey->dequeue() = " << CEntity::seveKey->dequeue() << "ent->getNo() = " << ent->getNo() << endl;
		if (CEntity::seveKey->dequeue() == ent->getNo())
		{
			cout << "�ߺ��Ǵ� Ű�� �����Ͽ� Ʈ���� ���� ���Ͽ����ϴ�." << endl;
			return nullptr;
		}
	}
	
	

	if (T == NULL)
	{
		cout << ent->getNo() << "�� ��ȯ" << endl;
		T = new node;
		//cout << "addEnt�� T�� �ּ� : " << T << endl;
		T->entity = ent;
		T->Lchild = NULL;
		T->Rchild = NULL;
	}
	else if (T->entity->getNo() > ent->getNo())
	{
		cout << ent->getNo() << "�������� ����" << endl;
		T->Lchild = addEnt(T->Lchild, ent);
	}
	else {
		cout << ent->getNo() << "���������� ����" << endl;
		T->Rchild = addEnt(T->Rchild, ent);
	}
	// T = new node; �ؼ� ���θ��� ����� �ּҸ� �ѱ��.
	// ������ add�Ҷ��� �� ���ο� �ּҸ� �־ ó���� NULL if���� �ǳ� �� �� �ִ�.(root�� NULL�� �ƴϰ� �ǹǷ�) 
	return T;
}

void CListEntity::delEnt(node* &T, CEntity* ent)
{

	if (T == NULL)
	{
		cout << "������ ��尡 ����" << endl;
		return;
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
		// ��ȣ�� �����ϱ� ���� ����� ��ü�� key�� ť�� ���� �մϴ�.
		CEntity::queueKey->enqueue(T->entity->getNo());
		cout << "������ ���� " << T->entity->getNo() << " �� ����!" << endl;
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
	if (T != NULL)
	{
		//cout << "entity�� �ּ� = " << T->entity << endl;
		//cout << "Ȱ��ȭ�� ��ȣ = //// " << T->entity->getNo() << " ////" << endl;
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
		CEntity::seveKey->enqueue(T->entity->getNo());
		//T->entity->update();
	}
}

void CListEntity::successorCopy(node* &T, CEntity& ent)
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
