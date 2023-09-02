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

double thetamotion(double theta, double t, double g, double l){
    return -(g/l)*sin(theta);
}

int main()
{   
    //constants
    const double g = -9.81;
    double m;
    double L;
    double theta0;

    double thetah;
    double vtheta;
    double vthetah;
    double time;
    double T = 2 * M_PI * sqrt(L/g);
    double omega = (2 * M_PI)/T;

    //prompts and inputs
    std::cout << "Enter a pendulum bob mass: ";
    std::cin >> m;
    std::cout << "Enter a pendulum arm length: ";
    std::cin >> L;
    std::cout << "Enter an initial angle for the pendulum to start from (between -+pi/2): ";
    std::cin >> theta0;



    //reference time to find time from releasing the pendulum
    auto time0 = std::chrono::steady_clock::now();
    
    while (calculateDuration(time0) <= 3){
        //implement runge kutta
        time = calculateDuration(time0);

        thetah = theta0 + (time/2)*vtheta;
        vthetah = vtheta + (time/2)*thetamotion(theta0, time, g, L);
        theta0 += time*vthetah;
        vtheta += time*thetamotion(thetah, time + time/2, g, L);

        std::cout << vtheta << '\n';
    }

    std::cout << '\n' << calculateDuration(time0);

    return 0;
}
