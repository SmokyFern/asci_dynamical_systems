#pragma once

#include <memory>
#include <Eigen/LU>

#define MAX_ARRAY_SIZE 500

class ASCIPlotter {

    public:
        ASCIPlotter(int canvas_width, int canvas_length);

        void provide_data_3d(Eigen::MatrixXd data_3d);
        void provide_data_2d(Eigen::MatrixXd data_2d);
        void plot_asci();
        void compute_projection(Eigen::MatrixXd data_3d, double x_scale, 
                                                         double y_scale,
                                                         double depth_offset);
    private:
        // void compute_projection(Eigen::MatrixXd data_3d, double x_scale, 
        //                                                  double y_scale,
        //                                                  double depth_offset);
        Eigen::MatrixXd rotate3d(Eigen::MatrixXd data_3d);
        Eigen::MatrixXd rotate2d(Eigen::MatrixXd data_2d);
    
    private:
        Eigen::Vector3d m_light_direction = {0., 1., 1.};

        char m_output[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
        double m_zbuffer[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

        Eigen::MatrixXd m_plotting_data;
        Eigen::VectorXi m_x_proj;
        Eigen::VectorXi m_y_proj;
        Eigen::VectorXd m_ooz;

        int m_canvas_width;
        int m_canvas_height;

};