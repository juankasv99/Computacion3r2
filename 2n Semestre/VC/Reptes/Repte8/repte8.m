close all; 
clear all; 
clc

im = im2double(imread("https://geoserveis.icgc.cat/icc_mapesbase/wms/service?REQUEST=GetMap&VERSION=1.1.0&SERVICE=WMS&SRS=EPSG:25831&BBOX=333773,4698340,334409,4699126&WIDTH=1024&HEIGHT=1024&LAYERS=orto25c&STYLES=&FORMAT=image/jpeg&BGCOLOR=0xFFFFFF&TRANSPARENT=TRUE&EXCEPTION=INIMAGE"));

% % %selecció de punts
% x1 = []; x2 = [];
% y1 = []; y2 = [];
% 
nPunts = 100;
% 
% figure(1);
% imshow(im);
% impixelinfo;
% 
% hold on;
% zoom on;
%  
% for i = 1:nPunts
%     zoom on;
%     pause();
%     zoom off;
%     [x1(i),y1(i)]=ginput(1);
%     zoom out;
%     plot(x1(i), y1(i), "go", "MarkerSize", 8);
%     disp("X:"+x1(i)+" Y:"+y1(i));
% end
% 
% save("pt1", "x1", "y1");
% 
% h = msgbox(sprintf("Ara es marquen els NO arbres"));
% 
% for i = 1:nPunts
%     zoom on;
%     pause();
%     zoom off;
%     [x2(i),y2(i)]=ginput(1);
%     zoom out;
%     plot(x2(i), y2(i), "ro", "MarkerSize", 8);
%     disp("X:"+x2(i)+" Y:"+y2(i));
% end
% 
% save("pt2", "x2", "y2");
% 
% hold off;

% carregar punts

load("pt1");
load("pt2");

figure(1);
imshow(im);

hold on;
plot(x1(1),y1(1),"go","MarkerSize",8);
plot(x2(1),y2(1),"ro","MarkerSize",8);
hold off;


%randomitzar indexs
idx1 = randperm(length(x1),length(x1));
idx2 = randperm(length(x2),length(x2));

x1(:) = x1(idx1);
y1(:) = y1(idx1);
x2(:) = x2(idx2);
y2(:) = y2(idx2);

figure(2);
imshow(im);

hold on;
plot(x1,y1,"go","MarkerSize",8);
plot(x2,y2,"ro","MarkerSize",8);
hold off;

%train/test split
%(x,y,,label);
%0 = bosc, 1 = no bosc

train = zeros(100, 76);
test = zeros(100, 76);
data1 = zeros(100,75);
data2 = zeros(100,75);

%im(x1(1)-2:x1(1)+2,y1(1)-2:y1(1)+2,:)

x1 = round(x1);
x2 = round(x2);
y1 = round(y1);
y2 = round(y2);

tic
for i = 1:nPunts
    tmp1 = im( y1(i)-2:y1(i)+2, x1(i)-2:x1(i)+2, : );
    tmp2 = im( y2(i)-2:y2(i)+2, x2(i)-2:x2(i)+2, : );
    
    tmp1 = reshape(tmp1, [1 75]);
    tmp2 = reshape(tmp2, [1 75]);
    
    data1(i,:) = tmp1; 
    data2(i,:) = tmp2;
end
toc

train(1:50,1:75) = data1(1:50,:);
train(1:50,76) = 0;
train(51:100,1:75) = data2(51:100,:);
train(51:100,76) = 1;

test(1:50,1:75) = data1(51:100,:);
test(1:50,76) = 0;
test(51:100,1:75) = data2(1:50,:);
test(51:100,76) = 1;

%IDA

MdlLinear = fitcdiscr(train(:,1:75),train(:,76));
prediction1 = predict(MdlLinear,test(:,1:75));
cm(1) = confusionchart(test(:,76),prediction1);

%NaiveBayes

Mdl = fitcnb(train(:,1:75),train(:,76));
prediction2 = predict(Mdl,test(:,1:75));
cm(2) = confusionchart(test(:,76),prediction2);

%SVM

Mdl = fitcsvm(train(:,1:75),train(:,76));%,'OptimizeHyperparameters','auto');
prediction3 = predict(Mdl,test(:,1:75));
cm(3) = confusionchart(test(:,76),prediction3);

midaImg = size(im, 1:2);
finalData = zeros((midaImg(1)-4)*(midaImg(2)-4),76);

for i = 3:midaImg(1)-2
    for j = 3:midaImg(2)-2
        %tmp = im( y1(i)-2:y1(i)+2, x1(i)-2:x1(i)+2, : );
        tmp = im(j-2:j+2, i-2:i+2, :);
        tmp = reshape(tmp, [1 75]);
        finalData((midaImg(1)-4)*(i-3)+j-2,1:75) = tmp;
    end
    
end

predictionFinal = predict(Mdl,finalData(:,1:75));
finalData(:,76) = predictionFinal(:);

imageBW = reshape(finalData(:,76),midaImg(1)-4,midaImg(2)-4);
cropIm = im(3:midaImg(1)-2,3:midaImg(2)-2,:);

imBosc = cropIm .* imageBW;
figure(3)
imshow(imBosc,[]);
imageBW1 = imageBW;

for i = 1:size(imageBW1,1)
    for j = 1:size(imageBW1,2)
        if imageBW1(i,j)==1
            imageBW1(i,j)=0;
        else
            imageBW1(i,j)=1;
        end
    end
end

imNoBosc = cropIm .* imageBW1;
figure(4)
imshow(imNoBosc,[]);




