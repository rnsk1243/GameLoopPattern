#include "World.h"
#include<Windows.h>

CWorld::CWorld()
{
	m_entTree = new CListEntity();
}


CWorld::~CWorld()
{
}

void CWorld::gameLoop(node* root)
{
	while (true)
	{
		//cout << "loop" << endl;
		// Ʈ���� �ִ� ��� ��ü�� ������Ʈ �޼ҵ� ȣ��
		m_entTree->preOrder(root);
		Sleep(500);
	}
}