#pragma once
#include "Hero.h"
#include "Fossil.h"
#include "MoneyCounter.h"

class MiningProcessor {
private:
	int processedOperations;
	int totalMinedValue;

public:
	MiningProcessor();

	bool processMining(Hero& hero, Fossil& fossil, MoneyCounter& moneyCounter);

	void resetStatistics();
	int getProcessedOperations() const;
	int getTotalMinedValue() const;
};