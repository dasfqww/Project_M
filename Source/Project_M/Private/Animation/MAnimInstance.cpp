// CSM All Rights Reserved.


#include "Animation/MAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(OwnerCharacter))
	{
		OwnerMovementComp = OwnerCharacter->GetCharacterMovement();
	}
}

void UMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(OwnerCharacter))
	{
		Speed = OwnerCharacter->GetVelocity().Length();
		FRotator BodyRot = OwnerCharacter->GetActorRotation();
		FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
		BodyPrevRot = BodyRot;

		YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);
		FRotator ControlRot = OwnerCharacter->GetBaseAimRotation();
		LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, BodyRot);
	}

	if(IsValid(OwnerMovementComp))
	{
		bIsJumping = OwnerMovementComp->IsFalling();
	}
}

void UMAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

}
