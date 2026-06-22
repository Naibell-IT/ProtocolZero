// (C) Naibell


#include "Sparker.h"

// Sets default values
ASparker::ASparker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

// Called when the game starts or when spawned
void ASparker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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

