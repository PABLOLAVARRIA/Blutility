// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPToolTest.h"

// Sets default values
ACPPToolTest::ACPPToolTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

}
 
// Called when the game starts or when spawned
void ACPPToolTest::BeginPlay()
{
	Super::BeginPlay();
	
} 

void ACPPToolTest::OnConstruction(const FTransform& Transform)
{
	if (NumberOfElements != ComponentList.Num())
	{
		for (auto* Comp : ComponentList)
		{
			Comp->UnregisterComponent();
			Comp->MarkAsGarbage();
		} 

		ComponentList.Empty();

		for (int32 i = 0; i < NumberOfElements; i++)
		{
			//UStaticMeshComponent* NewComp = CreateDefaultSubobject<UStaticMeshComponent>();
			UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this);
			NewComp->SetupAttachment(Body);
			NewComp->RegisterComponent();

	

			ComponentList.Add(NewComp);
		}

	}



}

// Called every frame
void ACPPToolTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

