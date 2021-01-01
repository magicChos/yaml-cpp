/************************************************************************************************
@filename    :write_yaml.cpp
@brief       :测试写入yaml封装类
@time        :2021/01/01 17:47:54
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
***********************************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <memory>
#include "writeyaml.h"


int main(int argc, char **argv)
{
    std::shared_ptr<YamlWriter> yamlwriter = std::make_shared<YamlWriter>("test.yaml");
    const std::string key = "name";
    int val = 10;
    yamlwriter->write<int>(key , val);

    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    yamlwriter->write<cv::Mat>("cameraMatrix" , cameraMatrix);

    return 1;
}