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

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AMainCharacter::StartRunning);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMainCharacter::StopRunning);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMainCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMainCharacter::StopCrouch);
	}

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

void AMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D look_vector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(look_vector.X);
		AddControllerPitchInput(look_vector.Y);
	}
}

void AMainCharacter::StartRunning(const FInputActionValue& Value)
{
	if (movement_state == EPlayerMovementState::Walking)
	{
		movement_state = EPlayerMovementState::Running;
		GetCharacterMovement()->MaxWalkSpeed = DefaultRunSpeed;
	}
}

void AMainCharacter::StopRunning(const FInputActionValue& Value)
{
	if (movement_state == EPlayerMovementState::Running)
	{
		movement_state = EPlayerMovementState::Walking;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

void AMainCharacter::StartCrouch(const FInputActionValue& Value)
{
	if (movement_state == EPlayerMovementState::Walking)
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

