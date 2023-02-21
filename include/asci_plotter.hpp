#pragma once

#include <memory>
#include <Eigen/LU>

#define MAX_ARRAY_SIZE 500

class ASCIPlotter {

    public:
        ASCIPlotter(std::string list_of_used_characters, int canvas_width, int canvas_length);

        void provide_data_3d(const Eigen::MatrixXd &data_3d);
        void provide_data_2d(const Eigen::MatrixXd &data_2d);
        void plot_asci();
        void compute_projection(const Eigen::MatrixXd &data_3d, double x_scale, 
                                                                double y_scale,
                                                                double depth_offset);
    private:
        // void compute_projection(const Eigen::MatrixXd &data_3d, double x_scale, 
        //                                                         double y_scale,
        //                                                         double depth_offset);
        void create_rotation_matrix(double alpha, double beta, double gamma);
        Eigen::MatrixXd rotate3d(const Eigen::MatrixXd &data_3d);
        Eigen::MatrixXd rotate2d(const Eigen::MatrixXd &data_2d);
    
    private:
        Eigen::Matrix3d m_R3d;
        Eigen::Matrix2d m_R2d;
        Eigen::Vector3d m_light_direction = {0., 1., 1.};

        std::string m_used_symbols;
        int m_idx_coeff;

        char m_output[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

        int m_elements_number;
        int m_canvas_width;
        int m_canvas_height;

};