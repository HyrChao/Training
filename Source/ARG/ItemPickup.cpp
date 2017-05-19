//2017/05/13
//By Chao
//拾取物品类

#include "ARG.h"
#include "ItemPickup.h"


//构造函数
AItemPickup::AItemPickup()
{
 	// 是否启用每帧调用
	PrimaryActorTick.bCanEverTick = true;
	isActive = true;
	collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collison"));
	RootComponent = collision;//碰撞体为RootComponent
	pickupMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	pickupMesh->SetSimulatePhysics(true);	//设置拾取网格的物理属性
	pickupMesh->SetupAttachment(RootComponent);

}

void AItemPickup::OnPickedUp()
{
	Destroy();
}

//游戏开始调用
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

//每帧调用
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

