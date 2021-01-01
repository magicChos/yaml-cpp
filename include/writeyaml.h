/************************************************************************************************
@filename    :write_yaml.cpp
@brief       :yaml写入封装
@time        :2021/01/01 17:17:52
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
***********************************************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <memory>

class YamlWriter
{
public:
    YamlWriter() = delete;
    YamlWriter(const std::string yaml_file);
    ~YamlWriter();
    
    template <typename T>
    void write(const std::string keyName, T &val)
    {
        m_fs << keyName << val;
    }

private:
    cv::FileStorage m_fs;
};