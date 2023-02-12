#include "mesh_generator.hpp"

MeshGenerator3D::MeshGenerator3D(double start, double end, int points_per_axis) {
            
    m_points_per_axis = points_per_axis;
    m_number_of_points = std::pow(points_per_axis, NUMBER_OF_AXIS);

    m_meshgrid = Eigen::MatrixXd::Zero(m_number_of_points, NUMBER_OF_AXIS);
    m_meshgrid_range = Eigen::VectorXd::LinSpaced(points_per_axis, start, end);

    generate_mesh();

};

void MeshGenerator3D::generate_mesh() {

    /* Number of points per 'layer' */
    int points_per_axis_sqd = std::pow(m_points_per_axis, 2);

    /* Dummy matrices */            
    Eigen::MatrixXd dummy_mesh = m_meshgrid_range.rowwise().replicate(points_per_axis_sqd);
    Eigen::Map<Eigen::MatrixXd> dummy_mesh_reshaped(dummy_mesh.data(), points_per_axis_sqd, m_points_per_axis);

    /* Create x coordinates for each point */
    Eigen::VectorXd x_coordinates = dummy_mesh_reshaped.reshaped<Eigen::RowMajor>(m_number_of_points, 1);
    /* Create y coordinates for each point */
    Eigen::VectorXd y_coordinates = dummy_mesh.reshaped<Eigen::RowMajor>(m_number_of_points, 1);
    /* Create z cooordintes for each point */
    Eigen::VectorXd z_coordinates = dummy_mesh.reshaped<Eigen::ColMajor>(m_number_of_points, 1);

    /* Put everything together */
    m_meshgrid << x_coordinates, y_coordinates, z_coordinates;

};

Eigen::MatrixXd MeshGenerator3D::get_meshgrid() {

    return m_meshgrid;

};