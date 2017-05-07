//2017/04/26
//by Chao

#include "ARG.h"
#include "ARGGameMode.h"
#include "ARGPlayerController.h"

AARGGameMode::AARGGameMode() 
{
	//Ϊ��ͼ��ɫ������Ĭ�ϵĽ�ɫ
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Ami_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//����Ĭ�Ͻ�ɫ������
	PlayerControllerClass = AARGPlayerController::StaticClass();
}

void AARGGameMode::BeginPlay() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Red,TEXT("Hello World!"));
	}
}

