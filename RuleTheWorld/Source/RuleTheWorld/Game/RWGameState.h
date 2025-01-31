// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RWGameState.generated.h"

/**
 * 
 */

UCLASS()
class RULETHEWORLD_API ARWGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ARWGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	TObjectPtr<class ARWGameMode> RWGameMode;
// Network
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Time")
	FTimerHandle TimerHandle_RequestGameTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Time")
	int32 DayScore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Time")
	float CurrentTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	float DayProgressPercent;

	// CurrentTime 변수를 바탕으로 CurrentHour와 Current Minute, DayProgressPercent를 계산
	UFUNCTION()
	void CalcTimeVariable();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentHour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentMinute;

	
public:
	UFUNCTION()
	void SetCurrentTime(float InputCurrnetTime);
	UFUNCTION()
	void SetDayScore(int32 InputDayScore);
	
	float GetClientCurrentTime() const;
	float GetClientDayProgressPercent() const;
	int32 GetClientDayScore() const;


// BackGround Music
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sound)
	TObjectPtr<class UAudioComponent> AudioComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sound)
	TObjectPtr<class USoundWave> DayBGM;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sound)
	TObjectPtr<class USoundWave> NightBGM;

	void PlaySound(class USoundWave* SoundWave);


// GameEvent UI
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class URWEventWidget> EventWidgetClass; // BP에서 지정
	
	TObjectPtr<class URWEventWidget> EventWidgetInstance;
	

	
	void EventWidgetInstancing();
	
// GameEvent
	void SetDayEvent();
	void SetNightEvent();

	
};
