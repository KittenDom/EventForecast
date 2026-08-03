#pragma once

#include "Jam_TimeOfDay.generated.h"

UENUM(BlueprintType)
enum class EJam_TimeOfDay : uint8
{
	Morning = 0,
	Noon = 1,
	Evening = 2,
	Night = 3,
};
