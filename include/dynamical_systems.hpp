#pragma once

#include <Eigen/LU>

namespace dynamical_systems {

    class DynamicalSystem {

        public:
            virtual Eigen::MatrixXd get_right_hand_side(const Eigen::MatrixXd &current_state) { 
                
                return current_state; 
                
            }

    };

    class LorenzSystem : public DynamicalSystem {

        public:
            LorenzSystem(double sigma, double beta, double rho);
            Eigen::MatrixXd get_right_hand_side(const Eigen::MatrixXd &current_state);

        private:
            double m_sigma;
            double m_beta;
            double m_rho;
            
            int dimensionality = 3;

    };

}