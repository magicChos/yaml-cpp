#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

class YamlReader
{
public:
    YamlReader() = delete;
    YamlReader(const std::string &yaml_file);
    ~YamlReader(){}

    cv::Mat getNodeMatrix(const std::string node_name);


private:
    cv::FileStorage storage_;
};