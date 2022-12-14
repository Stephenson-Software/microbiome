#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "header/simulation.h"

Simulation::Simulation(AppConfig* config, int id, std::string name) {
    this->config = config;
    this->microbiome = new Microbiome(id, name, config->getEnvironmentSize(), config->getEntityFactor());
    this->logger = new Logger("log.simulation.txt");
}

Simulation::~Simulation() {
    delete microbiome;
    delete logger;
}

void Simulation::run() {
    logger->log("Simulation " + std::to_string(microbiome->getId()) + " started.");
    while (running) {
        microbiome->initiateMicroorganismMovement();

        if (config->isSimulationOutputEnabled()) {
            system("clear");
            microbiome->printConsoleRepresentation();
            printRunningStats();
        }


        numTicks++;
        if (config->getMaxTicks() > 0 && numTicks >= config->getMaxTicks()) {
            logger->log("Max ticks reached. Stopping simulation.");
            running = false;
        }

        if (config->getTickLengthInSeconds() > 0) {
            sleep(config->getTickLengthInSeconds());
        }

        if (microbiome->getNumAliveMicroorganisms() == 0) {
            logger->log("All microorganisms are dead. Stopping simulation " + std::to_string(microbiome->getId()) + ".");
            running = false;
        }
    }
}

void Simulation::printRunningStats() {
    std::cout << "Name: " << microbiome->getName() << std::endl;
    std::cout << "Size: " << microbiome->getGrid()->getSize() << "x" << microbiome->getGrid()->getSize() << std::endl;
    std::cout << "Microorganisms: " << microbiome->getNumAliveMicroorganisms() << std::endl;
    std::cout << "Dead Microorganisms: " << microbiome->getNumDeadMicroorganisms() << "\n";
    std::cout << "Total Energy: " << microbiome->getTotalEnergy() << "\n";
    std::cout << "" << std::endl;
    if (config->getMaxTicks() > 0) {
        std::cout << "Ticks elapsed: " << numTicks << " of " << config->getMaxTicks() << std::endl;
    }
    else {
        std::cout << "Ticks elapsed: " << numTicks << std::endl;
    }
}

void Simulation::printFinishedStats() {
    std::cout << "" << std::endl;
    std::cout << "=== Simulation Complete ===" << std::endl;
    std::cout << "Locations: " << microbiome->getGrid()->getLocations().size() << "\n";
    std::cout << "Surviving Microorganisms: " << microbiome->getNumAliveMicroorganisms() << "\n";
    std::cout << "Dead Microorganisms: " << microbiome->getNumDeadMicroorganisms() << "\n";
    std::cout << "Total Energy: " << microbiome->getTotalEnergy() << "\n";
    std::cout << "Ticks elapsed: " << numTicks << std::endl;
}

size_t Simulation::getSurvivingMicroorganisms() {
    return microbiome->getNumAliveMicroorganisms();
}

size_t Simulation::getDeadMicroorganisms() {
    return microbiome->getNumDeadMicroorganisms();
}

size_t Simulation::getEnergy() {
    return microbiome->getTotalEnergy();
}

size_t Simulation::getTicksElapsed() {
    return numTicks;
}