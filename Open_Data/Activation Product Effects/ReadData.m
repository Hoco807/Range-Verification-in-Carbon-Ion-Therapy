%% read data
clear,clc
close all
fid=fopen('./Data/InBeam_energy_counts','r');
A=fread(fid,'uint16','s');
fclose(fid);
Data=reshape(A,204,[])';
Data(:,1:4)=[];
clear A fid ans

%% find Beam gaps
IC=sum(Data(:,1:100),2);
SC=sum(Data(:,101:200),2);

% the counts of IC and SC within 100ms
[m,~]=size(Data);
t=1;
for i=1:10:m
    IC_100(t,1)=sum(IC(i:i+9,1));
    SC_100(t,1)=sum(SC(i:i+9,1));
    t=t+1;
end
clear m t i