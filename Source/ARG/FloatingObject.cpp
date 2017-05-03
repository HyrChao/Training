//2017/05/3
//By Chao

//上下浮动物体类

#include "ARG.h"
#include "FloatingObject.h"

AFloatingObject::AFloatingObject()
{
	//开启美帧调用函数
	PrimaryActorTick.bCanEverTick = true;

}

void AFloatingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFloatingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//实现上下浮动，通过sin函数
	FVector currentLocatiom= GetActorLocation();
	float deltaH = (FMath::Sin(DeltaTime + runTime) - FMath::Sin(DeltaTime));
	currentLocatiom.Z += deltaH*5;//乘速度参数,Z轴增加
	runTime += DeltaTime;
	SetActorLocation(currentLocatiom);
}

