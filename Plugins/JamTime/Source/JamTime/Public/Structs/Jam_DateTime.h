#pragma once

#include "DateTimeHeader.h"

#include "Jam_DateTime.generated.h"


USTRUCT()
struct FJam_DateTime
{
	GENERATED_BODY()

public:
	FJam_DateTime()
	{
		CurrentTime = 6 * SECONDS_IN_AN_HOUR;
		CurrentDate = 0;
	}

	FJam_DateTime(const float currentTime, const int32 currentDate)
	{
		CurrentTime = currentTime;
		CurrentDate = currentDate;
	}

public:
	UPROPERTY()
	float CurrentTime = 6 * SECONDS_IN_AN_HOUR;

	UPROPERTY()
	int32 CurrentDate = 0;
};
