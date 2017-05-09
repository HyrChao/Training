//2017/04/27
//by Chao
//��ɫ��Ϊ���ɫ����

#pragma once

#include "GameFramework/Character.h"
#include "ARGCharacter.generated.h"

enum PlayerAction
{
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	Magic1,
	Magic2,
	Jump,
	Dodge,
};
//typedef void(*FuncP)();//���庯��ָ��
UCLASS()
class ARG_API AARGCharacter : public ACharacter
{
	GENERATED_BODY()

	//�������ײ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))//������ʾ
	USpringArmComponent* cameraBoom;

	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* followCamera;

	//���ӽ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaticMeshComponent, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* sword;


public:

	// �����뺯��
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ���캯��
	AARGCharacter();

	//������״̬����
	float xAxis;
	float yAxis;

	bool presseAttack;
	bool presseMagic;
	bool attackIdleState;
	float isAttacking;
	float usingMagic;


	PlayerAction action;

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
	bool GetAttackState() const { return isAttacking; }

	//���ù���״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	void SetAttackState(bool state) { isAttacking =state;}

	//��ȡħ��״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	bool GetMagicState() const { return usingMagic; }

	//����ħ��״̬
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	void SetMagicState(bool state) { usingMagic = state; }

	void EnterAttackIdleState();
protected:

	// ��Ϸ��ʼ����
	virtual void BeginPlay() override;

	//��ʱ��

	//�������

	void Attack();

	void EndAttack();

	void PresseAttack();

	void ReleaseAttack();

	void Magic();

	void EndMagic();

	void PresseMagic();

	void ReleaseMagic();

	//�ƶ����

	void Walk();

	void StopWalking();

	void MoveForward(float val);


	void MoveRight(float val);	

	//�ӽ����

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

protected:

	//float attackInterval;//�������ʱ��

private:

	//�ƶ���ز���
	float walkRatio;
	float basePlayerTurnRate;

	//������ز���
	FTimerHandle Timer;
	float attackMoveSpeed;

	//��Ծ��ز���


private:

	void EndAttackIdleState();

	//��Ծ��غ���
	void Jump();
};
