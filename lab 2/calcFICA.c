double calcFICA(float ytd, float gross, double FICARate, double FICALimit) {
    // Calculate amount of FICA owed depending on gross income and federal rates
    if (ytd >= FICALimit)
        return 0;
    if (ytd + gross <= FICALimit)
        return gross * FICARate;
    return FICARate * (FICALimit - ytd);
}
