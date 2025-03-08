// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemQuantityChangedDelegate, FGameplayTag, ItemType,  int32, Quantity); 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPAGHETJAM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnItemQuantityChangedDelegate OnItemQuantityChanged;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 AddToInventory(const FGameplayTag& Tag, int32 Quantity);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 RemoveFromInventory(const FGameplayTag& Tag, int32 Quantity);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 ConsumeFromInventory(const FGameplayTag& Tag, int32 Quantity);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 GetQuantity(const FGameplayTag& Tag);

private:
	TMap<FGameplayTag, int32> Inventory;
};
