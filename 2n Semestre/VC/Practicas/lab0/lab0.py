######################################################################
### VC i PSIV                                                      ###
### Lab 0 (basat en material de Gemma Rotger)                      ###
######################################################################


# Hello! Welcome to the computer vision LAB. 
import time
import cv2
import numpy as np
#from matplotlib import pyplot as plt
import matplotlib.pyplot as plt
import matplotlib.image as mpimg


## PROBLEM 1 (+0.5) --------------------------------------------------
# TODO. READ THE CAMERAMAN IMAGE. 
camera_path = "img/cameraman.jpg"
img=plt.imread(camera_path)

## PROBLEM 2 (+0.5) --------------------------------------------------
# TODO: SHOW THE CAMERAMAN IMAGE
plt.imshow(img, "gray")
plt.show()

## PROBELM 3 (+2.0) --------------------------------------------------
# TODO. Negative efect using a double for instruction

t=time.time()
# Your code goes here
# im_neg = ...

im_neg = np.zeros_like(img)
for i in range(np.shape(img)[0]):
    for j in range(np.shape(img)[1]):
        im_neg[i][j] = 255 - img[i][j]


elapsed=time.time()-t
print('Elapsed time is '+str(elapsed)+' seconds')

plt.imshow(im_neg,'gray')
plt.show()

# TODO. Negative efect using a vectorial instruction

t=time.time()
im_neg2 = - img
plt.imshow(im_neg2, "gray")
plt.show()
elapsed=time.time()-t
print('Elapsed time is '+str(elapsed)+' seconds')

# You sould see that results in figures 1 and 2 are the same but times
# are much different.

## PROBLEM 4 (+2.0) --------------------------------------------------

# TODO. Give some color (red, green or blue)

r = img
g = im_neg
b = img

im_col = np.zeros((256,256,3)).astype(int)

im_col[:,:,0] = r
im_col[:,:,1] = g
im_col[:,:,2] = b

plt.imshow(im_col)
plt.show()


# im_col = np.dstack...
# plt.imshow(im_col)
# plt.show()

im_col2 = np.dstack((r,g,b))
plt.imshow(im_col2)
plt.show()

## PROBLEM 5 (+1.0) --------------------------------------------------

# cv2.imwrite ...
# cv2.imwrite ...
# cv2.imwrite ...
cv2.imwrite("outputs/img_final.jpg",im_col)
cv2.imwrite("outputs/img_final.bmp",im_col)
cv2.imwrite("outputs/img_final.tif",im_col)
cv2.imwrite("outputs/img_final.png",im_col)

## PROBLEM 6 (+1.0) --------------------------------------------------

lin128=img[127,:]
plt.plot(lin128)
med = np.mean(lin128)
plt.hlines(med, 0, len(lin128), "r")
plt.show()

lin128rgb=im_col[127,:]
plt.plot(lin128rgb)
med2 = np.mean(lin128rgb)
plt.hlines(med2, 0, len(lin128rgb), "r")
plt.show()

## PROBLEM 7 (+2) ----------------------------------------------------

# TODO. Compute the histogram.
t=time.time()
hist,bins = np.histogram(img)
elapsed=time.time()-t
print('Elapsed time is '+str(elapsed)+' seconds')

plt.hist(img.reshape(256*256))
plt.show()

t=time.time()
h=np.zeros((256)).astype(int)
for i in range(len(h)):
    h[i] = np.count_nonzero(img==i)
plt.hist(img.reshape(256*256))
plt.show()

elapsed=time.time()-t
print('Elapsed time is '+str(elapsed)+' seconds')

## PROBLEM 8 Binarize the image text.png (+1) ------------------------

# TODO. Read the image
imtext = plt.imread("img/alice.jpg")
imtext = 0.299 * imtext[:,:,0] + 0.587 * imtext[:,:,1] + 0.114 * imtext[:,:,2]
plt.imshow(imtext, 'gray')
plt.show()

plt.hist(imtext.reshape(680*890))
plt.show()

# TODO. Define 3 different thresholds
th1 = 230
th2 = 190
th3 = 125

# TODO. Apply the 3 thresholds 5 to the image
threshimtext1 = imtext[:,:] > th1
threshimtext2 = imtext[:,:] > th2
threshimtext3 = imtext[:,:] > th3

# TODO. Show the original image and the segmentations in a subplot
fig, ax = plt.subplots(nrows=2, ncols=3);
ax[0,0].remove()
ax[0,1].imshow(imtext, "gray")
ax[0,1].set_title('Original image')
ax[0,2].remove()
ax[1,0].imshow(threshimtext1, "gray")
ax[1,1].imshow(threshimtext2, "gray")
ax[1,2].imshow(threshimtext3, "gray")
plt.show()


## THE END -----------------------------------------------------------
# Well done, you finished this lab! Now, remember to deliver it 
# properly on Caronte.

# File name:
# lab0_NIU.zip 
# (put matlab file lab0.m and python file lab0.py in the same zip file)
# Example lab0_1234567.zip

















