#pragma once

#include <cstdint>
#include <string>

/// @brief CSimEngine - Central simulation engine (Singleton)
/// Manages the entire simulation lifecycle and coordinates all subsystems
class CSimEngine {
private:
    static CSimEngine* instance;

    double simulationTime;
    double timeStep;
    bool isRunning;

    CSimEngine();

public:
    static CSimEngine* getInstance();

    CSimEngine(const CSimEngine&) = delete;
    CSimEngine& operator=(const CSimEngine&) = delete;

    ~CSimEngine();

    void initialize();
    void step();
    void run();
    void pause();
    void reset();
    void shutdown();

    double getSimulationTime() const { return simulationTime; }
    double getTimeStep() const { return timeStep; }
    bool getIsRunning() const { return isRunning; }

    void setTimeStep(double dt) { timeStep = dt; }
};
