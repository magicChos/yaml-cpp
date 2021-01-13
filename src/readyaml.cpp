#include "readyaml.h"

YamlReader::YamlReader(const std::string &yaml_file)
{
    storage_ = cv::FileStorage(yaml_file, cv::FileStorage::READ);
}

cv::Mat YamlReader::getNodeMatrix(const std::string node_name)
{
    cv::Mat mat = storage_[node_name].mat();
    return mat;
}
