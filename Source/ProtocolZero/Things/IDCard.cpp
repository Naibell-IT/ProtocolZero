// (C) Naibell


#include "IDCard.h"
#include "../MainCharacter/MainCharacter.h"
#include "../MainCharacter/QuestSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIDCard::AIDCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AIDCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIDCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIDCard::Interact_Implementation(const AActor* initiator)
{
	if (AMainCharacter* character = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (UQuestSystem* quest_system = character->FindComponentByClass<UQuestSystem>())
		{
			if (quest_system->GetCurrentQuest()->QuestData.QuestName == CardQuestName)
			{
				character->OnPickUpIDCard();
				quest_system->CompleteQuest(CardQuestName, 1);
				Destroy();
			}
		}
	}
}

FString AIDCard::GetThingDescription_Implementation()
{
	return ThingDescription;
}

