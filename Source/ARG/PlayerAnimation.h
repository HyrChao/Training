//2017/05/08
//by Chao
//����������

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
	//��Ծ״̬����
	bool isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//��Ծ״̬����
	bool isJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//�ƶ��ٶȴ���
	float moveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//�ƶ�������
	float moveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//���¹���
	bool presseAttack;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//����ħ��
	bool presseMagic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//����
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//ħ��
	bool usingMagic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//��������Ϣ����
	bool attackIdleState;



	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	//��������
	void UpdateAnimationProperties();

	//ִ��һ���ú���
	void StartAttackMontage();

	void ResetMontageDoOnce();
	
private:

	AARGCharacter* player;

	UAnimMontage* attackMontage;

	//����������
	bool startedMontage;
	
};
