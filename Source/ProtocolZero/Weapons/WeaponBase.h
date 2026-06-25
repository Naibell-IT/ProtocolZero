// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "../Interfaces/Interactable.h"
#include "WeaponBase.generated.h"

UCLASS(Abstract)
class PROTOCOLZERO_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(EditDefaultsOnly)
	float BodyDamage;
	UPROPERTY(EditDefaultsOnly)
	float HeadDamage;
	UPROPERTY(EditDefaultsOnly)
	float FireRate;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxClipAmmo;
	
	int32 CurrentFreeAmmo;
	int32 CurrentClipAmmo;
	bool IsAiming;
	FName SocketName;
protected:
	virtual void Equip();
	virtual void Fire();
public:
	virtual void StartFire();
	virtual void EndFire();
	virtual void Reload();

};
