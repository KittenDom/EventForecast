#include "Jam_TimeDisplayActor.h"

#include "Jam_TimeSystem.h"
#include "Components/TextRenderComponent.h"
#include "Utils/Jam_DateTimeUIUtil.h"

AJam_TimeDisplayActor::AJam_TimeDisplayActor()
{
	PrimaryActorTick.bCanEverTick = false;

	constexpr float textRenderMargin = -20.f;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	TimeText = CreateDefaultSubobject<UTextRenderComponent>("TimeText");
	TimeText->SetupAttachment(RootComponent);
	TimeText->SetText(FText::FromString(TEXT("Actual Time: hh:mm:ss")));

	DateText = CreateDefaultSubobject<UTextRenderComponent>("DateText");
	DateText->SetupAttachment(RootComponent);
	DateText->SetText(FText::FromString(TEXT("Actual Date: DD/MM/YY")));
	DateText->SetRelativeLocation(FVector(0.f, 0.f, 2 * textRenderMargin));
}

void AJam_TimeDisplayActor::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		if (UJam_TimeSystem* dateTimeSystem = GetWorld()->GetSubsystem<UJam_TimeSystem>())
		{
			dateTimeSystem->TimeChanged.AddUObject(this, &ThisClass::OnTimeChanged);
			dateTimeSystem->DateChanged.AddUObject(this, &ThisClass::OnDateChanged);
			OnTimeChanged(dateTimeSystem->GetCurrentTime());
			OnDateChanged(dateTimeSystem->GetCurrentDate());
		}
	}
}

void AJam_TimeDisplayActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		if (UJam_TimeSystem* dateTimeSystem = GetWorld()->GetSubsystem<UJam_TimeSystem>())
		{
			dateTimeSystem->TimeChanged.RemoveAll(this);
			dateTimeSystem->DateChanged.RemoveAll(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AJam_TimeDisplayActor::OnTimeChanged(float currentTime) const
{
	if (!TimeText)
	{
		return;
	}
	TimeText->SetText(UJam_DateTimeUIUtil::GetTimeToText(currentTime));
}

void AJam_TimeDisplayActor::OnDateChanged(int32 currentDate) const
{
	if (!DateText)
	{
		return;
	}
	DateText->SetText(UJam_DateTimeUIUtil::GetDateToText(currentDate));
}
