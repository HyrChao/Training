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
	class USpringArmComponent* CameraBoom;

	//相机跟随
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// 构造函数
	AARGCharacter();

	// 游戏开始调用
	virtual void BeginPlay() override;
	
	// 每帧调用
	virtual void Tick( float DeltaSeconds ) override;

	//基础转向率, 单位度每秒
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	//基础俯视&仰视率, 单位度每秒
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//返回CameraBoom subobject子对象
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }//FORCEINLINE宏强制转换函数为内联
	//返回FollowCamera子对象
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


protected:

	// 绑定输入函数
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float val);

	void MoveRight(float val);	

	void TurnArround(float val);

	void LookUp(float val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

};
