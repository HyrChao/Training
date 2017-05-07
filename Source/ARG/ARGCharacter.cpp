//2017/05/05
//by Chao

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

	////��������ת��ʱ��ֹ��ɫת��ʹ��ֻӰ�����.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	////���ý�ɫ���ƶ�
	GetCharacterMovement()->bOrientRotationToMovement = true; //��ɫ��������ķ���
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...ʹ�������ת��
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//���������ײ(������ײ��������ɫ)
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f; //����ڽ�ɫ���ľ���	
	cameraBoom->bUsePawnControlRotation = true; //��ת���ڿ���������ת��

	//�����������
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); //��������������ײ������һ�㼶������ײ�������䷽λ
	followCamera->bUsePawnControlRotation = false; //�����ת�����ڿ���������ת��
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//����
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AARGCharacter::Walk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AARGCharacter::StopWalking);

	//����
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AARGCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AARGCharacter::ReleaseAttack);
	PlayerInputComponent->BindAction("Magic", IE_Pressed, this, &AARGCharacter::Magic);
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



}

//�������

void AARGCharacter::Attack()
{
	presseAttack = true;
}

void AARGCharacter::Magic()
{
	presseMagic = true;
}

void AARGCharacter::ReleaseAttack()
{
	presseAttack = false;
}

void AARGCharacter::ReleaseMagic()
{
	presseMagic = false;
}

//�ƶ����

void AARGCharacter::MoveForward(float val) 
{

	if ((Controller != nullptr) && (val != 0.0f))
	{
		//�ж���������ǰ,Yaw����
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//��ȡ��ǰ����
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		//FVector direction = GetActorForwardVector();
		//�ƶ�
		AddMovementInput(direction, val*walkRatio);
	}
}

void AARGCharacter::MoveRight(float val)
{

	if ((Controller != nullptr) && (val != 0.0f))
	{
		//�ж���������ǰ,Yaw����
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//��ȡ��ǰ����
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		//FVector direction = GetActorRightVector();
		//�ƶ�
		AddMovementInput(direction, val*walkRatio);
	}
}

void AARGCharacter::Walk()
{
	walkRatio = 0.24f;
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



