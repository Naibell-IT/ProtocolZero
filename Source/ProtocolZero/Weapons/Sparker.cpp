// (C) Naibell


#include "Sparker.h"

ASparker::ASparker()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

void ASparker::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASparker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASparker::Equip()
{
}

void ASparker::StartFire()
{
}

void ASparker::EndFire()
{
}

void ASparker::Fire()
{
}

void ASparker::Reload()
{
}

void ASparker::Interact_Implementation(const AActor* initiator)
{
	Equip();
}

FString ASparker::GetThingDescription_Implementation()
{
	return ThingDescription;
}

