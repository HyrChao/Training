//2017/04/27
//by Chao
//角色行为与角色控制

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
//typedef void(*FuncP)();//定义函数指针
UCLASS()
class ARG_API AARGCharacter : public ACharacter
{
	GENERATED_BODY()

	//摄像机碰撞
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))//属性显示
	USpringArmComponent* cameraBoom;

	//相机跟随
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* followCamera;

	//附加剑
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaticMeshComponent, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* sword;


public:

	// 绑定输入函数
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 构造函数
	AARGCharacter();

	//动画及状态参数
	float xAxis;
	float yAxis;

	bool presseAttack;
	bool presseMagic;
	bool attackIdleState;
	float isAttacking;
	float usingMagic;


	PlayerAction action;

	// 每帧调用
	virtual void Tick(float DeltaTime) override;

	//基础转向率, 单位度每秒
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float baseTurnRate;

	//基础俯视&仰视率, 单位度每秒
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float baseLookUpRate;

	//返回CameraBoom subobject子对象
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraBoom; }//FORCEINLINE宏强制转换函数为内联
	//返回FollowCamera子对象
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return followCamera; }

	//蓝图用

	//获取攻击状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	bool GetAttackState() const { return isAttacking; }

	//设置攻击状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	void SetAttackState(bool state) { isAttacking =state;}

	//获取魔法状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	bool GetMagicState() const { return usingMagic; }

	//设置魔法状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
	void SetMagicState(bool state) { usingMagic = state; }

	void EnterAttackIdleState();
protected:

	// 游戏开始调用
	virtual void BeginPlay() override;

	//计时器

	//攻击相关

	void Attack();

	void EndAttack();

	void PresseAttack();

	void ReleaseAttack();

	void Magic();

	void EndMagic();

	void PresseMagic();

	void ReleaseMagic();

	//移动相关

	void Walk();

	void StopWalking();

	void MoveForward(float val);


	void MoveRight(float val);	

	//视角相关

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

protected:

	//float attackInterval;//攻击间隔时间

private:

	//移动相关参数
	float walkRatio;
	float basePlayerTurnRate;

	//攻击相关参数
	FTimerHandle Timer;
	float attackMoveSpeed;

	//跳跃相关参数


private:

	void EndAttackIdleState();

	//跳跃相关函数
	void Jump();
};
