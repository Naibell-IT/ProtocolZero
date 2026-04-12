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
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetStamina();
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
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;
public:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;
public:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StartMoving(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void EndMoving(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StartRunning(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StopRunningAction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StopRunning();
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
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float MaxStamina = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float StaminaConsumptionPerCall = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float StaminaRecoveryPerCall = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float StaminaConsumptionTimerDelay = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings")
	float StaminaRecoveryTimerDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	TSubclassOf<UCameraShakeBase> RunShakeClass;
	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	TSubclassOf<UCameraShakeBase> WalkShakeClass;

	UPROPERTY()
	UCameraShakeBase* ActiveRunShake;

	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	float RunCameraOffset = -15.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	float CameraLeanSpeed = 5.0f;

private:
	EPlayerMovementState movement_state;
	float default_camera_z;
	float targer_camera_z;
	float current_camera_z;
	float current_stamina;
private:
	FTimerHandle consumpt_stamina_handle;
	FTimerHandle recovery_stamina_handle;
	void ConsuptStamina();
	void RecoveryStamina();

};
