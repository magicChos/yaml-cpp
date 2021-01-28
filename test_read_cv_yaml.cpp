/************************************************************************************************
@filename    :test_read_cv_yaml.cpp
@brief       :测试利用opencv读取yaml文件
@time        :2021/01/13 14:06:39
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
***********************************************************************************************/

#include <iostream>
#include <memory>
#include "readyaml.h"
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Core>
#include <opencv2/core/eigen.hpp>

Eigen::Matrix4d Mat2Matrix4d(cv::Mat R)
{
    Eigen::Matrix4d T;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            T(i, j) = R.at<double>(i, j);
        }
    }
    return T;
}

Eigen::Matrix3d Mat2Matrix3d(cv::Mat R)
{
    Eigen::Matrix3d T;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            T(i, j) = R.at<double>(i, j);
        }
    }
    return T;
}

Eigen::MatrixXd Mat2MatrixXd(cv::Mat &R)
{
    Eigen::MatrixXd T(R.rows, R.cols);
    cv::cv2eigen(R, T);
    return T;
}

int main(int argc, char **argv)
{
    std::string yaml_file = "/home/han/data/project/yaml-cpp/camera_param.yaml";

    std::shared_ptr<YamlReader> yaml_obj = std::make_shared<YamlReader>(yaml_file);
    cv::Mat camera_matrix;
    yaml_obj->getNodeMatrix("camera_matrix", camera_matrix);

    // Eigen::Matrix3d camera_m = Mat2Matrix3d(camera_matrix);
    // std::cout << camera_m << std::endl;

    // Eigen::MatrixXd temp1(camera_matrix.rows , camera_matrix.cols);
    // cv::cv2eigen(camera_matrix , temp1);
    // std::cout << temp1 << std::endl;

    Eigen::Matrix3d temp1 = Mat2MatrixXd(camera_matrix);
    std::cout << temp1(0 ,0) << std::endl;

    return 1;
}