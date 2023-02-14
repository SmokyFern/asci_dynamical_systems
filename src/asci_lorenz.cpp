#include <iostream>
#include <unistd.h>
#include "mesh_generator.hpp"
#include "dynamical_systems.hpp"
#include "integrators.hpp"
#include "asci_plotter.hpp"

namespace dyns = dynamical_systems;
namespace intrs = integrators;

ASCIPlotter plotter(200, 40);

std::unique_ptr<dyns::DynamicalSystem> lorenz_sys;
MeshGenerator3D cube_of_points(-0.1, 0.1, 10);

Eigen::MatrixXd states;
Eigen::MatrixXd lorenz_offset = Eigen::MatrixXd::Zero(1, 3);

int main() {

    std::printf("\x1b[2J");

    lorenz_sys = std::make_unique<dyns::LorenzSystem>(10., 8./3., 28.);
    states = cube_of_points.get_meshgrid();

    intrs::RungeKuttaVectorized integrator(lorenz_sys, 0.01);

    while (true) {

        states = integrator.update(states);

        plotter.compute_projection(states, 1000., 150., 250.);
        plotter.plot_asci();

        usleep(10000);

    }

    return 0;

}

