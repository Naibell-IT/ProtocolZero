// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "../Interfaces/Interactable.h"
#include "Computer.generated.h"

USTRUCT(BlueprintType)
struct FMail
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Body;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComputerOpen, const TArray<FMail>&, ComputerMails);


UCLASS()
class PROTOCOLZERO_API AComputer : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComputer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TArray<FMail> Mails;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
public:	
	UFUNCTION(BlueprintCallable)
	TArray<FMail> GetMails();
	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;

	UPROPERTY(BlueprintAssignable)
	FOnComputerOpen OnComputerOpen;
private:
}; 
