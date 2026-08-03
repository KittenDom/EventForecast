#pragma once

#include "DateTimeHeader.h"

#include "Jam_Time.generated.h"


USTRUCT()
struct FJam_Time
{
	GENERATED_BODY()

	FJam_Time()
	{
	}

	FJam_Time(float seconds)
	{
		Hour = seconds / SECONDS_IN_AN_HOUR;
		Minute = (static_cast<int32>(seconds) % SECONDS_IN_AN_HOUR) / SECONDS_IN_A_MINUTE;
		Second = (static_cast<int32>(seconds) % SECONDS_IN_A_MINUTE);
	}

	operator float() const
	{
		return (Hour * SECONDS_IN_AN_HOUR) + (Minute * SECONDS_IN_A_MINUTE) + Second;
	}

	UPROPERTY(EditAnywhere)
	int32 Hour = 0;

	UPROPERTY(EditAnywhere)
	int32 Minute = 0;

	UPROPERTY(EditAnywhere)
	float Second = 0.f;
};
