//2017/05/06
//by Chao

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "ARGPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ARG_API AARGPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	
protected:

	virtual void BeginPlay() override;
	
};
