// (C) Naibell


#include "Sparker.h"
#include "../MainCharacter/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

ASparker::ASparker()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SocketName = FName(TEXT("WeaponSocket"));
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
	if (AMainCharacter* character = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		WeaponMesh->SetSimulatePhysics(false);

		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(character->HandsMesh, AttachmentRules, SocketName);

		character->SetPrimaryWeapon(this);
	}
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

