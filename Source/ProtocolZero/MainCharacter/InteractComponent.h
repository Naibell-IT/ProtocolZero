// (C) NAgames

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/Interactable.h"
#include "InteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractUpdate, bool, is_can_interact, UObject*, interact_object);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOCOLZERO_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();
	UFUNCTION()
	void OnInteract();
protected:
	virtual void BeginPlay() override;
public:
	FTimerHandle CheckInteractHandle;
	void CheckInteract();
	UPROPERTY(EditDefaultsOnly, Category = "Trace Settings")
	float InteractTraceLenght;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInteractUpdate OnInteractUpdate;
private:
	AActor* character;
	bool is_can_interact = false;
	AActor* hit_actor;
};
