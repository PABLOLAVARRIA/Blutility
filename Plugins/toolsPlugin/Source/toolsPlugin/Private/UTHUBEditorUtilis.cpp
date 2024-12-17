// Fill out your copyright notice in the Description page of Project Settings.


#include "UTHUBEditorUtilis.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/DateTime.h"
#include "HAL/FileManager.h"



void UUTHUBEditorUtilis::ListAssetDependencies()
{
    // Acceso al Asset Registry
    IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

    // Obtener todos los assets
    TArray<FAssetData> AllAssets;
    AssetRegistry.GetAllAssets(AllAssets, true);

    // Mapa para almacenar referencias a los assets
    TMap<FName, TArray<FName>> AssetDependenciesMap;
    TSet<FName> ReferencedAssets;

    // Procesar dependencias
    for (const FAssetData& Asset : AllAssets)
    {
        TArray<FName> Dependencies;
        AssetRegistry.GetDependencies(Asset.PackageName, Dependencies);

        if (Dependencies.Num() > 0)
        {
            AssetDependenciesMap.Add(Asset.PackageName, Dependencies);
            for (const FName& Dependency : Dependencies)
            {
                ReferencedAssets.Add(Dependency);
            }
        }
    }

    // Generar la lista de Asset Roots
    FString OutputLog = "Asset Dependencias:\n";
    for (const auto& Pair : AssetDependenciesMap)
    {
        const FName& AssetName = Pair.Key;
        if (!ReferencedAssets.Contains(AssetName)) 
        {
            OutputLog += FString::Printf(TEXT("%s [ROOT]\n"), *AssetName.ToString());
            for (const FName& Dependency : Pair.Value)
            {
                OutputLog += FString::Printf(TEXT("  |- %s\n"), *Dependency.ToString());

                // Subdependencias
                TArray<FName> SubDependencies;
                if (AssetDependenciesMap.Contains(Dependency))
                {
                    SubDependencies = AssetDependenciesMap[Dependency];
                    for (const FName& SubDependency : SubDependencies)
                    {
                        OutputLog += FString::Printf(TEXT("      |- %s\n"), *SubDependency.ToString());
                    }
                }
            }
        }
    }

    // Obtener la fecha actual
    FDateTime Now = FDateTime::Now();
    FString DateString = Now.ToString(TEXT("%Y%m%d"));

    FString FileName = FString::Printf(TEXT("RefLogOutput_%s.log"), *DateString);
    FString FilePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Logs"), FileName);

    if (FMessageDialog::Open(EAppMsgType::YesNo, FText::FromString(TEXT("¿Estas seguro de generar el archivo?"))))
    {
        FFileHelper::SaveStringToFile(OutputLog, *FilePath);
    }

    

    
}


