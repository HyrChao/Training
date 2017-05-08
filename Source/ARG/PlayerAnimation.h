//2017/05/08
//by Chao
//动画更新用

#pragma once

#include "Animation/AnimInstance.h"
#include "ARGCharacter.h"
#include "PlayerAnimation.generated.h"


UCLASS()
class ARG_API UPlayerAnimation : public UAnimInstance
{
	GENERATED_BODY()
public:
	//
	UPlayerAnimation();

protected:
	//跳跃状态传入
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isJumping;

	//移动速度传入
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float moveSpeed;
	
	//移动方向传入
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float moveDirection;

	//攻击
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool attack;

	//魔法
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool magic;

	//更新属性
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();
	
private:

	AARGCharacter* player;
	
};
