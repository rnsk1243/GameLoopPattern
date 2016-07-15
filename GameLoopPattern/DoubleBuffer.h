#pragma once
#include"World.h"
#include"Skeleton.h"
#include"Statue.h"

class CDoubleBuffer
{
	CSkeleton* skel;
	CSkeleton* skel1;
	CStatue* statue;
	node* m_currentRoot; // node는 초기화 시키지 않고 nullptr로 시작해야한다. tree에 담을때 tree 안에서 초기화 해준다.
	node* m_nextRoot;//만약 초기화 해준뒤에 트리에 넣으려고 하면 
	//postOrder메소드에서 T가 null이 아니라서 그냥 빠져나오지 않고 Entity의 getNo()메소드가 null(Entity가 nullptr임)이라고 오류뜸 당연히
	// node만 초기화(메모리할당) 했을뿐 node안의 프로퍼티(Entity*등)를 초기화 해주지않았기때문임. 
	CWorld* m_currentMyGame;
	CWorld* m_nextMyGame;

	CWorld world0;
	CWorld world1;
	// 교체 메소드는 여기에서만 호출 하도록 private에 선언
	void swap()
	{
		cout << "교체" << endl;

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
		// 사용할 몬스터 추가(준비단계)
		skel = new CSkeleton(); // 0번
		skel1 = new CSkeleton(); // 1번
		statue = new CStatue(5); // 2버
	}

	~CDoubleBuffer()
	{
	}
	// 몬스터 추가/삭제 메소드(준비한것을 배치함)추가하면 실사용/ 삭재하면 사용하지 않음.
	void callEntity()
	{
		// root가 null이므로 초기화 시켜 주어야 한다. 이렇게 하지 않으면 계속 null상태가 되어 전혀 실행이 되지 않는다.
		m_nextRoot = m_nextMyGame->addEnt(m_nextRoot, skel); // 스켈00 추가
		m_nextMyGame->addEnt(m_nextRoot, statue); // 석상 추가
		m_nextMyGame->removeEnt(m_nextRoot, skel); // 스켈00 삭제
		m_nextMyGame->addEnt(m_nextRoot, skel); // 스켈00 다시 추가
		m_nextMyGame->addEnt(m_nextRoot, skel1); // 스켈01 추가
		m_nextMyGame->removeEnt(m_nextRoot, skel1); // 스켈01 삭제
		m_nextMyGame->addEnt(m_nextRoot, skel1); // 스켈01 다시 추가
		// 석상, 스켈00, 스켈01 

		// 모두 추가했으면 이제 교체
		swap();
	}

	void gameLoop()
	{
		// 무조건 루프 실행은 현재 CWorld만 실행
		m_currentMyGame->gameLoop(m_currentRoot);
		//m_nextMyGame->gameLoop(m_nextRoot);
	}
};

