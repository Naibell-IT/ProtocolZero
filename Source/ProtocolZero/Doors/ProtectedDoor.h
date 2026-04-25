// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.h"
#include "ProtectedDoor.generated.h"

UCLASS()
class PROTOCOLZERO_API AProtectedDoor : public ADoor
{
	GENERATED_BODY()
	
public:	
	AProtectedDoor();
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;	
	UPROPERTY(EditAnywhere)
	float x_translation;
public:	
	UFUNCTION()
	void DoorInteract();
private:
	bool is_open = false;

};
