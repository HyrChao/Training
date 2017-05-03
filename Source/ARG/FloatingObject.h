//2017/05/3
//By Chao

//上下浮动物体类
#pragma once

#include "GameFramework/Actor.h"
#include "FloatingObject.generated.h"

UCLASS()
class ARG_API AFloatingObject : public AActor
{
	GENERATED_BODY()
	
public:	

	AFloatingObject();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:	

	float runTime;
	
};
