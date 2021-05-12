for i = 1:size(points,1)
hold on
plot(points{i,1},points{i,2},"r.","MarkerSize",15);
end
xlim([0 960]);
ylim([0 642 ]);
hold off