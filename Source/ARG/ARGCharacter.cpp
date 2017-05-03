//2017/04/27
//by Chao

#include "ARG.h"
#include "ARGCharacter.h"


// Sets default values
AARGCharacter::AARGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// 游戏开始调用
void AARGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// 每帧调用
void AARGCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// 绑定输入函数
void AARGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//bind前后左右移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AARGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARGCharacter::MoveRight);
	//bind上下左右旋转
	PlayerInputComponent->BindAxis("TurnArround", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void AARGCharacter::MoveForward(float val) 
{
	if (val != 0.f) 
	{
		//判断向哪是往前,Yaw导航
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//获取向前向量
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		//移动
		AddMovementInput(direction, val);
	}
}

void AARGCharacter::MoveRight(float val)
{
	if (val != 0.f)
	{
		//判断向哪是往前,Yaw导航
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//获取向前向量
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		//移动
		AddMovementInput(direction, val);
	}
}


