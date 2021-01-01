#include "writeyaml.h"


YamlWriter::YamlWriter(const std::string yaml_file) 
{
    m_fs.open(yaml_file, cv::FileStorage::WRITE);
}

YamlWriter::~YamlWriter() 
{
    m_fs.release();
}
