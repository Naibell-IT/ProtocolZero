// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

UCLASS(Abstract)
class PROTOCOLZERO_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();

protected:
	virtual void BeginPlay() override;
	void RotateOpenDoor(FRotator start_rotation, float rotation_yaw);
	void TranslateOpenDoor(FVector start_position, float x_position);
	void CloseDoor();
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;	
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorCurve;
	FTimeline DoorTimeline;
private:
	UFUNCTION()
	void RotateOpenDoorProgress(float progress);
	UFUNCTION()
	void TranslateOpenDoorProgress(float progress);
	FRotator start_rotation_param;
	float rotation_yaw_param;

	FVector start_position_param;
	float x_position_param;
};
