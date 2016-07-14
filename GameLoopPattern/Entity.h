#pragma once
class CEntity
{
	double m_x;
	double m_y;
	int m_no;
public:
	CEntity():m_x(0.0),m_y(0.0),m_no(numEntities)
	{
		numEntities++;
	}
	~CEntity()
	{
	}
	virtual void update() = 0;

	static int numEntities;
	double getX()const { return m_x; }
	double getY()const { return m_y; }
	void setX(double x) { m_x = x; }
	void setY(double y) { m_y = y; }
	int getNo() { return m_no; }
};

