//2017/05/13
//By Chao
//ʰȡ��Ʒ��

#include "ARG.h"
#include "ItemPickup.h"


//���캯��
AItemPickup::AItemPickup()
{
 	// �Ƿ�����ÿ֡����
	PrimaryActorTick.bCanEverTick = true;
	isActive = true;
	collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collison"));
	RootComponent = collision;//��ײ��ΪRootComponent
	pickupMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	pickupMesh->SetSimulatePhysics(true);	//����ʰȡ�������������
	pickupMesh->SetupAttachment(RootComponent);

}

void AItemPickup::OnPickedUp()
{
	Destroy();
}

//��Ϸ��ʼ����
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

//ÿ֡����
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

