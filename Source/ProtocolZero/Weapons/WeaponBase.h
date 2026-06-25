// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "../Interfaces/Interactable.h"
#include "WeaponBase.generated.h"


UENUM(BlueprintType)
enum class EPlayerAvailableWeapons : uint8
{
	Sparker,
	Squall,
	Hammer
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, current_clip_ammo, int32, current_free_ammo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotice, FText, NoticeText);


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
	float FireRateInSeconds;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxClipAmmo;
	UPROPERTY(EditDefaultsOnly)
	float FireRange;
	int32 CurrentFreeAmmo;
	int32 CurrentClipAmmo;
public:
	UPROPERTY(BlueprintReadOnly)
	EPlayerAvailableWeapons WeaponType;
	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnNotice;
protected:
	bool IsAiming;
	FName SocketName;
	virtual void Equip();
	virtual void Fire();
public:
	virtual void StartFire();
	virtual void EndFire();
	virtual void Reload();
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetCurrentAmmo();
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetClipAmmo();
};
