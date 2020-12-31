#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    YAML::Node config;
    config["CameraMat"]["rows"] = 3;
    config["CameraMat"]["cols"] = 3;
    config["CameraMat"]["dt"] = 'd';
    // std::vector<float> vec=  "[-4.7414625250654539e-03, 8.5735696382268611e-01, -2.6207096090810162e-03, -1.0303374250360127e-02, -2.8458739199082417e+00]";
    config["CameraMat"]["data"] = "[-4.7414625250654539e-03, 8.5735696382268611e-01, -2.6207096090810162e-03, -1.0303374250360127e-02, -2.8458739199082417e+00]";

    ofstream fout("testconfig.xml");
    fout << config;
    fout.close();

    return 1;
}