#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;


double DELTA_t = 0.01;
random_device rd;
default_random_engine generator;

double rand_normal(double mean, double sigma){
    generator.seed(rd());
    std::normal_distribution<double> distribution(mean, sigma);
    return distribution(generator);
}


int main(){

    double K, r;
    int N;

    cout << "Initial stock price (X_0): 100\n";

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

    vector<double> v(101);
    v[0] = 100.0; // Stock price at time zero (X_0)

    double sum;

    // Run simulations for N times as specified
    for (int j=0 ; j<N ; j++){
        for (int i=1 ; i < v.size() ; i++){
            // Euler-Maruyama update
            double W_t = rand_normal(0, DELTA_t);
            v[i] = v[i-1] + 0.1 * (100 * (10 * r + 1) * exp(r * (i * 1.0)/100) - v[i-1]) * DELTA_t + 0.2 * W_t;
        }
        sum += max(v[100] - K, 0.0);
    }

    // Compute discounted option value
    double premium = exp(-r) * (sum / (1.0 * N)); 

    cout << "The analytical solution of option fair price is " << premium;

}