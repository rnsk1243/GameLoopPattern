#pragma once
#include "Entity.h"
#include<iostream>
using namespace std;

class CSkeleton :
	public CEntity
{
	bool m_patrollingLeft;
public:
	CSkeleton():m_patrollingLeft(false){}
	virtual ~CSkeleton(){}
	virtual void update()
	{
		if (m_patrollingLeft)
		{
			setX(getX() - 1);
			if (getX() == 0)
				m_patrollingLeft = false;
		}
		else
		{
			setX(getX() + 1);
			if (getX() == 100)
				m_patrollingLeft = true;
		}
		cout << getNo() << "번 해골 : " << getX() << " 지점 이동 중..." << endl;
	}
};

