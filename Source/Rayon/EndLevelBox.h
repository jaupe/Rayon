// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndLevelBox.generated.h"

/**
 * 
 */
UCLASS()
class RAYON_API AEndLevelBox : public ATriggerBox
{
	GENERATED_BODY()

private:
	FTimerHandle EndLevelTimerHandle;
public: 
	AEndLevelBox();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
