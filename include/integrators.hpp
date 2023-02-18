#pragma once

#include <memory>
#include <Eigen/LU>
#include "dynamical_systems.hpp"

namespace dyns = dynamical_systems;

namespace integrators {

    class Integrator {

        public:
            virtual Eigen::MatrixXd update(const Eigen::MatrixXd &current_state) {
                
                return current_state;
                
            }

        private:
            virtual Eigen::MatrixXd get_right_hand_side(const Eigen::MatrixXd &current_state) {

                return current_state;

            }

    };

    class RungeKuttaVectorized : public Integrator {

        public:
            RungeKuttaVectorized(std::unique_ptr<dyns::DynamicalSystem> &dyn_sys, double dt);
            Eigen::MatrixXd update(const Eigen::MatrixXd &current_state);

        private:
            Eigen::MatrixXd get_right_hand_side(const Eigen::MatrixXd &current_state);

        private:
            double m_dt;
            std::unique_ptr<dyns::DynamicalSystem> m_dyn_sys;

    };

    class ForwardEulerVectorized : public Integrator {

        public:
            ForwardEulerVectorized(std::unique_ptr<dyns::DynamicalSystem> &dyn_sys, double dt);
            Eigen::MatrixXd update(const Eigen::MatrixXd &current_state);

        private:
            Eigen::MatrixXd get_right_hand_side(const Eigen::MatrixXd &current_state);

        private:
            double m_dt;
            std::unique_ptr<dyns::DynamicalSystem> m_dyn_sys;

    };

}