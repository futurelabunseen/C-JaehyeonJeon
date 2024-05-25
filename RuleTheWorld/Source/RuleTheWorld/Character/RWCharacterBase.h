// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/RWAnimationAttackInterface.h"
#include "Interface/RWCharacterWidgetInterface.h"
#include "Interface/RWShelterCollisionInterface.h"
#include "RWEnums.h" // Enum Type 모음
#include "Interface/RWInventoryInterface.h"
#include "RWCharacterBase.generated.h"


UCLASS()
class RULETHEWORLD_API ARWCharacterBase : public ACharacter, public IRWAnimationAttackInterface, public IRWCharacterWidgetInterface, public IRWShelterCollisionInterface, public IRWInventoryInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARWCharacterBase();

	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ECharacterState CharacterState;
// Bounding Box
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoundingBox")
	TObjectPtr<class UBoxComponent> CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoundingBox")
	//TObjectPtr<class ARWInteractableActor> CollisionedItem;
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoundingBox")
	//uint8 bIsItemInBound:1;
	//  => 인터페이스로 이동
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoundingBox")
	TObjectPtr<class APawn> CollisionedPawn;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoundingBox")
	uint8 bIsAnimalInBound:1;

// Attack Hit Check
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
// Dead Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	void SetDead();
	UFUNCTION(Server, Reliable)
	void ServerRPCSetDead();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetDead();
	
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

// Starving Section
	virtual void SetStarving();
	
// Stat Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<class URWCharacterStatComponent> StatComponent;

	// interface 구현
	virtual void SetUpCharacterWidget(class URWMainWidget* MainWidget) override;

// Shelter Section
protected:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Shelter, Meta = (AllowPrivateAccess = "true"))
	uint8 bIsInShelter:1;
	// Interface
	//UFUNCTION()
	virtual void SetupShelterEntry() override;
	virtual void SetupShelterExit() override;

	void ApplyFireDamageOverTime();
public:
	// Niagara Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shelter)
	TObjectPtr<class UNiagaraComponent> NiagaraEffectFire;
};
