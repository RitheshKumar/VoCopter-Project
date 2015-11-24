clear all;
clc;
close all;

%% 

fileID = fopen('aucorr.txt');
D = textscan(fileID,'%f','Delimiter','\n','CollectOutput', true);
% figure
% plot(D{1})
% aucorr = D{1};
% title('aucorr');  
 

[ACFAudio, fs] = audioread ('ACFAudio.wav');
ACFAudio = ACFAudio(1:512*5);


matAucorr = xcorr(ACFAudio, ACFAudio );
% figure 
% plot(matAucorr); title( 'matAucorr' );

numSamples = 1024;
myAucorr   = zeros( 1, numSamples);

for i = 1:numSamples
    iter  = numSamples-i+1;

    for k = iter:numSamples
        myAucorr(i) = myAucorr(i) + ACFAudio(k - iter + 1) * ACFAudio( k ); 
    end
end

sum ( myAucorr' - matAucorr(1:numSamples) )

%% 
y = [1:10,9:-1:1,2:10];
% y = [10:-1:1,2:10,9:-1:1]; 
maxVal = 0.0;

for i = 2:length(y)-1
    if ( y(i-1) < y(i) && y(i) >= y(i+1) )
        if (maxVal <= y(i))
            maxVal = y(i);
            myIdx  = i;
        end
    end
end


