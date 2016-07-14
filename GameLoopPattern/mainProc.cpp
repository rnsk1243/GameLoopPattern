#include"World.h"
#include"Statue.h"
#include"Skeleton.h"

// static 변수는 static변수가 선언된곳의 .h파일에서 초기화하면 중복된다고 에러뜸
// 그래서 메인cpp에서 초기화 해 드림!
int CEntity::numEntities = 0;

void main()
{
	node* root = nullptr;
	CSkeleton* sk01 = new CSkeleton();
	CStatue* st01 = new CStatue(30);

	CWorld* myGame = new CWorld();

	// root가 null이므로 초기화 시켜 주어야 한다. 이렇게 하지 않으면 계속 null상태가 되어 전혀 실행이 되지 않는다.
	root = myGame->addEnt(root, sk01);
	myGame->addEnt(root, st01);
	
	myGame->gameLoop(root);
	
}