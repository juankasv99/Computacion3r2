video_llum = VideoReader("./DSC_0524.MOV");
video_fosc = VideoReader("./DSC_0525.MOV");

frame = rgb2gray(readFrame(video_llum));
sz = size(frame);
N = 200;
acum = zeros(sz(1)/2,sz(2)/2,N);
acum(:,:,1) = frame(1:2:end, 1:2:end, 1);
for i=2:N
    frame = rgb2gray(readFrame(video_llum));
    acum(:,:,i) = frame(1:2:end, 1:2:end, 1);
end
fsr = sum(acum(:,:,1:100),3)/(N/2); %vs

fhdr = sum(acum(:,:,101:200),3);
fr = acum(:,:,101);

ruido = fr-fsr;
ruidohdr = fhdr-fsr;


figure, hold on
plot(acum(120,:,1)), plot(acum(120,:,50)), plot(acum(120,:,100)), plot(fsr(120,:,1), "LineWidth", 2.0)
legend({"frame_{1}","frame_{50}", "frame_{100}", "mean"})

figure, hold on
plot(acum(120,:,1)), plot(acum(120,:,50)), plot(acum(120,:,100)), plot(fsr(120,:,1), "LineWidth", 2.0)
legend({"frame_{1}","frame_{50}", "frame_{100}", "mean"})
axis([250, 730, 190, 230])
