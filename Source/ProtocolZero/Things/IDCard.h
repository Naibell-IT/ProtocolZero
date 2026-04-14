// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "IDCard.generated.h"

UCLASS()
class PROTOCOLZERO_API AIDCard : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIDCard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FString ThingDescription = TEXT("ID карта сотрудника");
	UPROPERTY(EditDefaultsOnly, Category = "Quests")
	FName CardQuestName;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;
};
