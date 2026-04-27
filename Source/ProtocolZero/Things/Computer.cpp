// (C) Naibell


#include "Computer.h"

AComputer::AComputer()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer Mesh"));
	Tags.Add(FName(TEXT("Computer")));
}

void AComputer::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FMail> AComputer::GetMails()
{
	return Mails;
}

void AComputer::Interact_Implementation(const AActor* initiator)
{
	OnComputerOpen.Broadcast(Mails);
}

FString AComputer::GetThingDescription_Implementation()
{
	return FString(TEXT("Компьютер"));
}


