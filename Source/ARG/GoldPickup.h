//2017/05/19
//By Chao
//ʰȡ�����

#pragma once

#include "ItemPickup.h"
#include "GoldPickup.generated.h"

UCLASS()
class ARG_API AGoldPickup : public AItemPickup
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gold)
	int gold;

	AGoldPickup();

	void AddGold();

	void OnPickedUp() override;

};
