"""
# source
https://www.youtube.com/watch?v=XZyPlNSzTzw
https://www.learnopencv.com/image-alignment-feature-based-using-opencv-c-python/
https://github.com/jagracar/OpenCV-python-tests/blob/master/OpenCV-tutorials/featureDetection/homography.py
https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_feature2d/py_feature_homography/py_feature_homography.html

video
https://www.learnopencv.com/object-tracking-using-opencv-cpp-python/
http://blog.christianperone.com/2015/01/real-time-drone-object-tracking-using-python-and-opencv/
"""

import cv2
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

GOOD_MATCH_PERCENT = 0.02

searchImgName = "image/picture_art_d.jpg"
backImgName = "image/frame.png"

searchImg = cv2.imread(searchImgName, 0)
backImg = cv2.imread(backImgName, 0)

# convert L is gray color OR RGB
# To show the final result in color
searchBW = np.array(Image.open(searchImgName).convert("RGB"))
backBW = np.array(Image.open(backImgName).convert("RGB"))
 
#sift = cv2.xfeatures2d.SIFT_create()
surf = cv2.xfeatures2d.SURF_create()
 
#key1, des1 = sift.detectAndCompute(searchImg, None)
key1, des1 = surf.detectAndCompute(searchImg, None)

#key2, des2 = sift.detectAndCompute(backImg, None)
key2, des2 = surf.detectAndCompute(backImg, None)

bf = cv2.BFMatcher()
matches = bf.match(des1,des2)
matches = sorted(matches, key = lambda m: m.distance)

# Remove not so good matches
numGoodMatches = int(len(matches) * GOOD_MATCH_PERCENT)
matches = matches[:numGoodMatches]

# Extract location of good matches
points1 = np.zeros((len(matches), 2), dtype=np.float32)
points2 = np.zeros((len(matches), 2), dtype=np.float32)
 
for i, match in enumerate(matches):
    points1[i, :] = key1[match.queryIdx].pt
    points2[i, :] = key2[match.trainIdx].pt
   
# Find homography
h, mask = cv2.findHomography(points1, points2, cv2.RANSAC)

# Draw Rectangle
height,width = searchImg.shape
pts = np.float32([ [0,0],[0,height-1],[width-1,height-1],[width-1,0] ]).reshape(-1,1,2)
dst = cv2.perspectiveTransform(pts,h)

backBW = cv2.polylines(backBW,[np.int32(dst)],True,(255,0,0),3, cv2.LINE_AA)

fig = plt.figure()
fig.set_size_inches((17,17))
# Draw the matches
matchesMask = mask.ravel().tolist()
drawParameters = dict(matchColor=(0, 255, 0), singlePointColor=None, matchesMask=matchesMask, flags=2)

resImg = cv2.drawMatches(searchBW, key1, backBW, key2, matches, None, **drawParameters)
plt.imshow(resImg)
cv2.imwrite("resImg.jpg",resImg)