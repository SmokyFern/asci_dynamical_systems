#include <iostream>
#include "dynamical_systems.hpp"

namespace dynamical_systems {

    LorenzSystem::LorenzSystem(double sigma, double beta, double rho) : m_sigma(sigma),
                                                                        m_beta(beta),
                                                                        m_rho(rho) {}

    Eigen::MatrixXd LorenzSystem::get_right_hand_side(const Eigen::MatrixXd &current_state) {

        Eigen::MatrixXd rhs(current_state.rows(), 3);
        Eigen::VectorXd x, y, z, dx, dy, dz;

        x = current_state.col(0);
        y = current_state.col(1); 
        z = current_state.col(2); 

        // /* Compute right hand side of ODE */
        dx = m_sigma * (y.array() - x.array());
        dy = x.array() * (m_rho - z.array()) - y.array();
        dz = x.array() * y.array() - m_beta * z.array();

        rhs << dx, dy, dz;
        return rhs;
        
    }

}