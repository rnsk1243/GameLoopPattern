#pragma once
#include<iostream>
using namespace std;
#include "Entity.h"

class CStatue :
	public CEntity
{
	int m_frames;
	int m_delay;
public:
	CStatue(int delay):m_frames(0),m_delay(delay) {}
	virtual ~CStatue(){}
	virtual void update()
	{
		if (++m_frames == m_delay)
		{
			shootLightning();
			m_frames = 0;
		}
	}
	void shootLightning()
	{
		cout << getNo() << "¹ø Å¸¿ö : Äâ°ú±¤!!!!!" << endl;
	}
};

