// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestProgress;
};

UCLASS()
class PROTOCOLZERO_API UQuestData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuest QuestData;
};
