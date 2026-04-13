// (C) NAgames

#include "QuestSystem.h"
#include "Kismet/GameplayStatics.h"

UQuestSystem::UQuestSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UQuestSystem::BeginPlay()
{
	Super::BeginPlay();
	ChangeQuestToNext();
}

void UQuestSystem::CompleteQuest(FName quest_name, int32 compeled_progress)
{
	if (quest_name == current_quest->QuestData.QuestName)
	{
		if (current_quest_progress + compeled_progress >= current_quest->QuestData.QuestProgress)
			ChangeQuestToNext();
		else
		{
			current_quest_progress += compeled_progress;
			OnQuestUpdate.Broadcast();
		}
	}
}

TArray<UQuestData*> UQuestSystem::GetAllQuests()
{
	return AllQuests;
}

UQuestData* UQuestSystem::GetCurrentQuest()
{
	return current_quest;
}

int32 UQuestSystem::GetCurrectProgress()
{
	return current_quest_progress;
}

void UQuestSystem::ChangeQuestToNext()
{
	current_quest_index++;

	if (AllQuests.IsValidIndex(current_quest_index))
	{
		current_quest = AllQuests[current_quest_index];
		current_quest_progress = 0;
	}
	else
		current_quest = nullptr;

	OnQuestUpdate.Broadcast();
}
