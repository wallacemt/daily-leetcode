int maximumEnergy(int* energy, int energySize, int k) {
    int maxEnergy = energy[energySize - 1];
    
    for (int i = energySize - 1; i >= 0; i--) {
        if (i + k < energySize) {
            energy[i] += energy[i + k];
        }
        if (energy[i] > maxEnergy) {
            maxEnergy = energy[i];
        }
    }
    return maxEnergy;
}