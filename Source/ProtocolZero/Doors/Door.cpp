// (C) Naibell


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DoorTimeline.TickTimeline(DeltaTime);

}
void ADoor::RotateOpenDoor(FRotator start_rotation, float rotation_yaw)
{
    if (DoorCurve)
    {
        FOnTimelineFloat ProgressFunction;
        ProgressFunction.BindUFunction(this, FName("RotateOpenDoorProgress"));

        DoorTimeline.AddInterpFloat(DoorCurve, ProgressFunction);

        GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("start %f"), start_rotation.Yaw));

        this->start_rotation_param = start_rotation;
        this->rotation_yaw_param = rotation_yaw;

        DoorTimeline.PlayFromStart();
    }
}

void ADoor::TranslateOpenDoor(FVector start_position, float x_position)
{
    if (DoorCurve)
    {
        FOnTimelineFloat ProgressFunction;
        ProgressFunction.BindUFunction(this, FName("TranslateOpenDoorProgress"));

        DoorTimeline.AddInterpFloat(DoorCurve, ProgressFunction);


        this->start_position_param = start_position;
        this->x_position_param = x_position;

        DoorTimeline.PlayFromStart();
    }
}

void ADoor::CloseDoor()
{
    DoorTimeline.Reverse();
}


void ADoor::RotateOpenDoorProgress(float progress)
{
    FRotator new_rotation = this->start_rotation_param;
    new_rotation.Yaw += this->rotation_yaw_param * progress;
    DoorMesh->SetRelativeRotation(new_rotation);
}

void ADoor::TranslateOpenDoorProgress(float progress)
{
    GEngine->AddOnScreenDebugMessage(1, 1, FColor::Blue, FString::Printf(TEXT("Progress: %f"), progress));

    FVector new_position = this->start_position_param;
    new_position.X += this->x_position_param * progress;
    DoorMesh->SetRelativeLocation(new_position);
}

