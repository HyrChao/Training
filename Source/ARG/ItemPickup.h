//2017/05/13
//By Chao
//拾取物品类

#pragma once

#include "GameFramework/Actor.h"
#include "ItemPickup.generated.h"

UCLASS()

class ARG_API AItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	//构造函数
	AItemPickup();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	bool isActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	USphereComponent* collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	UStaticMeshComponent* pickupMesh;

	//UFUNCTION(BlueprintNativeEvent)
	virtual void OnPickedUp();



protected:
	
	virtual void BeginPlay() override;
	
private:

};
