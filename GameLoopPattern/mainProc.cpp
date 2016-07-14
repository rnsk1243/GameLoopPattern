#include"World.h"
#include"Statue.h"
#include"Skeleton.h"

// static ������ static������ ����Ȱ��� .h���Ͽ��� �ʱ�ȭ�ϸ� �ߺ��ȴٰ� ������
// �׷��� ����cpp���� �ʱ�ȭ �� �帲!
int CEntity::numEntities = 0;

void main()
{
	node* root = nullptr;
	CSkeleton* sk01 = new CSkeleton();
	CStatue* st01 = new CStatue(30);

	CWorld* myGame = new CWorld();

	// root�� null�̹Ƿ� �ʱ�ȭ ���� �־�� �Ѵ�. �̷��� ���� ������ ��� null���°� �Ǿ� ���� ������ ���� �ʴ´�.
	root = myGame->addEnt(root, sk01);
	myGame->addEnt(root, st01);
	
	myGame->gameLoop(root);
	
}