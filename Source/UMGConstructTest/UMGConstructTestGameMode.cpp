// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMGConstructTestGameMode.h"
#include "UMGConstructTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUMGConstructTestGameMode::AUMGConstructTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
