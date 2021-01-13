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

int main(int argc, char **argv)
{
    std::string yaml_file = "/home/han/data/project/yaml-cpp/camera_param.yaml";

    std::shared_ptr<YamlReader> yaml_obj = std::make_shared<YamlReader>(yaml_file);
    cv::Mat camera_matrix = yaml_obj->getNodeMatrix("camera_matrix");
    std::cout << camera_matrix << std::endl;
    return 1;
}