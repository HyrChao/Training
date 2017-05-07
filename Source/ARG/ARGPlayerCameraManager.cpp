//2017/05/06
//by Chao

#include "ARG.h"
#include "ARGPlayerCameraManager.h"

void AARGPlayerCameraManager::BeginPlay() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("AARGPlayerCameraManager!"));
	}
}



