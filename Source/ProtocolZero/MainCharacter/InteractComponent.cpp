// (C) NAgames

#include "InteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetWorld()->GetTimerManager().SetTimer(CheckInteractHandle, this, &UInteractComponent::CheckInteract, 0.1f, true, 0);
}

void UInteractComponent::OnInteract()
{
	if (hit_actor && is_can_interact)
	{
		IInteractable::Execute_Interact(hit_actor, character);
	}
}

void UInteractComponent::CheckInteract()
{
	if (!character)
		return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!(PC && PC->PlayerCameraManager))
		return;
	
	FVector camera_pos = PC->PlayerCameraManager->GetCameraLocation();
	FVector camera_rotation = PC->PlayerCameraManager->GetCameraRotation().Vector();

	const FVector start_pos = camera_pos;
	const FVector end_pos = start_pos + (camera_rotation * InteractTraceLenght);

	FHitResult hit_result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(character);

	if (GetWorld()->LineTraceSingleByChannel(hit_result, start_pos, end_pos, ECC_WorldStatic, params))
	{

		if (AActor* hitted_actor = hit_result.GetActor())
		{

			if (hitted_actor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{

				hit_actor = hitted_actor;
				if (!is_can_interact)
				{
					is_can_interact = true;
					OnInteractUpdate.Broadcast(is_can_interact, hit_actor);
				}

			}
			else if (is_can_interact)
			{
				is_can_interact = false;
				OnInteractUpdate.Broadcast(is_can_interact, hit_actor);
				hit_actor = nullptr;
			}
		}
	}
	else if (is_can_interact)
	{
		is_can_interact = false;
		OnInteractUpdate.Broadcast(is_can_interact, hit_actor);
		hit_actor = nullptr;
	}
}

