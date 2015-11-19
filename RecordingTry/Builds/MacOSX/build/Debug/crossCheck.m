clear all;
clc;
close all;

fileID = fopen('aucorr.txt');
D = textscan(fileID,'%f','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
aucorr = D{1};
title('aucorr');


fileID = fopen('x1.txt');
D = textscan(fileID,'%f','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
x1 = D{1};
title('x1');

fileID = fopen('x2.txt');
D = textscan(fileID,'%f','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
x2 = D{1};
title('x2');

fileID = fopen('inputChannel.txt');
D = textscan(fileID,'%f','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
inputData = D{1};
title('inputChannel');

fileID = fopen('writtenAudio_SC.txt');
D = textscan(fileID,'%f','Delimiter','\n','CollectOutput', true);
figure
plot(D{1})
writtenAudio = D{1};
title('writtenAudio');

[ACFAudio, fs] = audioread ('ACFAudio.wav');
ACFAudio = ACFAudio(1:512*5);

% disp ( 'Sum of differce for written and read Audio is ' );
% disp ( sum ( writtenAudio - ACFAudio ) );

matAucorr = xcorr(ACFAudio, ACFAudio );
figure 
plot(matAucorr); title( 'matAucorr' );

ACFLen = 2*length(ACFAudio) - 1;
myAucorr = zeros( 1, ACFLen );
x1       = myAucorr;
x2       = myAucorr;

x1( 1:length(ACFAudio)   ) = ACFAudio;
x2( length(ACFAudio):end ) = ACFAudio;

for i = 1:length(x2)
    for k = 1:length(x2)
        myAucorr(i) = myAucorr(i) + x1(k)*x2(k);
    end
    x1 = circshift( x1, [1 1] );
end

sum ( myAucorr' - matAucorr )
% for (int ii=0; ii<x2.size(); ii++)
%         {
%             for (int kk=0; kk<x2.size(); kk++) {
%                 aucorr[ii]+=x1[kk]*x2[kk];
%             }
%             std::rotate(x2.begin(),x2.end()-1,x2.end());
%         }

y = [1:10,9:-1:1,2:10];
y = [10:-1:1,2:10,9:-1:1];
a = diff(y);
for i = 1: length(a) - 1
    if ( (a(i) <= 0 && a(i+1) <= 0 ) || ( a(i) >= 0 && a(i+1) >= 0 ) || ( a(i) <= 0 && a(i+1) >= 0 ) )
      continue;
    else
       break;
    end
end

if ( i~= length(a) - 1)
    disp (i+1);
end

