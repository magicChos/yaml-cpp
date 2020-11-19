#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/***************** Mat转vector **********************/
template <typename _Tp>
vector<_Tp> convertMat2Vector(const Mat &mat)
{
    return (vector<_Tp>)(mat.reshape(1, 1)); //通道数不变，按行转为一行
}

/****************** vector转Mat *********************/
template <typename _Tp>
cv::Mat convertVector2Mat(std::vector<_Tp> v, int channels, int rows)
{
    cv::Mat mat = cv::Mat(v);                           //将vector变成单列的mat
    cv::Mat dest = mat.reshape(channels, rows).clone(); //PS：必须clone()一份，否则返回出错
    return dest;
}




int main(int argc, char **argv)
{
    YAML::Node config;
    try
    {
        if (argc != 2)
        {
            std::cerr << "usage: exe config.yaml" << std::endl;
            return 0;
        }
        std::cout << "file: " << argv[1] << std::endl;
        config = YAML::LoadFile(argv[1]);
    }
    catch (YAML::BadFile &e)
    {
        std::cerr << "read error!" << e.what() << std::endl;
        return -1;
    }
    std::cout << "Node type: " << config.Type() << std::endl;

    std::vector<float> cameraMat = config["CameraMat"]["data"].as<std::vector<float>>();

    for (auto i : cameraMat)
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::vector<float> distCoeff = config["DistCoeff"]["data"].as<std::vector<float>>();

    cv::Mat distCoeffMat = cv::Mat(distCoeff);
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << distCoeffMat << std::endl;

    cv::Mat camera_mat = convertVector2Mat<float>(cameraMat, 1, 3);
    std::cout << camera_mat << std::endl;

    return 1;
}