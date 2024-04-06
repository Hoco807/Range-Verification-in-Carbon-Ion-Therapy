clear,clc
close all
warning off

Energy=[160.86;170.03;181.75;190.19;201.03;211.44;219.00;231.19];

MU=[2885.27;2985.06;3109.63;3197.41;3307.98;3412.01;3486.32;3604.08];

n=length(Energy);

for i=n:n

    Beam_Energy=['/control/alias Energy',' ',num2str(Energy(i)*12),' MeV','\r\n'];
    Beam_Number=['/control/alias Particle_Numble',' ',num2str(100*MU(i)),' MeV','\r\n'];

    cd ../Simulation/;

    % 模拟文件参数写入
    fid=fopen('./mac/configuration.mac','w+');
    fprintf(fid,Beam_Energy);
    fprintf(fid,Beam_Number);
    fclose(fid);
    clear fid ans;

    % 开始模拟
    dos('Gate main.mac');

    cd ./output/;
    dos('g++ convert.c  `root-config --cflags --libs`');
    dos('./a.out gemactor.root Out.txt');
    T=load('Out.txt');
    dos('rm gemactor.root Out.txt stats_adder.txt');

    cd ../../Control/;

    Data{i,1}=DataDeal(T);

    file=[num2str(Energy(i)),'.mat'];
    cd ./Data;
    save(file,'T');
    cd ..

    clear T ans Beam_* file;
end
