//2017/04/26
//by Chao

#include "ARG.h"
#include "ARGGameMode.h"

AARGGameMode::AARGGameMode() 
{
	//为蓝图角色类设置默认的角色
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Ami_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AARGGameMode::BeginPlay() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Red,TEXT("Hello World!"));
	}
}

