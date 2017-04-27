//2017/04/27
//by Chao
#pragma once

#include "GameFramework/Character.h"
#include "ARGCharacter.generated.h"

UCLASS()
class ARG_API AARGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARGCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void MoveForward(float val);

	void MoveRight(float val);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
