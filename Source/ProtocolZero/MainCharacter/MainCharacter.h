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

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	Walking,
	Running,
	Crouching
};


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
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CrouchAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* RunAction;
public:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;
public:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StartRunning(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StopRunning(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StartCrouch(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StopCrouch(const FInputActionValue& Value);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float DefaultWalkSpeed = 500;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float DefaultRunSpeed = 650;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float DefaultCrouchSpeed = 300;
private:
	EPlayerMovementState movement_state;
};
