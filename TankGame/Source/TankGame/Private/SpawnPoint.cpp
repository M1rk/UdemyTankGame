// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//автоматически выбираем переменную SpawnClass в блюпринте(иначе она слетает каждый раз при компил€ции)
	static ConstructorHelpers::FClassFinder<AActor> SprungWheelFinderClass(TEXT("/Game/Tank/SprungWheel_BP")); 
	if (SprungWheelFinderClass.Class != nullptr)
	{
		SpawnClass = SprungWheelFinderClass.Class;
	}
	
}




// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//спавним Actor'a в координатах компонента с (задержкой)?
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform()); 
	
	if (!SpawnedActor) { return; }
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());

	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

