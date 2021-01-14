#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@filename    :yaml_reader.py
@brief       :cv2封装yaml 
@time        :2021/01/14 09:39:13
@author      :hscoder
@versions    :1.0
@email       :hscoder@163.com
@usage       :
'''
import cv2
import numpy as np

class YamlReader(object):
    def __init__(self , yaml_file):
        self.fs = cv2.FileStorage(yaml_file , cv2.FILE_STORAGE_READ)
        
    def getRealNode(self , node_name):
        return self.fs.getNode(node_name).real()
    
    def getStrNode(self , node_name):
        return self.fs.getNode(node_name).string()
    
    def getMatNode(self , node_name):
        return self.fs.getNode(node_name).mat()
    
    
    
