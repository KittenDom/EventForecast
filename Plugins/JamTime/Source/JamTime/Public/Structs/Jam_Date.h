#pragma once

#include "DateTimeHeader.h"

#include "Jam_Date.generated.h"


USTRUCT()
struct FJam_Date
{
	GENERATED_BODY()

	FJam_Date()
	{
	}

	FJam_Date(int32 days)
	{
		Year = (days / DAYS_IN_A_YEAR) + 1;
		Month = ((days % DAYS_IN_A_YEAR) / DAYS_IN_A_MONTH) + 1;
		Date = (days % DAYS_IN_A_MONTH) + 1;
	}

	operator int32() const
	{
		return ((Year - 1) * DAYS_IN_A_YEAR) + ((Month - 1) * DAYS_IN_A_MONTH) + (Date - 1);
	}

	UPROPERTY(EditAnywhere)
	int32 Year = 1;

	UPROPERTY(EditAnywhere)
	int32 Month = 1;

	UPROPERTY(EditAnywhere)
	int32 Date = 1;
};
