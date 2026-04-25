// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "../Interfaces/Interactable.h"
#include "../MainCharacter/MainCharacter.h"
#include "ProtectedDoor.h"
#include "CardTerminal.generated.h"

UCLASS()
class PROTOCOLZERO_API ACardTerminal : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardTerminal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TerminalMesh;
	UPROPERTY(EditDefaultsOnly)
	FString ThingDescription = FString(TEXT("Терминал взаимодействия"));
	UPROPERTY(EditAnywhere)
	AProtectedDoor* LinkedDoor;
private:
	AMainCharacter* character;
};
