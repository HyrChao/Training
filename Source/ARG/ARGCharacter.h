//2017/04/27
//by Chao
#pragma once

#include "GameFramework/Character.h"
#include "ARGCharacter.generated.h"

UCLASS()
class ARG_API AARGCharacter : public ACharacter
{
	GENERATED_BODY()

	//摄像机碰撞
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))//属性显示
	class USpringArmComponent* cameraBoom;

	//相机跟随
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;


public:

	// 绑定输入函数
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 构造函数
	AARGCharacter();

	
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
		bool GetAttackState() const { return presseAttack; }

	//设置攻击状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		void SetAttackState(bool state) { presseAttack =state;}

	//获取魔法状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		bool GetMagicState() const { return presseMagic; }

	//设置魔法状态
	UFUNCTION(BlueprintCallable, Category = "ARGCharacter")
		void SetMagicState(bool state) { presseMagic = state; }
protected:

	// 游戏开始调用
	virtual void BeginPlay() override;

	//攻击相关

	void Attack();

	void Magic();

	void ReleaseAttack();

	void ReleaseMagic();

	//移动相关

	void Walk();

	void StopWalking();

	void MoveForward(float val);

	void MoveRight(float val);	

	//视角相关

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

private:

	bool presseAttack;

	bool presseMagic;

	float walkRatio;



};
