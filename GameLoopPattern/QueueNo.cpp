#include "QueueNo.h"
#include<iostream>
using namespace std;

CQueueNo::CQueueNo():m_head(nullptr), m_tail(nullptr), m_count(0)
{
}


CQueueNo::~CQueueNo()
{
}

void CQueueNo::enqueue(int key)
{
	noNode* temp = new noNode;
	temp->key = key;
	temp->next = nullptr;
	if (isEmpty())
	{
		m_head = temp;
		m_tail = temp;
	}
	else {
		m_tail->next = temp;
		m_tail = temp;
	}
	m_count++;
}

int CQueueNo::dequeue()
{
	if (!isEmpty())
	{
		int temp = m_head->key;
		noNode* delNode = m_head;
		m_head = delNode->next;
		delete delNode;
		m_count--;
		return temp;
	}
	return -1;
}


