#pragma once

#include "Jam_TimeDayOfWeek.generated.h"

UENUM(BlueprintType)
enum class EJam_TimeDayOfWeek : uint8
{
	None = 0,
	Monday = 1,
	Tuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Weekend = 5,
};
