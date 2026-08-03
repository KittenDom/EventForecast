#pragma once

#include "Jam_TimeSeason.generated.h"

UENUM(BlueprintType)
enum class EJam_TimeSeason : uint8
{
	None = 0,
	Spring = 1,
	Summer = 2,
	Fall = 3,
	Winter = 4,
};
