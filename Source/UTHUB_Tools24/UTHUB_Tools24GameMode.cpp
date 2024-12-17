// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_Tools24GameMode.h"
#include "UTHUB_Tools24Character.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_Tools24GameMode::AUTHUB_Tools24GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
