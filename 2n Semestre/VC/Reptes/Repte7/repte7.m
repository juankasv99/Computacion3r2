close all; 
clear all; 
clc

im = im2double(imread("img.jpeg"));


colorSpace = "hsv"; %rgb o hsv

if colorSpace == "hsv"
    im = rgb2hsv(im);
end

imgVector = reshape(im,size(im,1)*size(im,2),3);

nClusters = 16;
nIterations = 50;
centroids = imgVector( ceil(rand(nClusters,1)*size(imgVector,1)) ,:);

distances = zeros(size(imgVector,1),nClusters+2);
prevDistances = distances;
%k+1=centroide assignat a cada punt
%k+2=distancia al seu centroide

% centres aleatoris
tmp = ceil(numel(im(:,:,1))*rand(1,nClusters));

% KMEANS
tic

for n = 1:nIterations
    
    for i = 1:size(imgVector,1)
        
        for j = 1:nClusters
            distances(i,j) = norm( imgVector(i,:) -  centroids(j,:));    
        end
        [distance, center] = min(distances(i,1:nClusters));
        distances(i,nClusters+1) = center;
        distances(i,nClusters+2) = distance;      
    end
    
    if prevDistances(:,nClusters+1)==distances(:,nClusters+1)
        disp("Configuracions iguals, sortint de l'execució");disp(n);
        break
    end
    
    for i = 1:nClusters
        tmp = (distances(:,nClusters+1)==i);
        centroids(i,:) = mean(imgVector(tmp,:));
        
        if sum(isnan(centroids(:))) ~= 0
            disp("CENTROIDES AMB NAN");
        end
    end
    
    prevDistances = distances;
end
toc

X = zeros(size(imgVector));
for i = 1:nClusters
    idx = find(distances(:,nClusters+1)==i);
    X(idx,:) = repmat(centroids(i,:),size(idx,1),1);
end

T = reshape(X,size(im,1),size(im,2),3);
if colorSpace == "hsv"
    im = hsv2rgb(im);
    T = hsv2rgb(T);
end

figure()
subplot(121);imshow(im);title("original")
subplot(122);imshow(T);title("kmeans amb espai de color " + colorSpace);
disp("nombre de centroides: ");disp(nClusters);


