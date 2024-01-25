// Fill out your copyright notice in the Description page of Project Settings.


#include "A_CheckPoint.h"
#include "My_Singleton.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_CheckPoint::AA_CheckPoint(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AA_CheckPoint::BeginPlay(){
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AA_CheckPoint::OnOverlapBegin); 
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AA_CheckPoint::OnOverlapEnd);
	//OnActorHit.AddDynamic(this, &AA_CheckPoint::my_OnHit);
}

void AA_CheckPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player")){
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Entro en el Trigger");
		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->SaveNewCheckPoint(GetActorLocation(), CheckPoint_ID);
	}
}

void AA_CheckPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Salgo del Trigger");
}


