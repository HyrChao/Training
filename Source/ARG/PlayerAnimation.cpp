//2017/05/08
//by Chao
//����������

#include "ARG.h"
#include "PlayerAnimation.h"

UPlayerAnimation::UPlayerAnimation()
{
	player = nullptr;
	startedMontage = false;
	attackIdleState = false;
	//��ȡ����Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> _attackMontage(TEXT("AnimMontage'/Game/Character/Ami_Montage_Attack.Ami_Montage_Attack'"));
	attackMontage = _attackMontage.Object;
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
		isAttacking = player->isAttacking;
		usingMagic = player->usingMagic;
		presseAttack = player->presseAttack;
		presseMagic = player->presseMagic;
		attackIdleState = player->attackIdleState;

		//�жϹ��������Ƿ����
		if(!Montage_IsPlaying(attackMontage)&&startedMontage)
		{
			ResetMontageDoOnce();
			player->SetAttackState(false);
			player->EnterAttackIdleState();
		}

		//�ж��Ƿ���빥��Montage
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


