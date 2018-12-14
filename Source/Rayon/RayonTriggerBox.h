// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RayonTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class RAYON_API ARayonTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
	ARayonTriggerBox();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
	

};
