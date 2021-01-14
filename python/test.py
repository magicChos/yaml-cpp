#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@filename    :test.py
@brief       :
@time        :2021/01/14 09:49:40
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
'''

from yaml_reader import  YamlReader
from yaml_writer import YamlWriter
import numpy as np


def main():
    yaml_writer_obj = YamlWriter("test.yaml")
    yaml_writer_obj.write("name" , "hanshuo")
    yaml_writer_obj.write("year" , "1990")
    yaml_writer_obj.write("mat" , np.array([[1 , 2] , [3 , 4]]))
    yaml_writer_obj.close()
    
    yaml_reader_obj = YamlReader("test.yaml")
    name = yaml_reader_obj.getStrNode("name")
    year = yaml_reader_obj.getStrNode("year")
    mat  = yaml_reader_obj.getMatNode("mat")
    
    print("name: " , name)
    print("year: " , year)
    print("mat:  " , mat)
    
    

if __name__ == '__main__':
    main()
    