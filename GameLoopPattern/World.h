#pragma once
#include"Entity.h"
#include"ListEntity.h"
#include<iostream>
using namespace std;


class CWorld
{
	CListEntity* m_entTree;
public:
	CWorld();
	~CWorld();
	void gameLoop(node* root);
	node* addEnt(node* T, CEntity* ent)
	{
		cout << "Tree의 주소 = " << m_entTree << endl;
		cout << "T의 주소 : " << T << endl;
		return m_entTree->addEnt(T, ent);
	}
	void removeEnt(node* T, CEntity* ent)
	{
		m_entTree->delEnt(T, ent);
	}

};

