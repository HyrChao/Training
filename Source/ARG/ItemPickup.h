//2017/05/13
//By Chao
//ʰȡ��Ʒ��

#pragma once

#include "GameFramework/Actor.h"
#include "ItemPickup.generated.h"

UCLASS()

class ARG_API AItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	//���캯��
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
