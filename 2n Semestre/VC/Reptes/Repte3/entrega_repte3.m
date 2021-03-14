im = imread("./image.jpg");

figure(1);
imshow(im);
title('Imatge original', 'fontsize', 15);

% MODEL FOURIER RGB

R = im(:,:,1);
G = im(:,:,2);
B = im(:,:,3);

[M N] = size(im(:,:,1));
r = 30;
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

RGBResult = uint8(cat(3, resultR, resultG, resultB));

figure(2);
subplot(1,3,1);
imshow(abs(AR1),[-12 300000]);
title('fft del canal vermell','fontsize',15);
subplot(1,3,2);
imshow(abs(AG1),[-12 300000]);
title('fft del canal verd','fontsize',15);
subplot(1,3,3);
imshow(abs(AB1),[-12 300000]);
title('fft del canal blau','fontsize',15);

figure(3);
subplot(1,3,1);
imshow(abs(resultR),[12 290]);
title('Resultat canal Vermell', 'fontsize', 15);
subplot(1,3,2);
imshow(abs(resultG),[12 290]);
title('Resultat canal Verd', 'fontsize', 15);
subplot(1,3,3);
imshow(abs(resultB),[12 290]);
title('Resultat canal Blau', 'fontsize', 15);

figure(4);
imshow(RGBResult,[]);
title('Resultat RGB', 'fontsize', 15);