// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIFunctions.generated.h"

/**
 * 
 */
UCLASS()
class AILEANSTODRIVE_API UAIFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "AI Functions")
		static float Floor(float _Value);
};
