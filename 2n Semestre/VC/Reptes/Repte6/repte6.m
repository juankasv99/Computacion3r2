close all; 
clear all; 
clc



im = zeros(3000,4000,3,1, 'uint8');
im(:,:,:,1) = imread("input/im1.jpg");
im(:,:,:,2) = imread("input/im2.jpg");
pts = 100;
desc = zeros(68, 27, 2);

%DETECCIO + DESCRIPTORS

for i = 1:2
    I = im(:,:,:,i);
    figure;
    imshow(I);
    
    sigma = 2; thr = 50; r = 6; disp = 1;
    dx = [-1 0 1; -1 0 1; -1 0 1];
    dy = dx';
    
    Ix = conv2(I(1:3000,1:4000), dx, 'same');
    Iy = conv2(I(1:3000,1:4000), dy, 'same');
    g = fspecial('gaussian',5, sigma);
    
    Ix2 = conv2(Ix.^2, g, 'same');
    Iy2 = conv2(Iy.^2, g, 'same');
    Ixy = conv2(Ix.*Iy, g,'same');
    k = 0.04;
    R11 = (Ix2.*Iy2 - Ixy.^2) - k*(Ix2 + Iy2).^2;
    R=R11;
    ma=max(max(R));
    sz = 2*r+1;
    MX = ordfilt2(R,sz^2,ones(sz));
    R11 = (R==MX)&(R>thr);
    count=sum(sum(R11(5:size(R11,1)-5,5:size(R11,2)-5)));
    
    
    while((count>pts)||(count<pts))
        if count>pts
            thr=thr*1.5;
        elseif count<pts
            thr=thr*0.8;
        end
        
        R11 = (R==MX)&(R>thr);
        count=sum(sum(R11(5:size(R11,1)-5,5:size(R11,2)-5)));
    end
    
    R=R*0;
    R(5:size(R11,1)-5,5:size(R11,2)-5)=R11(5:size(R11,1)-5,5:size(R11,2)-5);
    [r,c] = find(R);
    PIP=[r,c];
    
    sizePI = size(PIP,1,2);
    I2 = I;
    for r=1: sizePI
        I2(PIP(r,1)-8:PIP(r,1)+8,PIP(r,2)-9:PIP(r,2)-8)=255;
        I2(PIP(r,1)-8:PIP(r,1)+8,PIP(r,2)-9:PIP(r,2)-8,2:3)=0;
        I2(PIP(r,1)-8:PIP(r,1)+8,PIP(r,2)+8:PIP(r,2)+9)=255;
        I2(PIP(r,1)-8:PIP(r,1)+8,PIP(r,2)+8:PIP(r,2)+9,2:3)=0;
        I2(PIP(r,1)-9:PIP(r,1)-8,PIP(r,2)-8:PIP(r,2)+8)=255;
        I2(PIP(r,1)-9:PIP(r,1)-8,PIP(r,2)-8:PIP(r,2)+8,2:3)=0;
        I2(PIP(r,1)+8:PIP(r,1)+9,PIP(r,2)-8:PIP(r,2)+8)=255;
        I2(PIP(r,1)+8:PIP(r,1)+9,PIP(r,2)-8:PIP(r,2)+8,2:3)=0;
    end
    figure;
    imshow(uint8(I2));
    
    
    for j=1:sizePI
        container = I(PIP(j,1)-1:PIP(j,1)+1,PIP(j,2)-1:PIP(j,2)+1,:);
        vectorContainer = reshape(container,1,[]);
        desc(j,:,i) = vectorContainer;
    end
    
    listPIP(i,:,:) = PIP;
    
    
end

% MATCHING
match = zeros(1,100);
for j=1:100
    d1=desc(j,:,1);
    [~,match(j)]=min(sum(abs(desc(:,:,2)-d1)));
end

figure,
imshow([im(:,:,:,1),im(:,:,:,2)]);
hold on
despl = size(im(:,:,:,1),2);
plot( listPIP(1,:,2),listPIP(1,:,1),"red","MarkerSize",5 );
plot( listPIP(2,:,2)+despl,listPIP(2,:,1),"yellow","MarkerSize",5 );
for j=1:100
    line([listPIP(1,j,2), listPIP(2,match(j),2)+despl], [listPIP(1,j,1),listPIP(2,match(j),1)]);
end
hold off

