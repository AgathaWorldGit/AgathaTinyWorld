#pragma once

UENUM(BlueprintType)
enum class EFramerate : uint8
{
	FPS_30 UMETA(DisplayName = "30 FPS"),
	FPS_60 UMETA(DisplayName = "60 FPS"),
	FPS_120 UMETA(DisplayName = "120 FPS"),
	FPS_144 UMETA(DisplayName = "144 FPS"),
	FPS_240 UMETA(DisplayName = "240 FPS"),
	FPS_Uncapped UMETA(DisplayName = "Uncapped"),
};

class FFramerateUtils
{
public:
	// Convert the EFramerate enum to its integer value
	static int EnumToValue(const EFramerate& InFramerate)
	{
		int Value = 0;
		switch (InFramerate)
		{
		case EFramerate::FPS_30:
			Value = 30;
			break;
		case EFramerate::FPS_60:
			Value = 60;
			break;
		case EFramerate::FPS_120:
			Value = 120;
			break;
		case EFramerate::FPS_144:
			Value = 144;
			break;
		case EFramerate::FPS_240:
			Value = 240;
			break;
		case EFramerate::FPS_Uncapped:
			Value = 0;  // Uncapped doesn't have a defined limit
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown framerate enum value, returning 0"));
			Value = 0;  // Default case for unexpected values
			break;
		}
		UE_LOG(LogTemp, Log, TEXT("EnumToValue: Framerate %s corresponds to %d FPS"), 
			*UEnum::GetValueAsString(InFramerate), Value);
		return Value;
	}

	// Convert the EFramerate enum to a string representation
	static FString EnumToString(const EFramerate& InFramerate)
	{
		const auto Value = EnumToValue(InFramerate);
		FString Result = Value > 0 
			? FString::Printf(TEXT("%d FPS"), Value)
			: FString(TEXT("Uncapped"));
		
		// Log the conversion result
		UE_LOG(LogTemp, Log, TEXT("EnumToString: Framerate %s converted to string '%s'"),
			*UEnum::GetValueAsString(InFramerate), *Result);

		return Result;
	}
};
