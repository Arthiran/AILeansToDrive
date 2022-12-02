// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Brain.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AILEANSTODRIVE_API UBrain : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBrain();

	UFUNCTION(BlueprintCallable, Category = "AI Car")
		void Init(TArray<float> _Weights, bool _Copy, float _MutationRate);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Car")
		int Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Car")
		TArray<float> Weights;

	int Increment = 0;
		
};
