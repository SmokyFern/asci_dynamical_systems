#pragma once

#include <Eigen/LU>
#include <math.h>

#define NUMBER_OF_AXIS 3

class MeshGenerator3D {

    public:
        MeshGenerator3D(double start, double end, int points_per_axis);
        Eigen::MatrixXd get_meshgrid();

    private:
        void generate_mesh();

    private:
        int m_points_per_axis;
        int m_number_of_points;

        Eigen::MatrixXd m_meshgrid;
        Eigen::VectorXd m_meshgrid_range;

};