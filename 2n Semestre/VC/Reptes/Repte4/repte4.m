im = imread("./image.jpg");

sz = size(im);

pixels_totals = size(im(:));

media = mean(im(:));

variacion = std2(double(im));

% test = double(im) - variacion;
% test = uint8(test);