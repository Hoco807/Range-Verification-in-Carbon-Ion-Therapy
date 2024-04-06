function Data = DataDeal(T)
t=1;
gap=2;
for i=1:gap:300
    a=find(T(:,4)>i & T(:,4)<=i+gap);
    Data(t,:)=[i,size(a,1)];
    t=t+1;
end

end

