// (C) Naibell


#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(0, 0, 60));
	Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;

	PrimaryActorTick.bCanEverTick = true;

	current_stamina = MaxStamina;

	QuestSystemComponent = CreateDefaultSubobject<UQuestSystem>(TEXT("Quest System"));
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("Interact Component"));
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	current_camera_z = default_camera_z = Camera->GetRelativeLocation().Z;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool is_running = !GetCharacterMovement()->Velocity.IsZero();
	targer_camera_z = is_running ? (default_camera_z + RunCameraOffset) : default_camera_z;

	current_camera_z = FMath::FInterpTo(current_camera_z, targer_camera_z, DeltaTime, CameraLeanSpeed);

	FVector new_location = Camera->GetRelativeLocation();
	new_location.Z = current_camera_z;
	Camera->SetRelativeLocation(new_location);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMainCharacter::StartMoving);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMainCharacter::EndMoving);
	
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AMainCharacter::StartRunning);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMainCharacter::StopRunningAction);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMainCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMainCharacter::StopCrouch);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AMainCharacter::Interact);

		EnhancedInputComponent->BindAction(ExitUIAction, ETriggerEvent::Completed, this, &AMainCharacter::ExitUI);
	}

}

float AMainCharacter::GetStamina()
{
	return current_stamina;
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D move_vector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yaw_rotation(0, rotation.Yaw, 0);
		const FVector forward_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
		const FVector right_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(forward_direction, move_vector.Y);
		AddMovementInput(right_direction, move_vector.X);
	}
}

void AMainCharacter::StartMoving(const FInputActionValue& Value)
{
	if (bIsControlBlocked)
		return;
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (movement_state == EPlayerMovementState::Running)
			ActiveRunShake = PC->PlayerCameraManager->StartCameraShake(RunShakeClass);
		else
			ActiveRunShake = PC->PlayerCameraManager->StartCameraShake(WalkShakeClass);
	}
}

void AMainCharacter::EndMoving(const FInputActionValue& Value)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->PlayerCameraManager->StopAllCameraShakes(true);
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D look_vector = Value.Get<FVector2D>();

	if (Controller && !bIsControlBlocked)
	{
		AddControllerYawInput(look_vector.X);
		AddControllerPitchInput(look_vector.Y);
	}
}

void AMainCharacter::StartRunning(const FInputActionValue& Value)
{
	if (movement_state == EPlayerMovementState::Walking && current_stamina >= StaminaConsumptionPerCall && !bIsControlBlocked)
	{
		movement_state = EPlayerMovementState::Running;
		GetCharacterMovement()->MaxWalkSpeed = DefaultRunSpeed;

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (ActiveRunShake && !GetCharacterMovement()->Velocity.IsZero())
			{
				PC->PlayerCameraManager->StopCameraShake(ActiveRunShake, true);
				ActiveRunShake = PC->PlayerCameraManager->StartCameraShake(RunShakeClass);
			}
		}
		if (!GetCharacterMovement()->Velocity.IsZero())
			GetWorldTimerManager().ClearTimer(recovery_stamina_handle);
		GetWorldTimerManager().SetTimer(consumpt_stamina_handle, this, &AMainCharacter::ConsuptStamina, StaminaConsumptionTimerDelay, true);
	}
}

void AMainCharacter::StopRunningAction(const FInputActionValue& Value)
{
	StopRunning();
}

void AMainCharacter::StopRunning()
{
	if (movement_state == EPlayerMovementState::Running)
	{
		movement_state = EPlayerMovementState::Walking;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (ActiveRunShake)
			{
				PC->PlayerCameraManager->StopCameraShake(ActiveRunShake, true);
				if (!GetCharacterMovement()->Velocity.IsZero())
					ActiveRunShake = PC->PlayerCameraManager->StartCameraShake(WalkShakeClass);
			}
		}
		GetWorldTimerManager().ClearTimer(consumpt_stamina_handle);
		GetWorldTimerManager().SetTimer(recovery_stamina_handle, this, &AMainCharacter::RecoveryStamina, StaminaRecoveryTimerDelay, true);
	}
}

void AMainCharacter::StartCrouch(const FInputActionValue& Value)
{
	if (movement_state == EPlayerMovementState::Walking && !GetCharacterMovement()->IsFalling() && !bIsControlBlocked)
	{
		movement_state = EPlayerMovementState::Crouching;
		GetCharacterMovement()->MaxWalkSpeed = DefaultCrouchSpeed;
		Crouch();
	}
}

void AMainCharacter::StopCrouch(const FInputActionValue& Value)
{
	if (movement_state == EPlayerMovementState::Crouching)
	{
		movement_state = EPlayerMovementState::Walking;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
	UnCrouch();
}

void AMainCharacter::Interact(const FInputActionValue& Value)
{
	if (InteractComponent && !bIsControlBlocked)
	{
		InteractComponent->OnInteract();
	}
}

void AMainCharacter::ExitUI(const FInputActionValue& Value)
{
	OnUIExit.Broadcast();
}

void AMainCharacter::ConsuptStamina()
{
	if (current_stamina <= 0)
		StopRunning();
	else if (!GetCharacterMovement()->Velocity.IsZero()) current_stamina -= StaminaConsumptionPerCall;
}

void AMainCharacter::RecoveryStamina()
{
	if (current_stamina >= MaxStamina)
	{
		GetWorldTimerManager().ClearTimer(recovery_stamina_handle);
		current_stamina = MaxStamina;
	}
	else current_stamina += StaminaRecoveryPerCall;
}

void AMainCharacter::OnPickUpIDCard()
{
	bIsHaveIDCard = true;
}

bool AMainCharacter::GetIsHaveIDCard()
{
	return bIsHaveIDCard;
}

void AMainCharacter::BlockControl()
{
	bIsControlBlocked = true;
}

void AMainCharacter::UnblockControl()
{
	bIsControlBlocked = false;
}
