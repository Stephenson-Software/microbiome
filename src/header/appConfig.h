#ifndef App_Config_h
#define App_Config_h

/**
 * The AppConfig class contains the configuration for the application and 
 * is used in the MicrobiomeApplication and Simulation classes.
 * @author Daniel McCoy Stephenson
 */
class AppConfig {
    public:
        int getEnvironmentSize();
        int getEntityFactor();
        int getMaxTicks();
        int getTickLengthInSeconds();
        int getNumSimulations();
        bool isSimulationOutputEnabled();

        void setEnvironmentSize(int environmentSize);
        void setEntityFactor(int entityFactor);
        void setMaxTicks(int maxTicks);
        void setTickLengthInSeconds(int tickLengthInSeconds);
        void setNumSimulations(int numSimulations);
        void setSimulationOutputEnabled(bool simulationOutputEnabled);
    private:
        int environmentSize = 10;
        int entityFactor = 10;
        int maxTicks = 120; // set to 0 to run indefinitely until all microorganisms die
        int tickLengthInSeconds = 1; // set to 0 to run as fast as possible
        int numSimulations = 10;
        bool simulationOutputEnabled = true;
};

#endif