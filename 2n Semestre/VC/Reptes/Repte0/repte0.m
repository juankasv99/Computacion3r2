close all, clear global
v = VideoReader("video.mp4");
suau = [];
pix = [];
frame = readFrame(v);
sz = size(frame);
while hasFrame(v)
    frame = readFrame(v);
    data = reshape(frame, sz(1)*sz(2), 3);
    pix = [pix data(sz(1)*sz(2)/2,1)]; %pixel mig R
    suau = [suau mean(data(:,1))]; %valor mitja R
end
temps = v.Duration;
fprintf("temps: %f s\n", temps)
figure, plot(pix')
hold on
plot(suau)

freq = abs(fft(suau));
freq(1:20)=0; %trec terme DC i primers valors
figure, plot(freq(1:end/2))
[~,pos] = max(freq(1:end/2));
fprintf('pols: %4.2f batecs/minut\n',30*pos/temps);

freq2 = abs(fft(pix));
freq2(1:20)=0; %trec terme DC i primers valors 
figure, plot(freq2(1:end/2))
[~,pos] = max(freq2(1:end/2));
fprintf('pols: %4.2f batecs/minut\n', 30*pos/temps);
    