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

// ��Ϸ��ʼ����
void AARGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// ÿ֡����
void AARGCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// �����뺯��
void AARGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//bindǰ�������ƶ�
	PlayerInputComponent->BindAxis("MoveForward", this, &AARGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARGCharacter::MoveRight);
	//bind����������ת
	PlayerInputComponent->BindAxis("TurnArround", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void AARGCharacter::MoveForward(float val) 
{
	if (val != 0.f) 
	{
		//�ж���������ǰ,Yaw����
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//��ȡ��ǰ����
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		//�ƶ�
		AddMovementInput(direction, val);
	}
}

void AARGCharacter::MoveRight(float val)
{
	if (val != 0.f)
	{
		//�ж���������ǰ,Yaw����
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//��ȡ��ǰ����
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		//�ƶ�
		AddMovementInput(direction, val);
	}
}


