#include "param_handler.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace ace::common;

template <typename _Tp>
cv::Mat convertVector2Mat(std::vector<_Tp> v, int channels, int rows);

bool readCameraMatrix(const std::string yaml_file, std::vector<float> &cameraMat, std::vector<float> &distCoeff)
{
    ParamHandler paramHandler(yaml_file);
    if (!paramHandler.FileOpenedSuccessfully())
    {
        return false;
    }

    paramHandler.GetValue<std::vector<float>>("CameraMat", "data", cameraMat);
    paramHandler.GetValue<std::vector<float>>("DistCoeff", "data", distCoeff);

    return true;
}

static void project_point_to_pixel(float pixel[2], cv::Mat &cameraMat, cv::Mat &distCoeff, const float point[3])
{
    double x = point[0] / point[2];
    double y = point[1] / point[2];

    double r2 = x * x + y * y;
    double k1 = distCoeff.at<float>(0, 0);
    double k2 = distCoeff.at<float>(0, 1);
    double p1 = distCoeff.at<float>(0, 2);
    double p2 = distCoeff.at<float>(0, 3);
    double k3 = distCoeff.at<float>(0, 4);

    double f = 1 + k1 * r2 + k2 * r2 * r2 + k3 * k2 * r2 * r2 * r2;
    x *= f;
    y *= f;

    double dx = x + 2 * p1 * x * y + p2 * (r2 + 2 * x * x);
    double dy = y + 2 * p2 * x * y + p1 * (r2 + 2 * y * y);

    x = dx;
    y = dy;

    double fx = cameraMat.at<float>(0, 0);
    double fy = cameraMat.at<float>(1, 1);
    double cx = cameraMat.at<float>(0, 2);
    double cy = cameraMat.at<float>(1, 2);

    pixel[0] = x * fx + cx;
    pixel[1] = y * fy + cy;
}

int main(int argc, char **argv)
{

    std::cout << "hello yaml!\n";
    const std::string yaml_file = "/home/han/data/project/test_code/yaml/9-27-result-test.yaml";
    std::vector<float> cameraVec, distVec;
    if (!readCameraMatrix(yaml_file, cameraVec, distVec))
    {
        std::cerr << "get camera intrinsic matrix failture!\n";
        return 0;
    }

    cv::Mat cameraMat, distCoeff;
    cameraMat = convertVector2Mat<float>(cameraVec, 1, 3);
    distCoeff = convertVector2Mat<float>(distVec, 1, 5);

    std::cout << "distCoeff: " << distCoeff;

    return 1;
}

template <typename _Tp>
cv::Mat convertVector2Mat(std::vector<_Tp> v, int channels, int rows)
{
    cv::Mat mat = cv::Mat(v);                           //将vector变成单列的mat
    cv::Mat dest = mat.reshape(channels, rows).clone(); //PS：必须clone()一份，否则返回出错
    return dest;
}