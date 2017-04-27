//2017/04/26
//by Chao

#include "ARG.h"
#include "ARGGameMode.h"


void AARGGameMode::BeginPlay() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Red,TEXT("Hello World!"));
	}
}

