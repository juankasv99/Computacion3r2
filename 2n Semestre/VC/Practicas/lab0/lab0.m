%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% VC i PSIV                                                      %%%
%%% Lab 0 (basat en les pr�ctiques de Gemma Rotger)                %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% 
% Hello! Welcome to the computer vision LAB. This is a section, and 
% you can execute it using the run section button on the top panel. If 
% you prefer, you can run all the code using the run button. Run this 
% section when you need to clear your data, figures and console 
% messages.
clearvars,
close all,
clc,

% With addpath you are adding the image path to your main path
% addpath('img')


%% PROBLEM 1 (+0.5) --------------------------------------------------
% TODO. READ THE CAMERAMAN IMAGE. 

img = imread("img/cameraman.jpg");

%% PROBLEM 2 (+0.5) --------------------------------------------------
% TODO: SHOW THE CAMERAMAN IMAGE
imshow(img);


%% PROBELM 3 (+2.0) --------------------------------------------------
% TODO. Negative efect using a double for instruction

tic,
% Your code goes here
im_neg = zeros(256,256,"uint8");
for i = 1:256
    for j = 1:256
        im_neg(i,j) = 255 - img(i,j);
    end
end
figure(1)
imshow(im_neg);
toc

% TODO. Negative efect using a vectorial instruction

tic,
im_neg = 255 - img;
figure(2)
imshow(im_neg);
toc,

% You sould see that results in figures 1 and 2 are the same but times
% are much different.

%% PROBLEM 4 (+2.0) --------------------------------------------------

% TODO. Give some color (red, green or blue)
r = img;
g = im_neg;
b = img;

im_col = zeros(256, 256, 3, "uint8");
im_col(:,:,1)= r;
im_col(:,:,2)= g;
im_col(:,:,3)= b;
figure(1)
imshow(im_col);

im_col = cat(3, r, g, b);
figure(2)
imshow(im_col);


%% PROBLEM 5 (+1.0) --------------------------------------------------

imwrite(im_col, "outputs/img_final.bmp");
imwrite(im_col, "outputs/img_final.jpg");
imwrite(im_col, "outputs/img_final.png");
imwrite(im_col, "outputs/img_final.tif");


%% PROBLEM 6 (+1.0) --------------------------------------------------

lin128=img(128,:);
figure(1)
plot(lin128);

lin128rgb=im_col(128,:);
figure(2)
plot(lin128rgb);


%% PROBLEM 7 (+2) ----------------------------------------------------

tic;
imhist(img);
toc;


% TODO. Compute the histogram.
tic;
h=zeros(1,256);
for i = 1:256
    h(i) = nnz(img == i);
end
plot(h)
toc;

%% PROBLEM 8 Binarize the image text.png (+1) ------------------------

% TODO. Read the image
imtext = imread("img/alice.jpg");
imtext = rgb2gray(imtext);
figure(1)
imshow(imtext)
imhist(imtext)

% TODO. Define 3 different thresholds
th1 = 230;
th2 = 190;
th3 = 125;

% TODO. Apply the 3 thresholds 5 to the image
threshimtext1 = imtext > th1;
threshimtext2 = imtext > th2;
threshimtext3 = imtext > th3;

% TODO. Show the original image and the segmentations in a subplot
figure(1)
subplot(2,1,1);
imshow(imtext);
subplot(2,3,4);
imshow(threshimtext1);
subplot(2,3,5);
imshow(threshimtext2);
subplot(2,3,6);
imshow(threshimtext3);
title('Original image');


%% THE END -----------------------------------------------------------
% Well done, you finished this lab! Now, remember to deliver it 
% properly on Caronte.

% File name:
% lab0_NIU.zip 
% (put matlab file lab0.m and python file lab0.py in the same zip file)
% Example lab0_1234567.zip

















