// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.h"
#include "../Interfaces/Interactable.h"
#include "SimpleDoor.generated.h"

UCLASS()
class PROTOCOLZERO_API ASimpleDoor : public ADoor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	FString DoorInteractionDescription = TEXT("");
	UPROPERTY(EditAnywhere, Category = "Animation")
	float RotationYaw = 90;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;
private:
	bool is_open = false;
};
