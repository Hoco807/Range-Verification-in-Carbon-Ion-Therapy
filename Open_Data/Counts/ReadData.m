clear,clc
close all
warning off

fid=dir('./Data/*MeV');
n=length(fid);

Data=struct();

for i=1:n

    f=fopen(['./Data/',fid(i).name],'r');
    A=fread(f,'uint16','s');
    fclose(f);

    A=reshape(A,204,[])';
    A(:,1:4)=[];

    name=['T',fid(i).name];

    Data.(name).Data=A;
    Data.(name).IC=reshape(A(:,1:100)',[],1);
    Data.(name).SC=reshape(A(:,101:200)',[],1);

    clear f A ans name;
end

clear i n fid