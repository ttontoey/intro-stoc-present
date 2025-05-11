#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;


double DELTA_t = 0.01; // Time step
random_device rd;                   // Non-deterministic number randomizer provided by hardware entropy (Slow but non-deterministic)
default_random_engine generator;    // Pseudo-random randomizer (Fast but quite deterministic)


double rand_normal(double mean, double sigma){
    std::normal_distribution<double> distribution(mean, sigma); // Create a normal distribution object
    return distribution(generator);                             // Return one sample from normal distribution
}

int main(){

    generator.seed(rd());
    // Idea: We want the normal distribution object seed to be non-deterministic as much as possible
    // Therefore, we use rd() to retrieve the seed for pseudo-random randomizer


    double K, r;    // Exercise price and risk-free rate respectively
    int N;          // Monte-Carlo simulation(s) to run

    cout << "Initial stock price (X_0): 100\n";

    // Inputs & Error handlers
    cout << "Exercise price (K): ";
    cin >> K;
    if (K <= 0){
        cout << "Error: Exercise price (K) must be greater than 0";
        return 0;
    }
    cout << "Return rate (r): ";
    cin >> r;
    if (r < 0){
        cout << "Error: Exercise price (K) must be greater than or equal to 0";
        return 0;
    }
    cout << "Simulation(s) to run: ";
    cin >> N;
    if (N <= 0){
        cout << "Error: Simulation(s) to run must be greater than 0";
        return 0;
    }

    // A data structure to store stock prices (X_t) value
    vector<double> v(101);

    v[0] = 100.0;   // Stock price at time zero (X_0)

    double sum;     // Temporary variable, will be used to calculate the result later on

    // Run simulations for N times as specified by user
    for (int j=0 ; j<N ; j++){

        // For each iteration, simulate X_t for 100 time steps
        for (int i=1 ; i < v.size() ; i++){

            // Randomize W_t
            double W_t = rand_normal(0, DELTA_t);

            // Update the X_t value according to Euler-Maruyama discretization
            v[i] = v[i-1] + 0.1 * (100 * (10 * r + 1) * exp(r * (i * 1.0)/100) - v[i-1]) * DELTA_t + 0.2 * W_t;

        }

        // Add option value at t = 1, denoted C_1, to the temporary variable
        // Note that v[100] is X_1
        sum += max(v[100] - K, 0.0);
    }

    // Compute E[C_1]
    double C_1 = (sum / (1.0 * N)); 

    // Compute discounted option value at t = 0
    double premium = exp(-r) * C_1; 

    cout << "The numerical solution of option fair price is " << premium;

}