// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "ProtectedDoor.h"
#include "AutoDoorController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOCOLZERO_API AAutoDoorController : public ATriggerVolume
{
	GENERATED_BODY()

public:
    AAutoDoorController();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
    UPROPERTY(EditAnywhere)
    AProtectedDoor* LeftDoor;
    UPROPERTY(EditAnywhere)
    AProtectedDoor* RightDoor;
};
