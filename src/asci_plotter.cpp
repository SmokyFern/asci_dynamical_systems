#include <iostream>
#include "asci_plotter.hpp"

ASCIPlotter::ASCIPlotter(int canvas_width, int canvas_height) : m_canvas_width(canvas_width),
                                                                m_canvas_height(canvas_height) {

    m_elements_number = std::pow(MAX_ARRAY_SIZE, 2);

    std::memset(m_output, ' ', m_elements_number);
    std::memset(m_zbuffer, 0., 8 * m_elements_number);

    m_light_direction.normalize();

}

void ASCIPlotter::provide_data_3d(Eigen::MatrixXd data_3d) {

    m_plotting_data = data_3d;

    // compute_projection(m_plotting_data);

}

void ASCIPlotter::compute_projection(Eigen::MatrixXd data_3d, double x_scale, double y_scale, double depth_offset) {
    
    m_ooz = 1. / (data_3d.col(2).array() + depth_offset);

    m_x_proj = (m_canvas_width / 2 +  
               x_scale * m_ooz.array() * data_3d.col(0).array()).cast<int>();

    m_y_proj = (m_canvas_height / 2 -  
               y_scale * m_ooz.array() * data_3d.col(1).array()).cast<int>();

    for (int i = 0; i < data_3d.rows(); i ++) {

        double luminance = m_light_direction.dot(data_3d.row(i).normalized());
        int luminance_idx = luminance * 8;

       if (m_ooz(i) > m_zbuffer[m_x_proj(i)][m_y_proj(i)]) {
            
            m_zbuffer[m_x_proj(i)][m_y_proj(i)] = m_ooz(i);
            m_output[m_x_proj(i)][m_y_proj(i)] = ".,-~:;=!*#$@"[luminance_idx > 0 ? luminance_idx : 0];

       }

    }

}

void ASCIPlotter::plot_asci() {

    /* Clear current console output */
    std::printf("\x1b[H");

    for (int height_idx = 0; height_idx < m_canvas_height; height_idx ++) {

        for (int width_idx = 0; width_idx < m_canvas_width; width_idx ++) {

            putchar(m_output[width_idx][height_idx]);

        }

        putchar('\n');

    }

    std::memset(m_output, ' ', m_elements_number);

}

Eigen::MatrixXd ASCIPlotter::rotate3d(Eigen::MatrixXd data_3d) {

    return data_3d;

}

Eigen::MatrixXd ASCIPlotter::rotate2d(Eigen::MatrixXd data_2d) {

    return data_2d;

}
