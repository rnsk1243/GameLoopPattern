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
		// 트리에 있는 모든 객체의 업데이트 메소드 호출
		m_entTree->preOrder(root);
		//Sleep(500);
}
