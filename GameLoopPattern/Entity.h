#pragma once
#include"QueueNo.h"
#include<iostream>
using namespace std;

class CEntity
{
	double m_x;
	double m_y;
	// 키값
	int m_no;
public:
	CEntity():m_x(0.0),m_y(0.0)
	{
		// 큐가 비어있으면
		if (queueKey->isEmpty())
		{
			// 초기화하고 정적변수 값증가
			m_no = numEntities;
			numEntities++;
		}
		else {
			// 객체가 삭제되어 큐가 비어있지 않으면 먼저 삭제되어 들어온 번호를 재사용
			m_no = queueKey->dequeue();
			cout << "재사용 된 번호 = " << m_no << endl;
		}
		
	}
	~CEntity()
	{
	}
	virtual void update() = 0;
	// 트리에 존재하는 키값
	static CQueueNo* seveKey;
	// 삭재된 키를 담음
	static CQueueNo* queueKey;
	// key값이다. 이 값은 0부터 양의정수가 연속될때만 증가한다.
	// 따라서 중복되는 값없이 객체마다 번호가 key번호가 매겨진다.
	static int numEntities;
	double getX()const { return m_x; }
	double getY()const { return m_y; }
	void setX(double x) { m_x = x; }
	void setY(double y) { m_y = y; }
	int getNo() { return m_no; }
};

