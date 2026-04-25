// (C) Naibell


#include "CardTerminal.h"
#include "Kismet/GameplayStatics.h"

ACardTerminal::ACardTerminal()
{
	PrimaryActorTick.bCanEverTick = false;
	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Terminal Mesh"));
}

void ACardTerminal::BeginPlay()
{
	Super::BeginPlay();
	if (AMainCharacter* casted_character = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		character = casted_character;
}

void ACardTerminal::Interact_Implementation(const AActor* initiator)
{
	if (character && character->GetIsHaveIDCard() && LinkedDoor)
		LinkedDoor->DoorInteract();
}

FString ACardTerminal::GetThingDescription_Implementation()
{
	return ThingDescription;
}

