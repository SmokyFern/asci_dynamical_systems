#include <iostream>
#include "asci_plotter.hpp"

ASCIPlotter::ASCIPlotter(std::string list_of_used_characters, 
                         int canvas_width,
                         int canvas_height) : m_used_symbols(list_of_used_characters),
                                              m_canvas_width(canvas_width),
                                              m_canvas_height(canvas_height) {

    m_elements_number = std::pow(MAX_ARRAY_SIZE, 2);
    std::memset(m_output, ' ', m_elements_number);

    m_idx_coeff = int (list_of_used_characters.length() / std::sqrt(2));

    m_light_direction.normalize();

}

void ASCIPlotter::provide_data_3d(const Eigen::MatrixXd &data_3d) {

    // compute_projection(data_3d);

}

void ASCIPlotter::compute_projection(const Eigen::MatrixXd &data_3d, double x_scale, 
                                                                     double y_scale,
                                                                     double depth_offset) {
    
    Eigen::VectorXi x_projection, y_projection, luminance_idx;
    Eigen::VectorXd x, y, z, ooz;

    x = data_3d.col(0);
    y = data_3d.col(1);
    z = data_3d.col(2);

    /* Compute one over zed */
    ooz = 1. / (z.array() + depth_offset);

    /* Compute projections */
    x_projection = (m_canvas_width / 2 +  
                    x_scale * ooz.array() * x.array()).cast<int>();
    y_projection = (m_canvas_height / 2 -  
                    y_scale * ooz.array() * y.array()).cast<int>();

    /* Compute luminance indexis for each point */
    luminance_idx = (data_3d.rowwise().normalized() * m_light_direction * m_idx_coeff).cast<int>();

    int symbol_idx = 0;
    for (int i = 0; i < data_3d.rows(); i ++) {
        
        if (luminance_idx(i) > 0) {

            symbol_idx = luminance_idx(i);

        } else {

            symbol_idx = 0;

        }

        m_output[x_projection(i)][y_projection(i)] = m_used_symbols[symbol_idx];

    }

}

void ASCIPlotter::plot_asci() {

    /* Clear current console output */
    std::printf("\x1b[H");

    /* Output every buffer element to console */
    for (int height_idx = 0; height_idx < m_canvas_height; height_idx ++) {

        for (int width_idx = 0; width_idx < m_canvas_width; width_idx ++) {

            putchar(m_output[width_idx][height_idx]);

        }

        putchar('\n');

    }

    std::memset(m_output, ' ', m_elements_number);

}

void ASCIPlotter::create_rotation_matrix(double alpha, double beta, double gamma) {

    double sinalpha = std::sin(alpha), sinbeta = std::sin(beta), singamma = std::sin(gamma);
    double cosalpha = std::cos(alpha), cosbeta = std::cos(beta), cosgamma = std::cos(gamma);

    Eigen::Matrix3d Rx, Ry, Rz;

    Rx << 1.,     0.,       0.,
          0., cosalpha, -sinalpha,
          0., sinalpha,  cosalpha;

    Ry << cosbeta, 0., -sinbeta,
             0.,   1.,     0,
          sinbeta, 0.,  cosbeta;

    Rz << cosgamma, -singamma, 0.,
          singamma,  cosgamma, 0.,
             0.,        0.,    1.;
    
    m_R3d = Rx * Ry * Rz;

}

Eigen::MatrixXd ASCIPlotter::rotate3d(const Eigen::MatrixXd &data_3d) {

    Eigen::MatrixXd rotated_data = data_3d * m_R3d;
    return rotated_data;

}

Eigen::MatrixXd ASCIPlotter::rotate2d(const Eigen::MatrixXd &data_2d) {

    Eigen::MatrixXd rotated_data = data_2d * m_R2d;
    return rotated_data;

}
