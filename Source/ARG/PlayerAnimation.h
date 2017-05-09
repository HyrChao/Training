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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//跳跃状态传入
	bool isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//跳跃状态传入
	bool isJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//移动速度传入
	float moveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//移动方向传入
	float moveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//按下攻击
	bool presseAttack;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//按下魔法
	bool presseMagic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//攻击
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//魔法
	bool usingMagic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//攻击后休息动画
	bool attackIdleState;



	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	//更新属性
	void UpdateAnimationProperties();

	//执行一次用函数
	void StartAttackMontage();

	void ResetMontageDoOnce();
	
private:

	AARGCharacter* player;

	UAnimMontage* attackMontage;

	//函数用容器
	bool startedMontage;
	
};
