//2017/05/05
//by Chao

#include "ARG.h"
#include "ARGCharacter.h"


//���캯����ʼ������
AARGCharacter::AARGCharacter()
{
 	//����ÿ֡���õ�Tick()����
	PrimaryActorTick.bCanEverTick = true;

	//�������ת���ʳ�ʼֵ
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	//��������ת��ʱ��ֹ��ɫת��ʹ��ֻӰ�����.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//���ý�ɫ���ƶ�
	GetCharacterMovement()->bOrientRotationToMovement = true; //��ɫ��������ķ���
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...ʹ�������ת��
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//���������ײ(������ײ��������ɫ)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; //����ڽ�ɫ���ľ���	
	CameraBoom->bUsePawnControlRotation = true; //��ת���ڿ���������ת��

	//�����������
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); //��������������ײ������һ�㼶������ײ�������䷽λ
	FollowCamera->bUsePawnControlRotation = false; //�����ת�����ڿ���������ת��
}

// �����뺯��
void AARGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//��Ծ
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//bindǰ�������ƶ�
	PlayerInputComponent->BindAxis("MoveForward", this, &AARGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARGCharacter::MoveRight);
	//bind����������ת
	PlayerInputComponent->BindAxis("TurnArround", this, &APawn::AddControllerYawInput);//��ת����꣩
	PlayerInputComponent->BindAxis("TurnArroundRate", this, &AARGCharacter::TurnAtRate);//��ת������꣩

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AARGCharacter::LookUpAtRate);


}

// ��Ϸ��ʼ����
void AARGCharacter::BeginPlay()
{
	//Super::BeginPlay();
	
}

// ÿ֡����
void AARGCharacter::Tick( float DeltaTime )
{
	//Super::Tick( DeltaTime );

}


void AARGCharacter::MoveForward(float val) 
{

	if ((Controller != NULL) && (val != 0.0f))
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("MoveForward"));
		}
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

	if ((Controller != NULL) && (val != 0.0f))
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("MoveRight"));
		}
		//�ж���������ǰ,Yaw����
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//��ȡ��ǰ����
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		//�ƶ�
		AddMovementInput(direction, val);
	}
}

void AARGCharacter::TurnAtRate(float Rate)
{
	//��rate�����֡���
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AARGCharacter::LookUpAtRate(float Rate)
{
	//��rate�����֡���
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



