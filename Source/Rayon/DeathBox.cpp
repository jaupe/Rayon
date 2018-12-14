// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathBox.h"
#include "Kismet/GameplayStatics.h"

ADeathBox::ADeathBox()
{

	//OnComponentBeginOverlap.AddDynamic(this, &ARayonTriggerBox::TriggerEnter);
		//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ADeathBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ADeathBox::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("ADeathBox"));
}

void ADeathBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ADeathBox::OnOverlapBegin"));

	UE_LOG(LogTemp, Warning, TEXT("ADeathBox::Restarting"));
	UGameplayStatics::OpenLevel((UObject*)GetWorld(), "SideScrollerExampleMap");
}

void ADeathBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ADeathBox::OnOverlapEnd"));
	UGameplayStatics::OpenLevel((UObject*)GetWorld(), "SideScrollerExampleMap");
}