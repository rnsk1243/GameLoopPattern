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
	// seveKey큐가 트리에 가지고있는 모든 key를 담을 수 있도록 postOrder메소드 호출함.
	postOrder(T);
	//cout << "seveKey->getCount() = " << CEntity::seveKey->getCount() << endl;
	// seveKey에 담긴 키들과 지금 넣으려는 키와 비교 
	for (int i = 0; i <= CEntity::seveKey->getCount();/*트리에 담긴 키 갯수*/ i++)
	{
		//cout << "seveKey->dequeue() = " << CEntity::seveKey->dequeue() << "ent->getNo() = " << ent->getNo() << endl;
		if (CEntity::seveKey->dequeue() == ent->getNo())
		{
			cout << "중복되는 키가 존재하여 트리에 담지 못하였습니다." << endl;
			return nullptr;
		}
	}
	
	

	if (T == NULL)
	{
		cout << ent->getNo() << "번 소환" << endl;
		T = new node;
		//cout << "addEnt속 T의 주소 : " << T << endl;
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

void CListEntity::delEnt(node* &T, CEntity* ent)
{

	if (T == NULL)
	{
		cout << "삭제할 노드가 없다" << endl;
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
		// 번호를 재사용하기 위해 삭재된 객체의 key는 큐에 저장 합니다.
		CEntity::queueKey->enqueue(T->entity->getNo());
		cout << "재사용을 위해 " << T->entity->getNo() << " 번 저장!" << endl;
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
		//cout << "entity의 주소 = " << T->entity << endl;
		//cout << "활성화된 번호 = //// " << T->entity->getNo() << " ////" << endl;
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
