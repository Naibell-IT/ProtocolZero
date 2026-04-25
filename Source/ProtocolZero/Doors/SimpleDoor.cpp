// (C) Naibell


#include "SimpleDoor.h"

// Sets default values
ASimpleDoor::ASimpleDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimpleDoor::Interact_Implementation(const AActor* initiator)
{
	if (!is_open)
	{
		RotateOpenDoor(DoorMesh->GetRelativeRotation(), RotationYaw);
		is_open = true;
	}
	else
	{
		CloseDoor();
		is_open = false;
	}
}

FString ASimpleDoor::GetThingDescription_Implementation()
{
	return FString(TEXT(""));
}

