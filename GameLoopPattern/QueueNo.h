#pragma once
// 키를 보관하는 큐
struct noNode
{
	int key;
	noNode* next;
};

class CQueueNo
{
	noNode* m_head;
	noNode* m_tail;
	int m_count;
public:
	CQueueNo();
	~CQueueNo();
	void enqueue(int key);
	int dequeue();
	bool isEmpty() { return m_count == 0; }
	int getCount() { return m_count; }
};

