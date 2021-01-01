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

static void project_point_to_pixel(cv::Point2i &project_xy, const cv::Mat &cameraMat, const cv::Mat &distCoeff, const cv::Point3f &point)
{
    double x = point.x / point.z;
    double y = point.y / point.z;

    std::cout << "x: " << x << " y: " << y << std::endl;

    double r2 = x * x + y * y;
    double k1 = distCoeff.at<float>(0, 0);
    double k2 = distCoeff.at<float>(0, 1);
    double p1 = distCoeff.at<float>(0, 2);
    double p2 = distCoeff.at<float>(0, 3);
    double k3 = distCoeff.at<float>(0, 4);

    double f = 1 + k1 * r2 + k2 * r2 * r2 ;
    x *= f;
    y *= f;

    double fx = cameraMat.at<float>(0, 0);
    double fy = cameraMat.at<float>(1, 1);
    double cx = cameraMat.at<float>(0, 2);
    double cy = cameraMat.at<float>(1, 2);

    project_xy.x = static_cast<int>(x * fx + cx);
    project_xy.y = static_cast<int>(y * fy + cy);
}

static void createCarline(std::vector<cv::Point3f> &left_car_line, std::vector<cv::Point3f> &right_car_line);

static void drawCarline(cv::Mat &img_src, const std::vector<cv::Point3f> &left_car_line, const std::vector<cv::Point3f> &right_car_line, const cv::Mat &cameraMat, const cv::Mat &distCoef);

int main(int argc, char **argv)
{

    std::cout << "hello yaml!\n";
    const std::string yaml_file = "/home/han/data/project/yaml-cpp/9-27-result-test.yaml";
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

    std::string imageName = "/home/han/data/project/yaml-cpp/image/66.jpg";
    cv::Mat img = cv::imread(imageName);
    if (!img.data)
    {
        std::cerr << "read image failture!\n";
        return 0;
    }

    std::vector<cv::Point3f> car_left_line, car_right_line;
    createCarline(car_left_line, car_right_line);

    std::cout << "----------------------------\n";
    for (auto pt : car_left_line)
    {
        std::cout << pt << " " << std::endl;
    }
    std::cout << "----------------------------\n";
    drawCarline(img, car_left_line, car_right_line, cameraMat, distCoeff);
    
    cv::imwrite("drawCar.jpg", img);
    cv::imshow("image", img);
    cv::waitKey(0);

    return 1;
}

template <typename _Tp>
cv::Mat convertVector2Mat(std::vector<_Tp> v, int channels, int rows)
{
    cv::Mat mat = cv::Mat(v);                           //将vector变成单列的mat
    cv::Mat dest = mat.reshape(channels, rows).clone(); //PS：必须clone()一份，否则返回出错
    return dest;
}

void createCarline(std::vector<cv::Point3f> &left_car_line, std::vector<cv::Point3f> &right_car_line)
{
    left_car_line.emplace_back(cv::Point3f(0.145, 0.1, 0.1));
    right_car_line.emplace_back(cv::Point3f(-0.145, 0.1, 0.1));
    for (int i = 1; i < 5; ++i)
    {
        left_car_line.emplace_back(cv::Point3f(0.145, 0.1, 0.5 * i));
        right_car_line.emplace_back(cv::Point3f(-0.145, 0.1, 0.5 * i));
    }
}

void drawCarline(cv::Mat &img_src, const std::vector<cv::Point3f> &left_car_line, const std::vector<cv::Point3f> &right_car_line, const cv::Mat &cameraMat, const cv::Mat &distCoef)
{
    std::vector<cv::Point2i> left_line_pixel, right_line_pixel;

    // left line
    for (auto left_pt : left_car_line)
    {
        cv::Point2i tmp;
        project_point_to_pixel(tmp, cameraMat, distCoef, left_pt);
        std::cout << "tmp: " << tmp << std::endl;
        left_line_pixel.emplace_back(tmp);
    }

    for (auto right_pt : right_car_line)
    {
        cv::Point2i tmp;
        project_point_to_pixel(tmp, cameraMat, distCoef, right_pt);
        right_line_pixel.emplace_back(tmp);
    }

    cv::Point2i start_pt = left_line_pixel[0];
    cv::Point2i end_pt = left_line_pixel[left_line_pixel.size() - 1];
    cv::line(img_src, start_pt, end_pt, cv::Scalar(0, 0, 255), 2);

    std::cout << "left start_pt: " << start_pt << "       end_pt: " << end_pt << std::endl;

    start_pt = right_line_pixel[0];
    end_pt = right_line_pixel[right_line_pixel.size() - 1];

    std::cout << "right start_pt: " << start_pt << "       end_pt: " << end_pt << std::endl;
    cv::line(img_src, start_pt, end_pt, cv::Scalar(0, 0, 255), 2);

    for (int i = 0; i < left_line_pixel.size(); ++i)
    {
        cv::Point2i left_pt = left_line_pixel[i];
        cv::Point2i right_pt = right_line_pixel[i];

        std::cout << "left_pt: " << left_pt << "      right_pt: " << right_pt << std::endl;
        cv::line(img_src, left_pt, right_pt, cv::Scalar(0, 0, 255), 1);
    }
}