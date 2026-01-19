#include "MiningProcessor.h"
#include <iostream>

MiningProcessor::MiningProcessor() :
	processedOperations(0), totalMinedValue(0) {}

bool MiningProcessor::processMining(Hero& hero, Fossil& fossil, MoneyCounter& moneyCounter) {
	if (!fossil.isCollected()) {
		hero.collectFossil(fossil);
		moneyCounter.addMoney(fossil.getValue());

		processedOperations++;
		totalMinedValue += fossil.getValue();

		Fossil* fossilPtr = &fossil;
		std::cout << "Processed fossil at address: " << fossilPtr
			<< " with value: " << fossil.getValue() << std::endl;

		return true;
	}
	return false;
}

void MiningProcessor::resetStatistics() {
	processedOperations = 0;
	totalMinedValue = 0;
}

int MiningProcessor::getProcessedOperations() const {
	return processedOperations;
}

int MiningProcessor::getTotalMinedValue() const {
	return totalMinedValue;
}