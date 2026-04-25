// (C) Naibell


#include "AutoDoorController.h"

AAutoDoorController::AAutoDoorController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAutoDoorController::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &AAutoDoorController::OnOverlap);
    OnActorEndOverlap.AddDynamic(this, &AAutoDoorController::OnOverlap);
}

void AAutoDoorController::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (LeftDoor && RightDoor)
    {
        LeftDoor->DoorInteract();
        RightDoor->DoorInteract();
    }
}
