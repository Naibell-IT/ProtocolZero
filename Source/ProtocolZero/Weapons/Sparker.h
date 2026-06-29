// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.h"
#include "Components/PointLightComponent.h"
#include "../Interfaces/Interactable.h"
#include "../MainCharacter/MainCharacter.h"
#include "Sparker.generated.h"

UCLASS()
class PROTOCOLZERO_API ASparker : public AWeaponBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ASparker();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FString ThingDescription = TEXT("ПТ-3 Искровик");
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UNiagaraSystem* ElectricBeamSystem;
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UPointLightComponent* MuzzleFlashlight;
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	float FlashDuration = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float ReloadTime = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float ManualShootingCooldown = 0.5f;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void Equip() override;
	void Fire() override;
	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;
	FTimerHandle FlashlightTimerHandle;
	FTimerHandle ReloadBlockTimerHandle;
	FTimerHandle FireBlockTimerHandle;
	void UnblockShootingReload();
	void UnblockShootFire();
	void TurnOffMuzzleLight();
public:
	void StartFire() override;
	void EndFire() override;
	void Reload() override;
private:
	AMainCharacter* player;
	FVector CastTrace();
	void ShowShootVFX(FVector beam_end_pos);
	bool is_shooting_blocked = false;
	bool is_reloading = false;
};
