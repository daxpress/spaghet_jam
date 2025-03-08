// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "GameplayTagContainer.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UInventoryComponent::AddToInventory(const FGameplayTag& Tag, int32 Quantity)
{
	if (Inventory.Contains(Tag))
	{
		auto ItemQuantity = Inventory.FindRef(Tag);
		ItemQuantity += Quantity;
		OnItemQuantityChanged.Broadcast(Tag, ItemQuantity);
		return ItemQuantity;
	}

	Inventory.Add(Tag, Quantity);
	OnItemQuantityChanged.Broadcast(Tag, Quantity);
	return Quantity;
}

int32 UInventoryComponent::RemoveFromInventory(const FGameplayTag& Tag, int32 Quantity)
{
	if (Inventory.Contains(Tag))
	{
		auto ItemQuantity = Inventory.FindRef(Tag);
		if (ItemQuantity > Quantity)
		{
			ItemQuantity -= Quantity;
			OnItemQuantityChanged.Broadcast(Tag, ItemQuantity);
			return ItemQuantity;
		}

		Inventory.Remove(Tag);
		OnItemQuantityChanged.Broadcast(Tag, 0);
		return 0;
	}

	return 0;
}

int32 UInventoryComponent::ConsumeFromInventory(const FGameplayTag& Tag, int32 Quantity)
{
	if (Inventory.Contains(Tag))
	{
		int32 OldValue = Inventory[Tag];
		int32 Remainig = RemoveFromInventory(Tag, Quantity);
		OnItemQuantityChanged.Broadcast(Tag, Remainig);

		return FMath::Min(OldValue - Remainig, Quantity);
	}
	return 0;
}

int32 UInventoryComponent::GetQuantity(const FGameplayTag& Tag)
{
	if (Inventory.Contains(Tag))
	{
		return Inventory[Tag];
	}

	return 0;
}
