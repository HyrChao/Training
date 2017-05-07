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
	class USpringArmComponent* cameraBoom;

	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;


public:

	// �����뺯��
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ���캯��
	AARGCharacter();

	
	// ÿ֡����
	virtual void Tick(float DeltaTime) override;

	//����ת����, ��λ��ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float baseTurnRate;

	//��������&������, ��λ��ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float baseLookUpRate;

	//����CameraBoom subobject�Ӷ���
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraBoom; }//FORCEINLINE��ǿ��ת������Ϊ����
	//����FollowCamera�Ӷ���
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return followCamera; }

	//��ͼ��

	//��ȡ����״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		bool GetAttackState() const { return presseAttack; }

	//���ù���״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		void SetAttackState(bool state) { presseAttack =state;}

	//��ȡħ��״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		bool GetMagicState() const { return presseMagic; }

	//����ħ��״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		void SetMagicState(bool state) { presseMagic = state; }
protected:

	// ��Ϸ��ʼ����
	virtual void BeginPlay() override;

	//�������

	void Attack();

	void Magic();

	void ReleaseAttack();

	void ReleaseMagic();

	//�ƶ����

	void Walk();

	void StopWalking();

	void MoveForward(float val);

	void MoveRight(float val);	

	//�ӽ����

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

private:

	bool presseAttack;

	bool presseMagic;

	float walkRatio;



};
