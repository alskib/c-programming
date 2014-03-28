double calcGross(double hours, double rate) {
    // Return normal rate if < 40, or normal rate for 40 hours and 1.5x each extra hour for > 40
    return (hours <= 40) ? (hours * rate) : (40 * rate) + (1.5 * (hours - 40) * rate);
}
