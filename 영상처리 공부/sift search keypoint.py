# -*- coding: utf-8 -*-
"""
source reference

https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_feature2d/py_feature_homography/py_feature_homography.html
https://github.com/opencv/opencv/issues/6487
"""
import cv2
from matplotlib import pyplot as plt

MIN_MATCH_COUNT = 10

img1 = cv2.imread('image/testImage.png')
gray1= cv2.cvtColor(img1,cv2.COLOR_BGR2GRAY)

# Initiate SIFT detector
sift = cv2.xfeatures2d.SIFT_create()

# find the keypoints and descriptors with SIFT
kp1, des1 = sift.detectAndCompute(img1,None)

cv2.drawKeypoints(gray1,kp1,img1)

fig = plt.figure()
fig.set_size_inches((15,15))
plt.imshow(img1, 'gray'),plt.show()
