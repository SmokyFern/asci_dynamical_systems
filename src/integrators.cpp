#include <iostream>
#include "integrators.hpp"

namespace integrators {

    RungeKuttaVectorized::RungeKuttaVectorized(std::unique_ptr<dyns::DynamicalSystem> &dyn_sys,
                                               double dt) : m_dt(dt), 
                                                            m_dyn_sys(std::move(dyn_sys)) {}

    Eigen::MatrixXd RungeKuttaVectorized::update(Eigen::MatrixXd current_state) {

        Eigen::MatrixXd f1, f2, f3, f4;
        f1 = get_right_hand_side(current_state);
        f2 = get_right_hand_side(current_state + m_dt/2 * f1);
        f3 = get_right_hand_side(current_state + m_dt/2 * f2);
        f4 = get_right_hand_side(current_state + m_dt * f3);

        return current_state + m_dt/6 * (f1 + 2*f2 + 2*f3 + f4);

    }

    Eigen::MatrixXd RungeKuttaVectorized::get_right_hand_side(Eigen::MatrixXd current_state) {

        return m_dyn_sys -> get_right_hand_side(current_state);

    }

    ForwardEulerVectorized::ForwardEulerVectorized(std::unique_ptr<dyns::DynamicalSystem> &dyn_sys,
                                               double dt) : m_dt(dt), 
                                                            m_dyn_sys(std::move(dyn_sys)) {}

    Eigen::MatrixXd ForwardEulerVectorized::update(Eigen::MatrixXd current_state) {

        Eigen::MatrixXd f1;
        f1 = get_right_hand_side(current_state);

        return current_state + m_dt * f1;

    }

    Eigen::MatrixXd ForwardEulerVectorized::get_right_hand_side(Eigen::MatrixXd current_state) {

        return m_dyn_sys -> get_right_hand_side(current_state);

    }

}