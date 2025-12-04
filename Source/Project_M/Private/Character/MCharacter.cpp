// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GAS/MAbilitySystemComponent.h"
#include "GAS/MAttributeSet.h"
#include "Widget/Overhead/OverheadStatGauge.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Component/Combat/PawnCombatComponent.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MAbilitySystemComp = CreateDefaultSubobject<UMAbilitySystemComponent>("Abilty System Component");
	MAttributeSet = CreateDefaultSubobject<UMAttributeSet>("Attribute Set");

	OverheadWidgetComp = CreateDefaultSubobject<UWidgetComponent>("Overhead Widget Component");
	OverheadWidgetComp->SetupAttachment(GetRootComponent());

	CombatComponent = CreateDefaultSubobject<UPawnCombatComponent>("Combat Component");

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

}

void AMCharacter::ServerSideInit()
{
	MAbilitySystemComp->InitAbilityActorInfo(this, this);
	MAbilitySystemComp->ApplyInitialEffects();
	MAbilitySystemComp->GiveInitialAbilities();
}

void AMCharacter::ClientSideInit()
{
	MAbilitySystemComp->InitAbilityActorInfo(this, this);

}

const TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& AMCharacter::GetAbilities() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return MAbilitySystemComp->GetAbilities();
}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConfigOverheadStatWidget();
}

void AMCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

UAbilitySystemComponent* AMCharacter::GetAbilitySystemComponent() const
{
	return GetMAbilitySystemComponent();
}

void AMCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() ==
		GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() ==
		GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(CombatComponent))
	{

	}
}

void AMCharacter::ConfigOverheadStatWidget()
{
	if (!IsValid(OverheadWidgetComp)) return;

	IsPlayerControlled();

	if (IsLocallyControlledByPlayer())
	{
		OverheadWidgetComp->SetHiddenInGame(true);
		return;
	}

	UOverheadStatGauge* OverheadGauge = Cast<UOverheadStatGauge>(OverheadWidgetComp->GetUserWidgetObject());
	if (IsValid(OverheadGauge))
	{
		OverheadGauge->ConfigureWithASC(GetAbilitySystemComponent());
		OverheadWidgetComp->SetHiddenInGame(false);
		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
		GetWorldTimerManager().SetTimer(HeadStatGaugeVisibilityUpdateTimerHandle, this, 
			&ThisClass::UpdateHeadGaugeVisibility, CheckInterval, true);
	}
}

void AMCharacter::UpdateHeadGaugeVisibility()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (LocalPlayerPawn)
	{
		float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		OverheadWidgetComp->SetHiddenInGame(DistSquared > CheckRangeSquared);
	}
}

