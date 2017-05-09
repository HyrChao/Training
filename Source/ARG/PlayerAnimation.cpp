//2017/05/08
//by Chao
//动画更新用

#include "ARG.h"
#include "PlayerAnimation.h"

UPlayerAnimation::UPlayerAnimation()
{
	player = nullptr;
	startedMontage = false;
	attackIdleState = false;
	//获取攻击Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> _attackMontage(TEXT("AnimMontage'/Game/Character/Ami_Montage_Attack.Ami_Montage_Attack'"));
	attackMontage = _attackMontage.Object;
}

void UPlayerAnimation::UpdateAnimationProperties()
{
	if (player!=nullptr)
	{
		//更新跳跃属性
		isJumping = player->bWasJumping;
		isFalling = player->GetMovementComponent()->IsFalling();

		//更新移动速度
		moveSpeed = player->xAxis;

		//更新移动方向
		moveDirection = player->yAxis;

		//更新攻击状态
		isAttacking = player->isAttacking;
		usingMagic = player->usingMagic;
		presseAttack = player->presseAttack;
		presseMagic = player->presseMagic;
		attackIdleState = player->attackIdleState;

		//判断攻击动画是否结束
		if(!Montage_IsPlaying(attackMontage)&&startedMontage)
		{
			ResetMontageDoOnce();
			player->SetAttackState(false);
			player->EnterAttackIdleState();
		}

		//判定是否进入攻击Montage
		if(isAttacking)
		{
			StartAttackMontage();
		}

	}
	else
		player = Cast<AARGCharacter>(TryGetPawnOwner());
}

void UPlayerAnimation::StartAttackMontage()
{
	if (!startedMontage)
	{
		startedMontage = true;
		Montage_Play(attackMontage, 1.f);
		
	}
}

void UPlayerAnimation::ResetMontageDoOnce()
{
	startedMontage = false;
}


