#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@filename    :yaml_writer.py
@brief       :cv2写入yaml封装
@time        :2021/01/14 09:45:14
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
'''

import cv2
import numpy as np

class YamlWriter(object):
    def __init__(self , yaml_file):
        self.fs = cv2.FileStorage(yaml_file , cv2.FILE_STORAGE_WRITE)
        
    def write(self , node_name, data):
        self.fs.write(node_name , data)
        
    def close(self):
        self.fs.release()
        
