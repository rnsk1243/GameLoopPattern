#pragma once
#include"Entity.h"

// 객체를 담는 트리
struct node
{
	CEntity* entity;
	node* Lchild;
	node* Rchild;
};

class CListEntity
{
	
public:
	CListEntity();
	~CListEntity();
	node* addEnt(node* T, CEntity* ent);
	void delEnt(node* &T, CEntity* ent);
	void preOrder(node* T);
	void inOrder(node* T);
	void postOrder(node* T);
	void successorCopy(node* &T, CEntity& ent);
};

