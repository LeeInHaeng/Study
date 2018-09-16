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

GOOD_MATCH_PERCENT = 0.02

searchImgName = "image/picture_art_d.jpg"
backVideoName = "image/frameVideo.mp4"

searchImg = cv2.imread(searchImgName, 0)
backVideo = cv2.VideoCapture(backVideoName)

if not backVideo.isOpened():
    print("Could not open video")
else:
    # convert L is gray color
    searchBW = np.array(Image.open(searchImgName).convert("RGB"))
    
    #sift = cv2.xfeatures2d.SIFT_create()
    surf = cv2.xfeatures2d.SURF_create()
    
    #key1, des1 = sift.detectAndCompute(searchImg, None)
    key1, des1 = surf.detectAndCompute(searchImg, None)
    
    # read first frame
    ok, frame = backVideo.read()
    
    # Define the codec and create VideoWriter object
    #frame_width = int(backVideo.get(3))
    #frame_height = int(backVideo.get(4))
    # resImg의 width와 height
    #frame_width, frame_height, channels = resImg.shape
    frame_width=2304
    frame_height=720
    resVideo = cv2.VideoWriter('surfVideo.avi',cv2.VideoWriter_fourcc('M','J','P','G'), 30, (frame_width,frame_height))
    
    while True:
        # read new frame
        ok, frame = backVideo.read()
        if not ok:
            break
        
        #key2, des2 = sift.detectAndCompute(backImg, None)
        key2, des2 = surf.detectAndCompute(frame, None)
        
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
        
        frame = cv2.polylines(frame,[np.int32(dst)],True,(255,0,0),3, cv2.LINE_AA)
    
        # Draw the matches
        matchesMask = mask.ravel().tolist()
        drawParameters = dict(matchColor=(0, 255, 0), singlePointColor=None, matchesMask=matchesMask, flags=2)
    
        resImg = cv2.drawMatches(searchBW, key1, frame, key2, matches, None, **drawParameters)

        resVideo.write(resImg)

backVideo.release()
resVideo.release()