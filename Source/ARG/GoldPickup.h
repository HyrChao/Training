//2017/05/19
//By Chao
//Ê°È¡½ð±ÒÀà

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
