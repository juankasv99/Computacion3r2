im1 = imread("./image1.jpg");
im2 = imread("./image2.jpg");

figure(1);
imshow(im1);


%x1=[]; y1=[];
%x2=[]; y2=[];

% for j=1:4
%     zoom on;
%     pause();
%     zoom off;
%     [x1(j),y1(j)]=ginput(1);
%     zoom out;
% end
% 
% figure(2)
% imshow(im2);
% 
% for j=1:4
%     zoom on;
%     pause();
%     zoom off;
%     [x2(j),y2(j)]=ginput(1);
%     zoom out;
% end
% 
% save("pt1", "x1", "y1");
% save("pt2", "x2", "y2");

load("pt1");
load("pt2");

%DLT
M = [];
for i=1:4
    M = [M ;
        x1(i) y1(1) 1 0 0 0 -x2(i)*x1(i) -x2(i)*y1(i) -x2(i);
        0 0 0 x1(i) y1(i) 1 -y2(i)*x1(i) -y2(i)*y1(i) -y2(i)];
end
[u,s,v] = svd(M);
H=reshape(v(:,end),3,3)';
H=H/H(3,3);
H = [H(:,2) H(:,1) H(:,3)];

% visualizacion
% b=1;
% while(b ~= 3)
%     figure(1)
%     [x y b] = ginput(1);
%     p = H*[x y 1]';
%     p = p/p(3);
%     figure(2)
%     hold on
%     plot(p(1), p(2), "rx", "MarkerSize", 20, "LineWidth", 3);
%     hold off
% end

tform = projective2d(inv(H'));
imgCorrected = imwarp(im2, tform);
imshow(imgCorrected)

% RO = imref2d(size(im1));
% B = imwarp(im1, tform, "OutputView", RO);
% imshow(B)