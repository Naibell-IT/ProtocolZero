// (C) NAgames

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Quests/QuestData.h"
#include "QuestSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestUpdate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOCOLZERO_API UQuestSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestSystem();

protected:
	virtual void BeginPlay() override;

public:
	void CompleteQuest(FName quest_name, int32 compeled_progress);
	UFUNCTION(BlueprintCallable)

	TArray<UQuestData*> GetAllQuests();
	UFUNCTION(BlueprintCallable)
	UQuestData* GetCurrentQuest();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetCurrectProgress();
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuestUpdate OnQuestUpdate;
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UQuestData*> AllQuests;
private:
	UQuestData* current_quest;
	int32 current_quest_progress = 0;
	int32 current_quest_index = -1;
	void ChangeQuestToNext();
};