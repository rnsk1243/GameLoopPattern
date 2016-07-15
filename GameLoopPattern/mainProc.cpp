#include"World.h"
#include"Statue.h"
#include"Skeleton.h"
#include<Windows.h>
#include"DoubleBuffer.h"
#include<time.h>

// 1초마다 업데이트 메소드 호출하도록
#define MS_PER_UPDATE 1000

// static 변수는 static변수가 선언된곳의 .h파일에서 초기화하면 중복된다고 에러뜸
// 그래서 메인cpp에서 초기화 해 드림!
int CEntity::numEntities = 0;

// 스레드생성에(CHeroineState 클래스의 update메소드 호출) 필요한 파라미터
struct ARGS
{
	// update의 파라미터로 들어갈 히로인 객체
	// &을 붙여주여야 엉뚱한 곳을 찾지 않고 내가 생성한 객체를 잘 찾아간다.(추측)
	// 만약 &을 붙여주지 않으면 프로그램이 죽지는 않으나 내가 원하는 update메소드가 호출되지 않음
	CDoubleBuffer& buffer;
	// 다양한 상태들의 부모 클래스를 선언하여 이 클래스를 상속받은 모든 클래스의 update메소드를 호출 할 수 있음
	//CHeroineState* state; // state를 정적변수로 바꾸면서 더이상 필요가 없어졌다.
};

// 따라잡기가 들어간 루프
// 업데이트 호출 스레드
DWORD WINAPI updateThread(LPVOID arg)
{
	// 시작 시간
	double begin;
	//cout << "스레드 생성 됨" << endl;
	begin = clock();
	// lag는 게임이 멈추어도 계속 증가하며 업데이트 메소드 호출시 MS_PER_UPDATE 값 만큼 줄어든다.
	double lag = 0.0;
	while (true)
	{
		
		// 구조체 주소를 담을 pArgs변수를 선언하고 파라미터로 들어온 arg를 ARGS구조체 주소형으로 바꾸어줌
		ARGS* pArgs = (ARGS*)arg;
		// 현재 시간
		double current = clock();
		// 경과 시간
		double elapsed = current - begin; // 2. begin 여기까지 시간을 재서(루프 한바퀴 돈것) 현재시간 current에 빼서 경과시간을 구함
		// 시작시간을 현재시간으로 교체
		begin = current; //1. begin시간이 여기서 부터
		// 경과시간 만큼 더함(만약 컴퓨터가 멈추면 한번에 큰 값이 lag에 들어감)
		lag += elapsed;
		// 인풋메소드 호출 부분
		//
		//////////////////////
		//cout << "lag = " << lag << endl;
		// MS_PER_UPDATE의 지정한 값보다 lag값이 크면(지연되어 lag값이 더 크게 될때)
		// 한번 호출마다 lag값이 MS_PER_UPDATE만큼씩 줄어들어 결국 while문을 빠져나온다.
		// 이게 따라잡기 이다.
		// 컴터가 지연되어 lag값이 커지면 그만큼 게임루프가 뒤쳐져 있다는 상태이므로
		// 따라잡기 위해 게임루프를 여러번 실행 시켜주는 것이다. 그후에 렌더링을 한번 거는 것이다.
		while (lag >= MS_PER_UPDATE)
		{
			// 버퍼에 담긴 현재 CWorld만 실행
			pArgs->buffer.gameLoop(); // 게임루프(업데이트메소드)를 실행
			// 한번 게임루프문 실행후 MS_PER_UPDATE만큼 빼줌
			lag -= MS_PER_UPDATE;
			
			//cout << "lag ============ " << lag << endl;
		}
		// 랜더링 함수 호출 부분
		//
		////////////////////////
		//Sleep(100);
	}
}



void main()
{
	// 버퍼
	CDoubleBuffer* gameBuffer = new CDoubleBuffer();
	// 버퍼의 몬스터 초기화 메소드 실행
	gameBuffer->callEntity();
	// 스레드를 담을 변수
	HANDLE hThreadUpdate = NULL;
	// 구조체에 버퍼를 담음
	ARGS args = { *gameBuffer };

	while (true)
	{


		// 입력마다 스레드가 만들어지지 않도록 스레드가 안만들어진 NULL일때만 통과시켜줌
		if (hThreadUpdate == NULL)
		{
			// 스레드 생성
			hThreadUpdate = CreateThread(NULL, 0, updateThread, &args, 0, NULL);
			if (hThreadUpdate == NULL)
				return;
			CloseHandle(hThreadUpdate);
		}
		// 영원한 안식(스레드만 일합시다)
		Sleep(10000000);
	}
	cout << "==============================================" << endl;
}
/*
#include"World.h"
#include"Statue.h"
#include"Skeleton.h"
#include<Windows.h>

// static 변수는 static변수가 선언된곳의 .h파일에서 초기화하면 중복된다고 에러뜸
// 그래서 메인cpp에서 초기화 해 드림!
int CEntity::numEntities = 0;

// 스레드생성에(CHeroineState 클래스의 update메소드 호출) 필요한 파라미터
struct ARGS
{
	// update의 파라미터로 들어갈 히로인 객체
	// &을 붙여주여야 엉뚱한 곳을 찾지 않고 내가 생성한 객체를 잘 찾아간다.(추측)
	// 만약 &을 붙여주지 않으면 프로그램이 죽지는 않으나 내가 원하는 update메소드가 호출되지 않음
	CWorld& world;
	node& root;
	// 다양한 상태들의 부모 클래스를 선언하여 이 클래스를 상속받은 모든 클래스의 update메소드를 호출 할 수 있음
	//CHeroineState* state; // state를 정적변수로 바꾸면서 더이상 필요가 없어졌다.
};

// 업데이트 호출 스레드
DWORD WINAPI updateThread(LPVOID arg)
{
	//cout << "스레드 생성 됨" << endl;
	while (true)
	{
		//cout << "호라여!" << endl;
		// 구조체 주소를 담을 pArgs변수를 선언하고 파라미터로 들어온 arg를 ARGS구조체 주소형으로 바꾸어줌
		ARGS* pArgs = (ARGS*)arg;
		pArgs->world.gameLoop(&pArgs->root);
		Sleep(100);
	}
}

void main()
{
	node* root = nullptr;
	CWorld* myGame = new CWorld();
	// 스레드를 담을 변수
	HANDLE hThreadUpdate = NULL;
	
	CSkeleton* sk01 = new CSkeleton();
//	CSkeleton* sk02 = new CSkeleton();
	CStatue* st01 = new CStatue(5);
//	CStatue* st02 = new CStatue(10);


	// root가 null이므로 초기화 시켜 주어야 한다. 이렇게 하지 않으면 계속 null상태가 되어 전혀 실행이 되지 않는다.
	root = myGame->addEnt(root, sk01);
	// 타워 설치
	myGame->addEnt(root, st01);
	
//	myGame->addEnt(root, sk02);
//	myGame->addEnt(root, st02);
	CSkeleton* sk03 = new CSkeleton(); // key 0번으로 재사용 됨.
	myGame->addEnt(root, sk03);
	//cout << "와씨 = " << sk03->getNo() << endl;

	
	//myGame->addEnt(root, sk01); // 한번 지운 객체 재사용 금지 // 객체 트리에 들어가지 못하도록 했음
	#############
	우연히.
	더블버퍼를 사용하면서 버그를 잡았다.
	원래 한번 delEnt하면 그 지운 객체는 다시 사용 못했는데 더블 버퍼를 쓰면서
	Entity객체를 버퍼생성자에서 초기화해주어서 객체번호가 순서대로 0부터 자연스럽게 매겨진다.
	거기다 생성자는 callEntity()몬스터 추가 메소드보다 먼저 호출 되므로 몬스터 추가 메소드에서
	몬스터를 삭제 한다고 해도 이미 순서대로 고정된 객체번호가 부여되어 몬스터 추가 메소드에서
	마음데로 삭제하고 다시 생성하고 해도 된다. 
	이렇게 되면 번호를 재사용하려고 큐를 만들어두었는데 무쓸모가 되었다. 
	#############
	// 루프
	//myGame->gameLoop(root);
	
	// 삭제
	
	while (true)
	{
		// 구조체 초기화 한다.
		ARGS args = { *myGame, *root };
		// 더블 버퍼를 쓰지 않았을 경우 여기서 오류가 난다.
		// 이유는 바로 위에서 args구조체를 초기화 해준 상태에서 
		// 아래에서 sk01객체를 트리에서 지웠다
		// 하지만 구조체는 sk01객체가 지워진줄 모른다. 이상태에서 구조체를 넘겨받은 스레드는 sk01객체가 있는줄알고
		// sk01객체의 update메소드를 실행함으로 오류가 발생한다.
		// 이런 오류를 방지하기위해 더블 버퍼를 사용해보았다.
		// 후면버퍼에 모든 몬스터 추가or삭제를 한 뒤에 포인터를 교체하여(주소교체) 전면버퍼를 가리키던 포인터가
		후면버퍼를 가리키게 됨(이제 후면버퍼가 전면버퍼임) 
		모든 준비가 끝난 후에(추가될건 추가되고 삭제된건 삭제가 된, 최신상태의 동기화가 잘됐다.) 
		각 객체의 update메소드를 호출하므로 오류없이 잘 된다.
		myGame->removeEnt(root, sk01); // <- 여기
		// 입력마다 스레드가 만들어지지 않도록 스레드가 안만들어진 NULL일때만 통과시켜줌
		if (hThreadUpdate == NULL)
		{
			// 스레드 생성
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