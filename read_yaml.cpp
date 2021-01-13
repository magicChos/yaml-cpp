/************************************************************************************************
@filename    :read_yaml.cpp
@brief       :测试yaml读取的封装类
@time        :2021/01/01 17:53:18
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
***********************************************************************************************/

#include "param_handler.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <open3d/Open3D.h>

template <typename _Tp>
cv::Mat convertVector2Mat(std::vector<_Tp> v, int channels, int rows)
{
    cv::Mat mat = cv::Mat(v);                           //将vector变成单列的mat
    cv::Mat dest = mat.reshape(channels, rows).clone(); //PS：必须clone()一份，否则返回出错
    return dest;
}

int main(int argc, char **argv)
{
    std::string yaml_file = "/home/han/data/project/yaml-cpp/9-27-result-test.yaml";
    ParamHandler paramHandler(yaml_file);
    if (!paramHandler.FileOpenedSuccessfully())
    {
        return false;
    }

    std::vector<float> cameraMat;
    paramHandler.GetValue<std::vector<float>>("CameraMat", "data", cameraMat);
    for (auto v : cameraMat)
    {
        std::cout << v << std::endl;
    }
    return 1;
}