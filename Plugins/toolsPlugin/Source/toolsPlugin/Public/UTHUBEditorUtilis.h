// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UTHUBEditorUtilis.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSPLUGIN_API UUTHUBEditorUtilis : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(CallInEditor, BlueprintCallable, Category = "Asset Management")
    static void ListAssetDependencies();


};
