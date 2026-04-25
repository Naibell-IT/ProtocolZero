// (C) Naibell

#include "ProtectedDoor.h"

AProtectedDoor::AProtectedDoor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AProtectedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProtectedDoor::BeginPlay()
{
	Super::BeginPlay();
}

void AProtectedDoor::DoorInteract()
{
	if (!is_open)
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Blue, FString::Printf(TEXT("Open Door ads")));
		TranslateOpenDoor(DoorMesh->GetRelativeLocation(), x_translation);
		is_open = true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Blue, FString::Printf(TEXT("Close Door ads")));
		CloseDoor();
		is_open = false;
	}
}

