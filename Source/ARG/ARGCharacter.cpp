//2017/05/05
//by Chao
//��ɫ��Ϊ���ɫ����

#include "ARG.h"
#include "ARGCharacter.h"


//���캯����ʼ������
AARGCharacter::AARGCharacter()
{
 	//����ÿ֡���õ�Tick()����
	PrimaryActorTick.bCanEverTick = true;

	//��������ϵ��
	walkRatio = 1.0f;

	//�������ת���ʳ�ʼֵ
	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;
	basePlayerTurnRate =0.1f;


	////��������ת��ʱ��ֹ��ɫת��ʹ��ֻӰ�����.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	////���ý�ɫ���ƶ�
	GetCharacterMovement()->bOrientRotationToMovement = true; //��ɫ��������ķ���
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...ʹ�������ת��
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//���������󶨲��
	sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	sword->SetupAttachment(GetMesh(),TEXT("Cup_RSocket_Sword"));//����������ɫ��Cup_RSocket_Sword�����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _sword(TEXT("StaticMesh'/Game/Character/Mesh/Sword_A.Sword_A'"));//��ȡ���ľ�������
	if (_sword.Succeeded())
		sword->SetStaticMesh(_sword.Object);//������ָ���ڽ�

	//���������ײ(������ײ��������ɫ)
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f; //����ڽ�ɫ���ľ���	
	cameraBoom->bUsePawnControlRotation = true; //��ת���ڿ���������ת��

	//�����������
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); //��������������ײ������һ�㼶������ײ�������䷽λ
	followCamera->bUsePawnControlRotation = false; //�����ת�����ڿ���������ת��

	//����ֵ��ʼ��
	attackIdleState = false;
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
	PlayerInputComponent->BindAxis("TurnArround", this, &APawn::AddControllerYawInput);//��ת����꣩
	PlayerInputComponent->BindAxis("TurnArroundRate", this, &AARGCharacter::TurnAtRate);//��ת������꣩
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AARGCharacter::LookUpAtRate);

	//��Ծ
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AARGCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//����
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AARGCharacter::Walk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AARGCharacter::StopWalking);

	//����
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AARGCharacter::PresseAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AARGCharacter::ReleaseAttack);
	PlayerInputComponent->BindAction("Magic", IE_Pressed, this, &AARGCharacter::PresseMagic);
	PlayerInputComponent->BindAction("Magic", IE_Released, this, &AARGCharacter::ReleaseMagic);



}

// ��Ϸ��ʼ����
void AARGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// ÿ֡����
void AARGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//isAttacking = false;
	//usingMagic = false;

}

void AARGCharacter::Jump()
{
	if(!isAttacking)
		ACharacter::Jump();
}

//�������

void AARGCharacter::Attack()
{
	isAttacking = true;
}

void AARGCharacter::Magic()
{
	usingMagic = true;
}

void AARGCharacter::PresseAttack()
{
	presseAttack = true;
	if(!bWasJumping)
		isAttacking = true;
}

void AARGCharacter::PresseMagic()
{
	presseMagic = true;
	if (!bWasJumping)
		usingMagic = true;
}

void AARGCharacter::ReleaseAttack()
{
	presseAttack = false;
}

void AARGCharacter::ReleaseMagic()
{
	presseMagic = false;
}

void AARGCharacter::EndAttack() 
{
	isAttacking = false;
}

void AARGCharacter::EndMagic()
{
	usingMagic = false;
}

//�ƶ����

void AARGCharacter::MoveForward(float val) 
{
	xAxis = val;//���汾�ε���ʱ��Xaxis
	if (val != 0.0f)
	{
		FVector direction = GetActorForwardVector();
		//�ƶ�
		if (val > 0) 
		{
			bUseControllerRotationYaw = false;
			//controller->AddInputVector(direction*val*walkRatio);
			//����MovementComponent���Ż��ٶȣ��˺��������ת90��
			Internal_AddMovementInput(direction*val*walkRatio);//�˺��������ת90�ȣ��������ں���
		}
		else
		{
			bUseControllerRotationYaw = true;//ʹ��ɫ��ת�����
			Internal_AddMovementInput(direction*val*0.35f);
		}
	}
	else
		bUseControllerRotationYaw = false;

}

void AARGCharacter::MoveRight(float val)
{
	yAxis = val;//���汾�ε���ʱ��Yaxis
	if (val != 0.0f)
	{
		//�����ں���״̬�������л�Ϊת���ӽ�
		if (bUseControllerRotationYaw)
		{
			AddControllerYawInput(val * baseTurnRate*-0.5f * GetWorld()->GetDeltaSeconds());
		}
		else
		{
			FVector direction = GetActorRightVector();
			//�ƶ�
			//controller->AddInputVector(direction*val*walkRatio);
			Internal_AddMovementInput(direction*val*walkRatio*basePlayerTurnRate);
			//������ƶ�
			AddControllerYawInput(val*walkRatio *85.f*GetWorld()->GetDeltaSeconds());
		}
	}

}

void AARGCharacter::Walk()
{
	walkRatio = 0.38f;
}

void AARGCharacter::StopWalking()
{
	walkRatio = 1.0f;
}

//�ӽ����

void AARGCharacter::TurnAtRate(float rate)
{
	if(rate!=0.f)
	//��rate�����֡���
	AddControllerYawInput(rate * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AARGCharacter::LookUpAtRate(float rate)
{
	if (rate!=0.f)
	//��rate�����֡���
	AddControllerPitchInput(rate * baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AARGCharacter::EnterAttackIdleState()
{
	attackIdleState = true;
	GetWorldTimerManager().SetTimer(Timer, this, &AARGCharacter::EndAttackIdleState, 0.8f /*Time you want*/, false /*if you want loop set to true*/);//��ʱ��ʼ�Ժ�XX����ú�������������Ϊtrue��ѭ��
	//GetWorldTimerManager().ClearTimer(Timer);
	//GetWorldTimerManager().ClearTimer(attackTimer);����ʱ��ѭ��ִ�У��ô˺�����ֹ
}

void AARGCharacter::EndAttackIdleState()
{
	attackIdleState = false;
}

//���ܺ���
//void AARGCharacter::DoOnce(PlayerAction act)
//{
//	if (canDoOnce)
//	{
//		canDoOnce = false;
//		switch (act) 
//		{
//		case Attack1:
//			Attack();
//			if (GEngine)
//				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("canDoOnce"));
//			break;
//		case Magic1:
//			Magic();
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//void AARGCharacter::ResetDoOnce()
//{
//	canDoOnce = true;
//}
	

