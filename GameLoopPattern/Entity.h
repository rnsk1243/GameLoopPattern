#pragma once
#include"QueueNo.h"
#include<iostream>
using namespace std;

class CEntity
{
	double m_x;
	double m_y;
	// Ű��
	int m_no;
public:
	CEntity():m_x(0.0),m_y(0.0)
	{
		// ť�� ���������
		if (queueKey->isEmpty())
		{
			// �ʱ�ȭ�ϰ� �������� ������
			m_no = numEntities;
			numEntities++;
		}
		else {
			// ��ü�� �����Ǿ� ť�� ������� ������ ���� �����Ǿ� ���� ��ȣ�� ����
			m_no = queueKey->dequeue();
			cout << "���� �� ��ȣ = " << m_no << endl;
		}
		
	}
	~CEntity()
	{
	}
	virtual void update() = 0;
	// Ʈ���� �����ϴ� Ű��
	static CQueueNo* seveKey;
	// ����� Ű�� ����
	static CQueueNo* queueKey;
	// key���̴�. �� ���� 0���� ���������� ���ӵɶ��� �����Ѵ�.
	// ���� �ߺ��Ǵ� ������ ��ü���� ��ȣ�� key��ȣ�� �Ű�����.
	static int numEntities;
	double getX()const { return m_x; }
	double getY()const { return m_y; }
	void setX(double x) { m_x = x; }
	void setY(double y) { m_y = y; }
	int getNo() { return m_no; }
};

