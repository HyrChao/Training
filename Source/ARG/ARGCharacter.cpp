//2017/05/05
//by Chao

#include "ARG.h"
#include "ARGCharacter.h"


//构造函数初始化参数
AARGCharacter::AARGCharacter()
{
 	//启用每帧调用的Tick()函数
	PrimaryActorTick.bCanEverTick = true;

	//设置相机转向率初始值
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	//当控制器转向时禁止角色转向，使其只影响相机.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//设置角色的移动
	GetCharacterMovement()->bOrientRotationToMovement = true; //角色移向输入的方向
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...使用这个旋转率
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//创建相机碰撞(若有碰撞拉近至角色)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; //相机在角色身后的距离	
	CameraBoom->bUsePawnControlRotation = true; //旋转基于控制器的旋转臂

	//创建跟随相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); //将相机置于相机碰撞器的下一层级并让碰撞器控制其方位
	FollowCamera->bUsePawnControlRotation = false; //相机旋转不基于控制器的旋转臂
}

// 绑定输入函数
void AARGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//跳跃
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//bind前后左右移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AARGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARGCharacter::MoveRight);
	//bind上下左右旋转
	PlayerInputComponent->BindAxis("TurnArround", this, &APawn::AddControllerYawInput);//旋转（鼠标）
	PlayerInputComponent->BindAxis("TurnArroundRate", this, &AARGCharacter::TurnAtRate);//旋转（非鼠标）

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AARGCharacter::LookUpAtRate);


}

// 游戏开始调用
void AARGCharacter::BeginPlay()
{
	//Super::BeginPlay();
	
}

// 每帧调用
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

	if ((Controller != NULL) && (val != 0.0f))
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("MoveRight"));
		}
		//判断向哪是往前,Yaw导航
		const FRotator rotation = GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		//获取向前向量
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		//移动
		AddMovementInput(direction, val);
	}
}

void AARGCharacter::TurnAtRate(float Rate)
{
	//由rate计算该帧间隔
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AARGCharacter::LookUpAtRate(float Rate)
{
	//由rate计算该帧间隔
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



