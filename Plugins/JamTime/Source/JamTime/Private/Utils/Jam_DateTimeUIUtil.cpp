#include "Utils/Jam_DateTimeUIUtil.h"

#include "Jam_TimeSetting.h"
#include "Enums/Jam_TimeSeason.h"
#include "Internationalization/StringTable.h"
#include "Utils/Jam_DateTimeUtil.h"


int32 UJam_DateTimeUIUtil::GetHour(float seconds)
{
	return UJam_DateTimeUtil::GetHourClamped(seconds);
}

int32 UJam_DateTimeUIUtil::GetMinute(float seconds)
{
	int32 clampedMinutes = static_cast<int32>(seconds) % SECONDS_IN_AN_HOUR;
	if (clampedMinutes < 0)
	{
		clampedMinutes += SECONDS_IN_AN_HOUR;
	}
	return clampedMinutes / SECONDS_IN_A_MINUTE;
}

int32 UJam_DateTimeUIUtil::GetSecond(float seconds)
{
	int32 clampedSeconds = static_cast<int32>(seconds) % SECONDS_IN_A_MINUTE;
	if (clampedSeconds < 0)
	{
		clampedSeconds += SECONDS_IN_A_MINUTE;
	}
	return clampedSeconds;
}


FText UJam_DateTimeUIUtil::GetTwoDigitsFormat(const int32 timeValue)
{
	return FText::AsNumber(FMath::Abs(timeValue), &FNumberFormattingOptions().SetMinimumIntegralDigits(2).SetUseGrouping(false));
}

FText UJam_DateTimeUIUtil::GetTimeToText(const float seconds)
{
	FFormatNamedArguments args;
	args.Emplace("hour", GetTwoDigitsFormat(GetHour(seconds)));
	args.Emplace("minute", GetTwoDigitsFormat(GetMinute(seconds)));
	args.Emplace("second", GetTwoDigitsFormat(GetSecond(seconds)));
	return FText::Format(INVTEXT("{hour}:{minute}:{second}"), args);
}

FText UJam_DateTimeUIUtil::GetPeriodicTimeToText(const float seconds, const bool b12hClockFormat, const int32 clockPeriod)
{
	FFormatNamedArguments args;
	const int32 periodMinute = (GetMinute(seconds) / clockPeriod) * clockPeriod;
	args.Emplace("minute", GetTwoDigitsFormat(periodMinute));

	if (b12hClockFormat)
	{
		int32 formattedHour = GetHour(seconds);
		if (formattedHour > 12)
		{
			formattedHour = formattedHour % 12;
		}
		if (formattedHour == 0)
		{
			formattedHour = 12;
		}

		args.Emplace("hour", GetTwoDigitsFormat(formattedHour));
		args.Emplace("meridiem", GetHour(seconds) < 12 ? FText::FromString("AM") : FText::FromString("PM"));
		return FText::Format(INVTEXT("{hour}:{minute} {meridiem}"), args);
	}
	args.Emplace("hour", GetTwoDigitsFormat(GetHour(seconds)));

	return FText::Format(INVTEXT("{hour}:{minute}"), args);
}

FText UJam_DateTimeUIUtil::GetDateToText(const int32 days)
{
	FFormatNamedArguments args;
	args.Emplace("date", GetTwoDigitsFormat(UJam_DateTimeUtil::GetDate(days)));
	args.Emplace("month", GetTwoDigitsFormat(UJam_DateTimeUtil::GetMonth(days)));
	args.Emplace("year", GetTwoDigitsFormat(UJam_DateTimeUtil::GetYear(days)));
	args.Emplace("era", FText::FromString(TEXT("")));

	if (days < 0)
	{
		if (const UStringTable* dateTimeStringTable = GetDefault<UJam_TimeSetting>()->DateTimeStringTable.LoadSynchronous())
		{
			args.Emplace("era", FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Era_BCE")));
		}
		return FText::Format(INVTEXT("{date}/{month}/{year} {era}"), args);
	}
	return FText::Format(INVTEXT("{date}/{month}/{year}"), args);
}

FText UJam_DateTimeUIUtil::GetDayOfWeek(const int32 days)
{
	if (const UStringTable* dateTimeStringTable = GetDefault<UJam_TimeSetting>()->DateTimeStringTable.LoadSynchronous())
	{
		switch (UJam_DateTimeUtil::GetDayOfWeek(days))
		{
			case EJam_TimeDayOfWeek::None:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_None"));

			case EJam_TimeDayOfWeek::Monday:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_Monday"));

			case EJam_TimeDayOfWeek::Tuesday:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_Tuesday"));

			case EJam_TimeDayOfWeek::Wednesday:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_Wednesday"));

			case EJam_TimeDayOfWeek::Thursday:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_Thursday"));

			case EJam_TimeDayOfWeek::Weekend:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_Weekend"));
		}
		return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_DayOfWeek_None"));
	}
	return FText(UEnum::GetDisplayValueAsText(EJam_TimeDayOfWeek::None));
}

FText UJam_DateTimeUIUtil::GetSeason(const int32 days)
{
	if (const UStringTable* dateTimeStringTable = GetDefault<UJam_TimeSetting>()->DateTimeStringTable.LoadSynchronous())
	{
		switch (UJam_DateTimeUtil::GetSeason(days))
		{
			case EJam_TimeSeason::None:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Season_None"));

			case EJam_TimeSeason::Spring:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Season_Spring"));

			case EJam_TimeSeason::Summer:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Season_Summer"));

			case EJam_TimeSeason::Fall:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Season_Fall"));

			case EJam_TimeSeason::Winter:
				return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Season_Winter"));
		}
		return FText::FromStringTable(dateTimeStringTable->GetStringTableId(), FTextKey("SoeDateTimeSystem_Season_None"));
	}
	return FText(UEnum::GetDisplayValueAsText(EJam_TimeSeason::None));
}
