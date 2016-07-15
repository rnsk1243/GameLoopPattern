#pragma once
#include"World.h"
#include"Skeleton.h"
#include"Statue.h"

class CDoubleBuffer
{
	CSkeleton* skel;
	CSkeleton* skel1;
	CStatue* statue;
	node* m_currentRoot; // node�� �ʱ�ȭ ��Ű�� �ʰ� nullptr�� �����ؾ��Ѵ�. tree�� ������ tree �ȿ��� �ʱ�ȭ ���ش�.
	node* m_nextRoot;//���� �ʱ�ȭ ���صڿ� Ʈ���� �������� �ϸ� 
	//postOrder�޼ҵ忡�� T�� null�� �ƴ϶� �׳� ���������� �ʰ� Entity�� getNo()�޼ҵ尡 null(Entity�� nullptr��)�̶�� ������ �翬��
	// node�� �ʱ�ȭ(�޸��Ҵ�) ������ node���� ������Ƽ(Entity*��)�� �ʱ�ȭ �������ʾұ⶧����. 
	CWorld* m_currentMyGame;
	CWorld* m_nextMyGame;

	CWorld world0;
	CWorld world1;
	// ��ü �޼ҵ�� ���⿡���� ȣ�� �ϵ��� private�� ����
	void swap()
	{
		cout << "��ü" << endl;

		node* tempRoot = m_currentRoot;
		CWorld* tempWorld = m_currentMyGame;
		m_currentRoot = m_nextRoot;
		m_currentMyGame = m_nextMyGame;
		m_nextRoot = tempRoot;
		m_nextMyGame = tempWorld;
	}
public:

	CDoubleBuffer() : m_currentMyGame(&world0), m_nextMyGame(&world1)
	{
		// ����� ���� �߰�(�غ�ܰ�)
		skel = new CSkeleton(); // 0��
		skel1 = new CSkeleton(); // 1��
		statue = new CStatue(5); // 2��
	}

	~CDoubleBuffer()
	{
	}
	// ���� �߰�/���� �޼ҵ�(�غ��Ѱ��� ��ġ��)�߰��ϸ� �ǻ��/ �����ϸ� ������� ����.
	void callEntity()
	{
		// root�� null�̹Ƿ� �ʱ�ȭ ���� �־�� �Ѵ�. �̷��� ���� ������ ��� null���°� �Ǿ� ���� ������ ���� �ʴ´�.
		m_nextRoot = m_nextMyGame->addEnt(m_nextRoot, skel); // ����00 �߰�
		m_nextMyGame->addEnt(m_nextRoot, statue); // ���� �߰�
		m_nextMyGame->removeEnt(m_nextRoot, skel); // ����00 ����
		m_nextMyGame->addEnt(m_nextRoot, skel); // ����00 �ٽ� �߰�
		m_nextMyGame->addEnt(m_nextRoot, skel1); // ����01 �߰�
		m_nextMyGame->removeEnt(m_nextRoot, skel1); // ����01 ����
		m_nextMyGame->addEnt(m_nextRoot, skel1); // ����01 �ٽ� �߰�
		// ����, ����00, ����01 

		// ��� �߰������� ���� ��ü
		swap();
	}

	void gameLoop()
	{
		// ������ ���� ������ ���� CWorld�� ����
		m_currentMyGame->gameLoop(m_currentRoot);
		//m_nextMyGame->gameLoop(m_nextRoot);
	}
};

