// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "QuestSystem.h"
#include "InteractComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Weapons/WeaponBase.h"
#include "MainCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveWeaponChange, AWeaponBase*, weapon_ptr);


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
	FORCEINLINE float GetStamina();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EPlayerMovementState GetCurrentMovementState();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool GetIsAiming();
	UFUNCTION()
	FORCEINLINE void OnPickUpIDCard();
	UFUNCTION()
	FORCEINLINE bool GetIsHaveIDCard();

	UFUNCTION(BlueprintCallable)
	void BlockControl();
	UFUNCTION(BlueprintCallable)
	void UnblockControl();
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
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ExitUIAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ToggleFlashlightAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AimAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ReloadAction;
public:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* Flashlight;
	UPROPERTY(EditDefaultsOnly)
	UQuestSystem* QuestSystemComponent;
	UPROPERTY(EditDefaultsOnly)
	UInteractComponent* InteractComponent;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* HandsMesh;
	UPROPERTY(BlueprintAssignable)
	FOnUIExit OnUIExit;
	UPROPERTY(BlueprintAssignable)
	FOnActiveWeaponChange OnActiveWeaponChange;
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
	UFUNCTION(BlueprintCallable)
	void Interact(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void ExitUI(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void ToggleFlashlight(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StartFire(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void EndFire(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void StartAiming(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void EndAimingAction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Reload(const FInputActionValue& Value);

	UFUNCTION()
	void SetPrimaryWeapon(AWeaponBase* weapon);
	UFUNCTION()
	void SetSecondaryWeapon(AWeaponBase* weapon);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWeaponBase* GetPrimaryWeapon();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWeaponBase* GetSecondaryWeapon();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWeaponBase* GetCurrentWeapon();
	UFUNCTION()
	void OnSigleFire();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float DefaultWalkSpeed = 500;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float DefaultRunSpeed = 650;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float DefaultCrouchSpeed = 300;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float MaxStamina = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float StaminaConsumptionPerCall = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float StaminaRecoveryPerCall = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float StaminaConsumptionTimerDelay = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float StaminaRecoveryTimerDelay = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Settings", BlueprintReadOnly)
	float AimSlowing = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Flashlight Settings")
	float FlashlightLagSpeed = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	TSubclassOf<UCameraShakeBase> RunShakeClass;
	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	TSubclassOf<UCameraShakeBase> WalkShakeClass;
	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	TSubclassOf<UCameraShakeBase> SparkerFireShakeClass;

	UPROPERTY()
	UCameraShakeBase* ActiveRunShake;

	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	float RunCameraOffset = -15.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera | Effects")
	float CameraLeanSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Camera | Aiming")
	float AimFOV = 65;

	UPROPERTY(EditAnywhere, Category = "Camera | Aiming")
	float AimZoomSpeed = 12;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Animations")
	UAnimMontage* HipFireMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Animations")
	UAnimMontage* AimFireMontage;

private:
	EPlayerMovementState movement_state;
	float default_camera_z;
	float targer_camera_z;
	float current_camera_z;
	float current_stamina;
	float default_fov = 90;

	bool bIsControlBlocked = false;
	bool bIsHaveIDCard = false;
	bool bIsAiming = false;

	AWeaponBase* primary_weapon;
	AWeaponBase* secondary_weapon;
	AWeaponBase* current_weapon;

private:
	FTimerHandle consumpt_stamina_handle;
	FTimerHandle recovery_stamina_handle;
	void ConsuptStamina();
	void RecoveryStamina();
	void EndAiming();
	void SetCurrentWeapon(AWeaponBase* weapon);
};
