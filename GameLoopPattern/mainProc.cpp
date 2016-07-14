#include"World.h"
#include"Statue.h"
#include"Skeleton.h"

// static ������ static������ ����Ȱ��� .h���Ͽ��� �ʱ�ȭ�ϸ� �ߺ��ȴٰ� ������
// �׷��� ����cpp���� �ʱ�ȭ �� �帲!
int CEntity::numEntities = 0;

void main()
{
	node* root = nullptr;
	CWorld* myGame = new CWorld();
	
	CSkeleton* sk01 = new CSkeleton();
	CSkeleton* sk02 = new CSkeleton();
	CStatue* st01 = new CStatue(5);
	CStatue* st02 = new CStatue(10);


	// root�� null�̹Ƿ� �ʱ�ȭ ���� �־�� �Ѵ�. �̷��� ���� ������ ��� null���°� �Ǿ� ���� ������ ���� �ʴ´�.
	root = myGame->addEnt(root, sk01);

	myGame->addEnt(root, st01);
	// ����
	myGame->removeEnt(root, sk01);
	//myGame->addEnt(root, sk01); // �ѹ� ���� ��ü ���� ����
	
	myGame->addEnt(root, sk02);
	myGame->addEnt(root, st02);
	CSkeleton* sk03 = new CSkeleton(); // key 0������ ���� ��.
	myGame->addEnt(root, sk03);
	//cout << "�;� = " << sk03->getNo() << endl;

	// ����
	myGame->gameLoop(root);
}