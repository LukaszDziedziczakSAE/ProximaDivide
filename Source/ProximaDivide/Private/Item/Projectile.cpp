// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsSet) return;
	FVector location = GetActorLocation();
	location += GetActorForwardVector() * DeltaTime * Speed;
	SetActorLocation(location);
	TimeToLive -= DeltaTime;
	if (TimeToLive <= 0)
	{
		Destroy();
	}
		
}

void AProjectile::Set(float ProjectileSpeed, float DistanceToTarget)
{
	Speed = ProjectileSpeed;
	TimeToLive = DistanceToTarget / ProjectileSpeed;
	
	bIsSet = true;
}

