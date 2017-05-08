//2017/05/08
//by Chao
//动画更新用

#include "ARG.h"
#include "PlayerAnimation.h"

UPlayerAnimation::UPlayerAnimation()
{
	player = nullptr;
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
		attack = player->presseAttack;
		magic = player->presseMagic;

	}
	else
		player = Cast<AARGCharacter>(TryGetPawnOwner());
}


