// Fill out your copyright notice in the Description page of Project Settings.

#include "RayonTriggerBox.h"

ARayonTriggerBox::ARayonTriggerBox()
{

	//OnComponentBeginOverlap.AddDynamic(this, &ARayonTriggerBox::TriggerEnter);
		//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ARayonTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ARayonTriggerBox::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("RayonTriggerBox"));
}

void ARayonTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
}

void ARayonTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));
}