im = imread("./image.jpg");
%im = imread('http://www.cvc.uab.es/shared/teach/a102784/doc/images/gossos.jpg');

m = 0;
s = 10;
x = -3 * s : 3 * s;
g = (1/(s * sqrt(2 * pi))) * exp(-0.5 * ((x - m) / s) .^ 2);
g = g / sum(g(:));
g2 = g' * g;
 
%ims = convn(double(im), g2, "full");
ims = imfilter(im, g2, "same", "circular");
imshow(ims); 


fftR = fft(double(im));
espR = abs(fftR);
phaseR = atan2(imag(fftR), real(fftR));
% imshow(convn(double(im),g,"same"));
