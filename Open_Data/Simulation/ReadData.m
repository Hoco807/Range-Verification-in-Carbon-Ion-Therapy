clear,clc
close all
warning off

fid=dir('*MeV');
n=length(fid);

for i=1:n

    cd([fid(i).name,'/output']);

    dos('hadd -f Data.root data*.root');
    dos('g++ convert.c `root-config --cflags --libs`');
    dos(' ./a.out Data.root Out.txt');
    clear ans;

    E1=0;
    for j=1:10
        EE1=textread(['MSIC',num2str(j),'-Edep.txt'],'','headerlines',6);
        E1=E1+EE1;
    end
    clear EE1 j ans;
    MU=(E1*10^6*1.6*10^-19)/(2*10^-12*35);

    Data=load('Out.txt');
    a=Data(:,6)>0;
    Data=Data(a,:);
    clear a;

    [a,b]=histcounts(Data(:,6),'BinWidth',10);
    a=a./MU;

    HC{i,1}=[b(2:end)',a'];
    HC{i,1}(:,3)=smooth(b(2:end),a);

    plot(HC{i,1}(1:20,3));
    hold on;

    clear a b Data E1 MU;
    cd ../../;
end
clear i n fid;