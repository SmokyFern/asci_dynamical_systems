#include <unistd.h>
#include "mesh_generator.hpp"
#include "dynamical_systems.hpp"
#include "integrators.hpp"
#include "asci_plotter.hpp"

namespace dyns = dynamical_systems;
namespace intrs = integrators;

ASCIPlotter plotter(200, 40);

std::unique_ptr<dyns::DynamicalSystem> lorenz_sys;
MeshGenerator3D cube_of_points(-5, 5, 40);

Eigen::MatrixXd states;

int main() {


    lorenz_sys = std::make_unique<dyns::LorenzSystem>(10, 8/3, 28);
    states = cube_of_points.get_meshgrid();

    intrs::RungeKuttaVectorized integrator(lorenz_sys, 0.01);

    while (true) {

        states = integrator.update(states);

        plotter.compute_projection(states, 1000, 150, 250);
        plotter.plot_asci();

        usleep(1000);

    }

    return 0;

}

