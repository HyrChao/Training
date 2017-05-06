//2017/04/27
//by Chao
#pragma once

#include "GameFramework/Character.h"
#include "ARGCharacter.generated.h"

UCLASS()
class ARG_API AARGCharacter : public ACharacter
{
	GENERATED_BODY()

	//�������ײ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))//������ʾ
	class USpringArmComponent* CameraBoom;

	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// ���캯��
	AARGCharacter();

	// ��Ϸ��ʼ����
	virtual void BeginPlay() override;
	
	// ÿ֡����
	virtual void Tick( float DeltaSeconds ) override;

	//����ת����, ��λ��ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	//��������&������, ��λ��ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//����CameraBoom subobject�Ӷ���
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }//FORCEINLINE��ǿ��ת������Ϊ����
	//����FollowCamera�Ӷ���
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


protected:

	// �����뺯��
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float val);

	void MoveRight(float val);	

	void TurnArround(float val);

	void LookUp(float val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

};
