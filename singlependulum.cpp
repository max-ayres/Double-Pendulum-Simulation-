#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <chrono>

//elapsed pendulum time from release, swings in real time
// double calculateDuration(const std::chrono::time_point<std::chrono::steady_clock>& time0) {
//     auto end = std::chrono::steady_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - time0).count();
//     return static_cast<double>(duration) * pow(10, -6);
// }

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
    double time = 0.0;
    double dt = 0.01;

    std::cout << "Enter a pendulum bob mass: ";
    std::cin >> m;
    std::cout << "Enter a pendulum arm length: ";
    std::cin >> L;
    std::cout << "Enter an initial angle for the pendulum to start from (between -180 and 180 degrees): ";
    std::cin >> theta;

    //calculate time period and ang frequency

    double T = 2.0 * M_PI * sqrt(L/g);
    double omega = 0.0;

    //runge kutta variables
    double k1_theta;
    double k2_theta;
    double k3_theta;
    double k4_theta;
    double k1_omega;
    double k2_omega;
    double k3_omega;
    double k4_omega;
    double h = 0.01;

    theta *= M_PI/180.0;

    //set up figure window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Penduum Window");
    sf::Font font;

    //reference time to find time from releasing the pendulum
    auto time0 = std::chrono::steady_clock::now();
    
    while (time <= 2){
        //time at current frame
        sf::Text text(std::to_string(time), font, 50);

        //implement runge kutta
        k1_theta = h * omega;
        k1_omega = h * angacc(theta, g, L);

        k2_theta = h * (omega + 0.5 * k1_omega);
        k2_omega = h * angacc(theta + 0.5 * k1_theta, g, L);

        k3_theta = h * (omega + 0.5 * k2_omega);
        k3_omega = h * angacc(theta + 0.5 * k2_theta, g, L);

        k4_theta = h * (omega + k3_omega);
        k4_omega = h * angacc(theta + k3_theta, g, L);

        theta += (1.0/6.0) * (k1_theta + 2.0 * k2_theta + 2.0 * k3_theta + k4_theta);
        omega += (1.0/6.0) * (k1_omega + 2.0 * k2_omega + 2.0 * k3_omega + k4_omega);

        time += dt;
        sleep(10);

        window.clear();
    }

    return 0;
}

