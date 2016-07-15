#include"World.h"
#include"Statue.h"
#include"Skeleton.h"
#include<Windows.h>
#include"DoubleBuffer.h"
#include<time.h>

// 1�ʸ��� ������Ʈ �޼ҵ� ȣ���ϵ���
#define MS_PER_UPDATE 1000

// static ������ static������ ����Ȱ��� .h���Ͽ��� �ʱ�ȭ�ϸ� �ߺ��ȴٰ� ������
// �׷��� ����cpp���� �ʱ�ȭ �� �帲!
int CEntity::numEntities = 0;

// �����������(CHeroineState Ŭ������ update�޼ҵ� ȣ��) �ʿ��� �Ķ����
struct ARGS
{
	// update�� �Ķ���ͷ� �� ������ ��ü
	// &�� �ٿ��ֿ��� ������ ���� ã�� �ʰ� ���� ������ ��ü�� �� ã�ư���.(����)
	// ���� &�� �ٿ����� ������ ���α׷��� ������ ������ ���� ���ϴ� update�޼ҵ尡 ȣ����� ����
	CDoubleBuffer& buffer;
	// �پ��� ���µ��� �θ� Ŭ������ �����Ͽ� �� Ŭ������ ��ӹ��� ��� Ŭ������ update�޼ҵ带 ȣ�� �� �� ����
	//CHeroineState* state; // state�� ���������� �ٲٸ鼭 ���̻� �ʿ䰡 ��������.
};

// ������Ⱑ �� ����
// ������Ʈ ȣ�� ������
DWORD WINAPI updateThread(LPVOID arg)
{
	// ���� �ð�
	double begin;
	//cout << "������ ���� ��" << endl;
	begin = clock();
	// lag�� ������ ���߾ ��� �����ϸ� ������Ʈ �޼ҵ� ȣ��� MS_PER_UPDATE �� ��ŭ �پ���.
	double lag = 0.0;
	while (true)
	{
		
		// ����ü �ּҸ� ���� pArgs������ �����ϰ� �Ķ���ͷ� ���� arg�� ARGS����ü �ּ������� �ٲپ���
		ARGS* pArgs = (ARGS*)arg;
		// ���� �ð�
		double current = clock();
		// ��� �ð�
		double elapsed = current - begin; // 2. begin ������� �ð��� �缭(���� �ѹ��� ����) ����ð� current�� ���� ����ð��� ����
		// ���۽ð��� ����ð����� ��ü
		begin = current; //1. begin�ð��� ���⼭ ����
		// ����ð� ��ŭ ����(���� ��ǻ�Ͱ� ���߸� �ѹ��� ū ���� lag�� ��)
		lag += elapsed;
		// ��ǲ�޼ҵ� ȣ�� �κ�
		//
		//////////////////////
		//cout << "lag = " << lag << endl;
		// MS_PER_UPDATE�� ������ ������ lag���� ũ��(�����Ǿ� lag���� �� ũ�� �ɶ�)
		// �ѹ� ȣ�⸶�� lag���� MS_PER_UPDATE��ŭ�� �پ��� �ᱹ while���� �������´�.
		// �̰� ������� �̴�.
		// ���Ͱ� �����Ǿ� lag���� Ŀ���� �׸�ŭ ���ӷ����� ������ �ִٴ� �����̹Ƿ�
		// ������� ���� ���ӷ����� ������ ���� �����ִ� ���̴�. ���Ŀ� �������� �ѹ� �Ŵ� ���̴�.
		while (lag >= MS_PER_UPDATE)
		{
			// ���ۿ� ��� ���� CWorld�� ����
			pArgs->buffer.gameLoop(); // ���ӷ���(������Ʈ�޼ҵ�)�� ����
			// �ѹ� ���ӷ����� ������ MS_PER_UPDATE��ŭ ����
			lag -= MS_PER_UPDATE;
			
			//cout << "lag ============ " << lag << endl;
		}
		// ������ �Լ� ȣ�� �κ�
		//
		////////////////////////
		//Sleep(100);
	}
}



void main()
{
	// ����
	CDoubleBuffer* gameBuffer = new CDoubleBuffer();
	// ������ ���� �ʱ�ȭ �޼ҵ� ����
	gameBuffer->callEntity();
	// �����带 ���� ����
	HANDLE hThreadUpdate = NULL;
	// ����ü�� ���۸� ����
	ARGS args = { *gameBuffer };

	while (true)
	{


		// �Է¸��� �����尡 ��������� �ʵ��� �����尡 �ȸ������ NULL�϶��� ���������
		if (hThreadUpdate == NULL)
		{
			// ������ ����
			hThreadUpdate = CreateThread(NULL, 0, updateThread, &args, 0, NULL);
			if (hThreadUpdate == NULL)
				return;
			CloseHandle(hThreadUpdate);
		}
		// ������ �Ƚ�(�����常 ���սô�)
		Sleep(10000000);
	}
	cout << "==============================================" << endl;
}
/*
#include"World.h"
#include"Statue.h"
#include"Skeleton.h"
#include<Windows.h>

// static ������ static������ ����Ȱ��� .h���Ͽ��� �ʱ�ȭ�ϸ� �ߺ��ȴٰ� ������
// �׷��� ����cpp���� �ʱ�ȭ �� �帲!
int CEntity::numEntities = 0;

// �����������(CHeroineState Ŭ������ update�޼ҵ� ȣ��) �ʿ��� �Ķ����
struct ARGS
{
	// update�� �Ķ���ͷ� �� ������ ��ü
	// &�� �ٿ��ֿ��� ������ ���� ã�� �ʰ� ���� ������ ��ü�� �� ã�ư���.(����)
	// ���� &�� �ٿ����� ������ ���α׷��� ������ ������ ���� ���ϴ� update�޼ҵ尡 ȣ����� ����
	CWorld& world;
	node& root;
	// �پ��� ���µ��� �θ� Ŭ������ �����Ͽ� �� Ŭ������ ��ӹ��� ��� Ŭ������ update�޼ҵ带 ȣ�� �� �� ����
	//CHeroineState* state; // state�� ���������� �ٲٸ鼭 ���̻� �ʿ䰡 ��������.
};

// ������Ʈ ȣ�� ������
DWORD WINAPI updateThread(LPVOID arg)
{
	//cout << "������ ���� ��" << endl;
	while (true)
	{
		//cout << "ȣ��!" << endl;
		// ����ü �ּҸ� ���� pArgs������ �����ϰ� �Ķ���ͷ� ���� arg�� ARGS����ü �ּ������� �ٲپ���
		ARGS* pArgs = (ARGS*)arg;
		pArgs->world.gameLoop(&pArgs->root);
		Sleep(100);
	}
}

void main()
{
	node* root = nullptr;
	CWorld* myGame = new CWorld();
	// �����带 ���� ����
	HANDLE hThreadUpdate = NULL;
	
	CSkeleton* sk01 = new CSkeleton();
//	CSkeleton* sk02 = new CSkeleton();
	CStatue* st01 = new CStatue(5);
//	CStatue* st02 = new CStatue(10);


	// root�� null�̹Ƿ� �ʱ�ȭ ���� �־�� �Ѵ�. �̷��� ���� ������ ��� null���°� �Ǿ� ���� ������ ���� �ʴ´�.
	root = myGame->addEnt(root, sk01);
	// Ÿ�� ��ġ
	myGame->addEnt(root, st01);
	
//	myGame->addEnt(root, sk02);
//	myGame->addEnt(root, st02);
	CSkeleton* sk03 = new CSkeleton(); // key 0������ ���� ��.
	myGame->addEnt(root, sk03);
	//cout << "�;� = " << sk03->getNo() << endl;

	
	//myGame->addEnt(root, sk01); // �ѹ� ���� ��ü ���� ���� // ��ü Ʈ���� ���� ���ϵ��� ����
	#############
	�쿬��.
	������۸� ����ϸ鼭 ���׸� ��Ҵ�.
	���� �ѹ� delEnt�ϸ� �� ���� ��ü�� �ٽ� ��� ���ߴµ� ���� ���۸� ���鼭
	Entity��ü�� ���ۻ����ڿ��� �ʱ�ȭ���־ ��ü��ȣ�� ������� 0���� �ڿ������� �Ű�����.
	�ű�� �����ڴ� callEntity()���� �߰� �޼ҵ庸�� ���� ȣ�� �ǹǷ� ���� �߰� �޼ҵ忡��
	���͸� ���� �Ѵٰ� �ص� �̹� ������� ������ ��ü��ȣ�� �ο��Ǿ� ���� �߰� �޼ҵ忡��
	�������� �����ϰ� �ٽ� �����ϰ� �ص� �ȴ�. 
	�̷��� �Ǹ� ��ȣ�� �����Ϸ��� ť�� �����ξ��µ� ������ �Ǿ���. 
	#############
	// ����
	//myGame->gameLoop(root);
	
	// ����
	
	while (true)
	{
		// ����ü �ʱ�ȭ �Ѵ�.
		ARGS args = { *myGame, *root };
		// ���� ���۸� ���� �ʾ��� ��� ���⼭ ������ ����.
		// ������ �ٷ� ������ args����ü�� �ʱ�ȭ ���� ���¿��� 
		// �Ʒ����� sk01��ü�� Ʈ������ ������
		// ������ ����ü�� sk01��ü�� �������� �𸥴�. �̻��¿��� ����ü�� �Ѱܹ��� ������� sk01��ü�� �ִ��پ˰�
		// sk01��ü�� update�޼ҵ带 ���������� ������ �߻��Ѵ�.
		// �̷� ������ �����ϱ����� ���� ���۸� ����غ��Ҵ�.
		// �ĸ���ۿ� ��� ���� �߰�or������ �� �ڿ� �����͸� ��ü�Ͽ�(�ּұ�ü) ������۸� ����Ű�� �����Ͱ�
		�ĸ���۸� ����Ű�� ��(���� �ĸ���۰� ���������) 
		��� �غ� ���� �Ŀ�(�߰��ɰ� �߰��ǰ� �����Ȱ� ������ ��, �ֽŻ����� ����ȭ�� �ߵƴ�.) 
		�� ��ü�� update�޼ҵ带 ȣ���ϹǷ� �������� �� �ȴ�.
		myGame->removeEnt(root, sk01); // <- ����
		// �Է¸��� �����尡 ��������� �ʵ��� �����尡 �ȸ������ NULL�϶��� ���������
		if (hThreadUpdate == NULL)
		{
			// ������ ����
			hThreadUpdate = CreateThread(NULL, 0, updateThread, &args, 0, NULL);
			if (hThreadUpdate == NULL)
				return;
			CloseHandle(hThreadUpdate);
		}
		
		Sleep(500);
	}
	cout << "==============================================" << endl;
}
*/