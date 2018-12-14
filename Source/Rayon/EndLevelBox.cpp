// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevelBox.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEndLevelBox::AEndLevelBox()
{

	//OnComponentBeginOverlap.AddDynamic(this, &ARayonTriggerBox::TriggerEnter);
		//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AEndLevelBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AEndLevelBox::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("AEndLevelBox"));
}

void AEndLevelBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("AEndLevelBox::OnOverlapBegin"));

	UE_LOG(LogTemp, Warning, TEXT("AEndLevelBox::Restarting"));

	UGameplayStatics::OpenLevel((UObject*)GetWorld(), "SideScrollerExampleMap");
}

void AEndLevelBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("AEndLevelBox::OnOverlapEnd"));
	UGameplayStatics::OpenLevel((UObject*)GetWorld(), "SideScrollerExampleMap");
}