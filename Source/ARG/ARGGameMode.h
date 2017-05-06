//2017/04/26
//by Chao
#pragma once

#include "GameFramework/GameModeBase.h"
#include "ARGGameMode.generated.h"

UCLASS()
class ARG_API AARGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AARGGameMode();

	virtual void BeginPlay() override;
		
};
