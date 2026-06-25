// (C) Naibell


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Equip()
{
}
void AWeaponBase::StartFire()
{
}
void AWeaponBase::EndFire()
{
}
void AWeaponBase::Fire()
{
}
void AWeaponBase::Reload()
{
}

int32 AWeaponBase::GetCurrentAmmo()
{
	return CurrentFreeAmmo;
}

int32 AWeaponBase::GetClipAmmo()
{
	return CurrentClipAmmo;
}
