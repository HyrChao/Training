//2017/05/05
//by Chao
//角色行为与角色控制

#include "ARG.h"
#include "ARGCharacter.h"


//构造函数初始化参数
AARGCharacter::AARGCharacter()
{
 	//启用每帧调用的Tick()函数
	PrimaryActorTick.bCanEverTick = true;

	//设置行走系数
	walkRatio = 1.0f;

	//设置相机转向率初始值
	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;
	basePlayerTurnRate =0.1f;


	////当控制器转向时禁止角色转向，使其只影响相机.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	////设置角色的移动
	GetCharacterMovement()->bOrientRotationToMovement = true; //角色移向输入的方向
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...使用这个旋转率
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//创建剑并绑定插槽
	sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	sword->SetupAttachment(GetMesh(),TEXT("Cup_RSocket_Sword"));//将剑绑定至角色的Cup_RSocket_Sword插槽上
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _sword(TEXT("StaticMesh'/Game/Character/Mesh/Sword_A.Sword_A'"));//获取剑的具体网格
	if (_sword.Succeeded())
		sword->SetStaticMesh(_sword.Object);//将网格指定于剑

	//创建相机碰撞(若有碰撞拉近至角色)
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f; //相机在角色身后的距离	
	cameraBoom->bUsePawnControlRotation = true; //旋转基于控制器的旋转臂

	//创建跟随相机
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); //将相机置于相机碰撞器的下一层级并让碰撞器控制其方位
	followCamera->bUsePawnControlRotation = false; //相机旋转不基于控制器的旋转臂

	//杂项值初始化
	attackIdleState = false;
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
	PlayerInputComponent->BindAxis("TurnArround", this, &APawn::AddControllerYawInput);//旋转（鼠标）
	PlayerInputComponent->BindAxis("TurnArroundRate", this, &AARGCharacter::TurnAtRate);//旋转（非鼠标）
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AARGCharacter::LookUpAtRate);

	//跳跃
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AARGCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//奔跑
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AARGCharacter::Walk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AARGCharacter::StopWalking);

	//攻击
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AARGCharacter::PresseAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AARGCharacter::ReleaseAttack);
	PlayerInputComponent->BindAction("Magic", IE_Pressed, this, &AARGCharacter::PresseMagic);
	PlayerInputComponent->BindAction("Magic", IE_Released, this, &AARGCharacter::ReleaseMagic);



}

// 游戏开始调用
void AARGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// 每帧调用
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

//攻击相关

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

//移动相关

void AARGCharacter::MoveForward(float val) 
{
	xAxis = val;//储存本次调用时的Xaxis
	if (val != 0.0f)
	{
		FVector direction = GetActorForwardVector();
		//移动
		if (val > 0) 
		{
			bUseControllerRotationYaw = false;
			//controller->AddInputVector(direction*val*walkRatio);
			//跳过MovementComponent，优化速度，此函数最多旋转90度
			Internal_AddMovementInput(direction*val*walkRatio);//此函数最多旋转90度，不适用于后退
		}
		else
		{
			bUseControllerRotationYaw = true;//使角色不转向后退
			Internal_AddMovementInput(direction*val*0.35f);
		}
	}
	else
		bUseControllerRotationYaw = false;

}

void AARGCharacter::MoveRight(float val)
{
	yAxis = val;//储存本次调用时的Yaxis
	if (val != 0.0f)
	{
		//若处于后退状态，功能切换为转换视角
		if (bUseControllerRotationYaw)
		{
			AddControllerYawInput(val * baseTurnRate*-0.5f * GetWorld()->GetDeltaSeconds());
		}
		else
		{
			FVector direction = GetActorRightVector();
			//移动
			//controller->AddInputVector(direction*val*walkRatio);
			Internal_AddMovementInput(direction*val*walkRatio*basePlayerTurnRate);
			//摄像机移动
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

//视角相关

void AARGCharacter::TurnAtRate(float rate)
{
	if(rate!=0.f)
	//由rate计算该帧间隔
	AddControllerYawInput(rate * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AARGCharacter::LookUpAtRate(float rate)
{
	if (rate!=0.f)
	//由rate计算该帧间隔
	AddControllerPitchInput(rate * baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AARGCharacter::EnterAttackIdleState()
{
	attackIdleState = true;
	GetWorldTimerManager().SetTimer(Timer, this, &AARGCharacter::EndAttackIdleState, 0.8f /*Time you want*/, false /*if you want loop set to true*/);//计时开始以后XX秒调用函数，若最后参数为true则循环
	//GetWorldTimerManager().ClearTimer(Timer);
	//GetWorldTimerManager().ClearTimer(attackTimer);若定时器循环执行，用此函数终止
}

void AARGCharacter::EndAttackIdleState()
{
	attackIdleState = false;
}

//功能函数
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
	

