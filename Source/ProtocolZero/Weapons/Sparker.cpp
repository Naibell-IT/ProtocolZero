// (C) Naibell


#include "Sparker.h"
#include "Kismet/GameplayStatics.h"

ASparker::ASparker()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SocketName = FName(TEXT("WeaponSocket"));
	WeaponType = EPlayerAvailableWeapons::Sparker;

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

void ASparker::StartFire()
{
	Fire();
}

void ASparker::EndFire()
{
}

void ASparker::Fire()
{
	if (CurrentClipAmmo < 1)
		return;

	CurrentClipAmmo--;
	OnAmmoChanged.Broadcast(CurrentClipAmmo, CurrentFreeAmmo);
	
	if (player)
		player->OnSigleFire();

	CastTrace();
}

void ASparker::Reload()
{
}

void ASparker::CastTrace()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!(PC && PC->PlayerCameraManager))
		return;

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
	}
}

void ASparker::Interact_Implementation(const AActor* initiator)
{
	Equip();
}

FString ASparker::GetThingDescription_Implementation()
{
	return ThingDescription;
}

