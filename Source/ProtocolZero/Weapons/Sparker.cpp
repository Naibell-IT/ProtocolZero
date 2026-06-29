// (C) Naibell


#include "Sparker.h"
#include "Kismet/GameplayStatics.h"

ASparker::ASparker()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SocketName = FName(TEXT("WeaponSocket"));
	WeaponType = EPlayerAvailableWeapons::Sparker;
	MuzzleFlashlight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MuzzleFlashlight"));

	MuzzleFlashlight->SetupAttachment(WeaponMesh);

	BodyDamage = 35;
	HeadDamage = 100;
	MaxClipAmmo = 5;
	MaxAmmo = 100;
	FireRange = 1000;
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

		CurrentClipAmmo = 5;
		CurrentFreeAmmo = 25;
		character->SetPrimaryWeapon(this);
		player = character;
	}
}

void ASparker::UnblockShootingReload()
{
	is_shooting_blocked = false;
	is_reloading = false;
	OnAmmoChanged.Broadcast(CurrentClipAmmo, CurrentFreeAmmo);
}

void ASparker::UnblockShootFire()
{
	if (!is_reloading)
		is_shooting_blocked = false;
}

void ASparker::TurnOffMuzzleLight()
{
	MuzzleFlashlight->SetVisibility(false);
}

void ASparker::StartFire()
{
	Fire();
}

void ASparker::EndFire()
{
}

void ASparker::Fire()
{
	if (CurrentClipAmmo < 1 || is_shooting_blocked)
		return;

	CurrentClipAmmo--;
	OnAmmoChanged.Broadcast(CurrentClipAmmo, CurrentFreeAmmo);
	
	if (player)
		player->OnSingleFire();

	FVector end_pos = CastTrace();
	ShowShootVFX(end_pos);

	is_shooting_blocked = true;
	GetWorldTimerManager().SetTimer(FireBlockTimerHandle, this, &ASparker::UnblockShootFire, ManualShootingCooldown, false);
}

void ASparker::Reload()
{
	if (CurrentClipAmmo == MaxClipAmmo || CurrentFreeAmmo == 0 || is_reloading)
		return;
	
	is_reloading = true;
	float ammo_to_reload = MaxClipAmmo - CurrentClipAmmo;
	
	if (CurrentFreeAmmo < ammo_to_reload)
		ammo_to_reload = CurrentFreeAmmo;

	CurrentFreeAmmo -= ammo_to_reload;
	CurrentClipAmmo += ammo_to_reload;

	player->OnReload();

	is_shooting_blocked = true;
	GetWorldTimerManager().SetTimer(ReloadBlockTimerHandle, this, &ASparker::UnblockShootingReload, ReloadTime, false);
}


FVector ASparker::CastTrace()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!(PC && PC->PlayerCameraManager))
		return FVector::ZeroVector;

	FVector camera_pos = PC->PlayerCameraManager->GetCameraLocation();
	FVector camera_rotation = PC->PlayerCameraManager->GetCameraRotation().Vector();

	const FVector start_pos = camera_pos;
	const FVector end_pos = start_pos + (camera_rotation * FireRange);


	FHitResult hit_result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	if (GetWorld()->LineTraceSingleByChannel(hit_result, start_pos, end_pos, ECC_WorldStatic, params))
	{
		if (AActor* hitted_actor = hit_result.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Blue, FString::Printf(TEXT("%s"), *hitted_actor->GetName()));
		}
		return hit_result.ImpactPoint;
	}
	return end_pos;
}

void ASparker::ShowShootVFX(FVector beam_end_pos)
{
	FVector beam_start_pos = WeaponMesh->GetSocketLocation(TEXT("Muzzle"));

	if (ElectricBeamSystem)
	{
		UNiagaraComponent* beam_comp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ElectricBeamSystem,
			beam_start_pos,
			FRotator::ZeroRotator
		);

		if (beam_comp)
		{
			beam_comp->SetNiagaraVariableVec3(FString("User.BeamEnd"), beam_end_pos);
		}
	}
	GetWorldTimerManager().ClearTimer(FlashlightTimerHandle);

	MuzzleFlashlight->SetVisibility(true);
	MuzzleFlashlight->SetWorldLocation(beam_start_pos);
	
	GetWorldTimerManager().SetTimer(FlashlightTimerHandle, this, &ASparker::TurnOffMuzzleLight, FlashDuration, false);
}

void ASparker::Interact_Implementation(const AActor* initiator)
{
	Equip();
}

FString ASparker::GetThingDescription_Implementation()
{
	return ThingDescription;
}

