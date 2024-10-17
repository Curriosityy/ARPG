#pragma once
#include "ARPGEnumTypes.generated.h"

UENUM()
enum class EARPGConfirmType: uint8
{
	Yes,
	No
};


UENUM()
enum class EARPGValidType: uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EARPGSuccessType: uint8
{
	Successful,
	Unsuccessful
};

UENUM()
enum class EARPGHitDirection: uint8
{
	Front,
	Back,
	Left,
	Right
};
