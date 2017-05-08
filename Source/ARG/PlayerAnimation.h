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
	//��Ծ״̬����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isJumping;

	//�ƶ��ٶȴ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float moveSpeed;
	
	//�ƶ�������
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float moveDirection;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool attack;

	//ħ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool magic;

	//��������
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();
	
private:

	AARGCharacter* player;
	
};
