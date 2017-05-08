//2017/05/08
//by Chao
//����������

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
		//������Ծ����
		isJumping = player->bWasJumping;
		isFalling = player->GetMovementComponent()->IsFalling();

		//�����ƶ��ٶ�
		moveSpeed = player->xAxis;

		//�����ƶ�����
		moveDirection = player->yAxis;

		//���¹���״̬
		attack = player->presseAttack;
		magic = player->presseMagic;

	}
	else
		player = Cast<AARGCharacter>(TryGetPawnOwner());
}


