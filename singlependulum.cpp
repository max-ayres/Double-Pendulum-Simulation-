#include <iostream>
#include <cmath>
//#include <SFML/Graphics.hpp>
#include <time.h>
#include <chrono>

//elapsed pendulum time from release, swings in real time
double calculateDuration(const std::chrono::time_point<std::chrono::steady_clock>& time0) {
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - time0).count();
    return static_cast<double>(duration) * pow(10, -6);
}

//angular acceleration
double angacc(double theta, double g, double L){
    return -(g/L)*sin(theta);
}

int main()
{   
    //constants
    const double g = -9.81;

    //prompts and inputs
    double m;
    double L;
    double theta;
    double time;

    std::cout << "Enter a pendulum bob mass: ";
    std::cin >> m;
    std::cout << "Enter a pendulum arm length: ";
    std::cin >> L;
    std::cout << "Enter an initial angle for the pendulum to start from (between -+pi/2): ";
    std::cin >> theta;

    //calculate time period and ang frequency

    double T = 2 * M_PI * sqrt(L/g);
    double omega = (2 * M_PI)/T;

    //runge kutta variables
    double k1_theta;
    double k2_theta;
    double k3_theta;
    double k4_theta;
    double k1_omega;
    double k2_omega;
    double k3_omega;
    double k4_omega;
    double h = 0.1;

    //reference time to find time from releasing the pendulum
    auto time0 = std::chrono::steady_clock::now();
    
    while (calculateDuration(time0) <= 2){
        //time at current frame
        time = calculateDuration(time0);

        //implement runge kutta
        k1_theta = h * omega;
        k1_omega = h * angacc(theta, g, L);

        k2_theta = h * (omega + 0.5 * k1_omega);
        k2_omega = h * angacc(theta + 0.5 * k1_theta, g, L);

        k3_theta = h * (omega + 0.5 * k2_omega);
        k3_omega = h * angacc(theta + 0.5 * k2_theta, g, L);

        k4_theta = h * (omega + k3_omega);
        k4_omega = h * angacc(theta + k3_theta, g, L);

        theta += (1/6) * (k1_theta + 2 * k2_theta + 2 * k3_theta + k4_theta);
        omega += (1/6) * (k1_omega + 2 * k2_omega + 2 * k3_omega + k4_omega);

        std::cout << theta << '\n';
        std::cout << time << '\n';
        std::cout << omega << '\n';
    }

    std::cout << '\n' << calculateDuration(time0);

    return 0;
}

//add feature that changes the framerate
