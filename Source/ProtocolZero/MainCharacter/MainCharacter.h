// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROTOCOLZERO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;
public:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;
public:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float DefaultWalkSpeed = 500;
};
