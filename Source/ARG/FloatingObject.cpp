//2017/05/3
//By Chao

//���¸���������

#include "ARG.h"
#include "FloatingObject.h"

AFloatingObject::AFloatingObject()
{
	//������֡���ú���
	PrimaryActorTick.bCanEverTick = true;

}

void AFloatingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFloatingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ʵ�����¸�����ͨ��sin����
	FVector currentLocatiom= GetActorLocation();
	float deltaH = (FMath::Sin(DeltaTime + runTime) - FMath::Sin(DeltaTime));
	currentLocatiom.Z += deltaH*5;//���ٶȲ���,Z������
	runTime += DeltaTime;
	SetActorLocation(currentLocatiom);
}

