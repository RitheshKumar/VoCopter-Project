clear all;
clc;
close all;

fileID = fopen('aucorr.txt');
D = textscan(fileID,'%d','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
aucorr = D{1};
title('aucorr');

fileID = fopen('x1.txt');
D = textscan(fileID,'%d','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
x1 = D{1};
title('x1');

fileID = fopen('x2.txt');
D = textscan(fileID,'%d','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
x2 = D{1};
title('x2');

fileID = fopen('inputChannel.txt');
D = textscan(fileID,'%d','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
inputData = D{1};
title('inputChannel');