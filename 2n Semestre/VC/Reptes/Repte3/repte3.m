im = imread("./image.jpg");

figure(1);
imshow(im);
title('Imatge original', 'fontsize', 15);

% MODEL CONVN + FILT EN COLOR

m = 0;
s = 8;
x = -3 * s : 3 * s;
g = (1/(s * sqrt(2 * pi))) * exp(-0.5 * ((x - m) / s) .^ 2);
g = g / sum(g(:));
g2 = g' * g;

ims = convn(double(im), g2, "full");
ims = imfilter(im, g2, "same", "circular");

figure(2);
imshow(ims);
title('Imatge filtrada amb color','fontsize',14);

% MODEL FOURIER R+G+B PERO NO JUNTA

R = im(:,:,1);
G = im(:,:,2);
B = im(:,:,3);

[M N] = size(im(:,:,1));
r = 10;
x = 0 : N-1;
y = 0 : M-1;
[x y] = meshgrid(x,y);
cx = 0.5*N;
cy = 0.5*M;
lowFilt = exp(-((x-cx).^2+(y-cy).^2)./(2*r).^2);

AR = fft2(double(R));
AG = fft2(double(G));
AB = fft2(double(B));
AR1 = fftshift(AR);
AG1 = fftshift(AG);
AB1 = fftshift(AB);

lowPassR = AR1.*lowFilt;
lowPassG = AG1.*lowFilt;
lowPassB = AB1.*lowFilt;

lowPassR1 = ifftshift(lowPassR);
lowPassG1 = ifftshift(lowPassG);
lowPassB1 = ifftshift(lowPassB);

resultR = ifft2(lowPassR1);
resultG = ifft2(lowPassG1);
resultB = ifft2(lowPassB1);

RGBResult = cat(3, resultR, resultG, resultB);

figure(3);
subplot(1,3,1);
imshow(abs(AR1),[-12 300000]);
title('fft del canal vermell','fontsize',15);
subplot(1,3,2);
imshow(abs(AG1),[-12 300000]);
title('fft del canal verd','fontsize',15);
subplot(1,3,3);
imshow(abs(AB1),[-12 300000]);
title('fft del canal blau','fontsize',15);

figure(4);
subplot(1,3,1);
imshow(abs(resultR),[12 290]);
title('Resultat canal Vermell', 'fontsize', 15);
subplot(1,3,2);
imshow(abs(resultG),[12 290]);
title('Resultat canal Verd', 'fontsize', 15);
subplot(1,3,3);
imshow(abs(resultB),[12 290]);
title('Resultat canal Blau', 'fontsize', 15);


% MODEL FOURIER GREYSCALE

imGray = rgb2gray(im);

firstIter = fft2(double(imGray));
firstIter1 = fftshift(firstIter);

[M N]=size(firstIter);
r=20;
x=0:N-1;
y=0:M-1;
[x y]=meshgrid(x,y);
cx=0.5*N;
cy=0.5*M;
lowFilter=exp(-((x-cx).^2+(y-cy).^2)./(2*r).^2);

filtered=firstIter1.*lowFilter;
filtered1=ifftshift(filtered);
filtResult=ifft2(filtered1);

figure(5);
imshow(abs(filtResult),[12 290]);
title('Resultat Fourier blanc i negre', 'fontsize', 15);