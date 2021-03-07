video_llum = VideoReader("./DSC_0524.MOV");
video_fosc = VideoReader("./DSC_0525.MOV");



frame_llum = rgb2gray(readFrame(video_llum));
frame_fosc = rgb2gray(readFrame(video_fosc));
sz_llum = size(frame_llum);
sz_fosc = size(frame_fosc);
N = 200;
acum_llum = zeros(sz_llum(1)/2,sz_llum(2)/2,N);
acum_llum(:,:,1) = frame_llum(1:2:end, 1:2:end, 1);
acum_fosc = zeros(sz_fosc(1)/2,sz_fosc(2)/2,N);
acum_fosc(:,:,1) = frame_fosc(1:2:end, 1:2:end, 1);
for i=2:N
    frame_llum = rgb2gray(readFrame(video_llum));
    acum_llum(:,:,i) = frame_llum(1:2:end, 1:2:end, 1);
    frame_fosc = rgb2gray(readFrame(video_fosc));
    acum_fosc(:,:,i) = frame_fosc(1:2:end, 1:2:end, 1);
end
fsr_llum = sum(acum_llum(:,:,1:100),3)/(N/2);
fsr_fosc = sum(acum_fosc(:,:,1:100),3)/(N/2);

fhdr_llum = sum(acum_llum(:,:,101:200),3);
fr_llum = acum_llum(:,:,101);

fhdr_fosc = sum(acum_fosc(:,:,101:200),3);
fr_fosc = acum_fosc(:,:,101);

ruido_llum = fr_llum-fsr_llum;
ruidohdr_llum = fhdr_llum-(fsr_llum*100);

ruido_fosc = fr_fosc-fsr_fosc;
ruidohdr_fosc = fhdr_fosc-(fsr_fosc*100);


figure, hold on
plot(acum_llum(120,:,1)), plot(acum_llum(120,:,50)), plot(acum_llum(120,:,100)), plot(fsr_llum(120,:,1), "LineWidth", 2.0)
legend({"frame_{1}","frame_{50}", "frame_{100}", "mean"})

figure, hold on
plot(acum_llum(120,:,1)), plot(acum_llum(120,:,50)), plot(acum_llum(120,:,100)), plot(fsr_llum(120,:,1), "LineWidth", 2.0)
legend({"frame_{1}","frame_{50}", "frame_{100}", "mean"})
axis([250, 730, 190, 230])

figure, hold on
plot(acum_fosc(120,:,1)), plot(acum_fosc(120,:,50)), plot(acum_fosc(120,:,100)), plot(fsr_fosc(120,:,1), "LineWidth", 2.0)
legend({"frame_{1}","frame_{50}", "frame_{100}", "mean"})

figure, hold on
plot(acum_fosc(120,:,1)), plot(acum_fosc(120,:,50)), plot(acum_fosc(120,:,100)), plot(fsr_fosc(120,:,1), "LineWidth", 2.0)
legend({"frame_{1}","frame_{50}", "frame_{100}", "mean"})
axis([250, 750, 0, 55])

soroll_llum = 255/(2*std2(ruido_llum));
soroll_fosc = 255/(2*std2(ruido_fosc));
soroll_llum_rang = 25500 / (2*std2(fhdr_llum-(fsr_llum*100)));
soroll_fosc_rang = 25500 / (2*std2(fhdr_fosc-(fsr_fosc*100)));