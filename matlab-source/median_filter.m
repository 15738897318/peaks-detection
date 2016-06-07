function yy = median_filter(y,k)
% yy: �˲��������
% ��ֵ�˲�
% y����������
% k: ����ֵ�������г���
n = max(size(y));
for i=1:k
    tmp(:,i) = y(i:n-k+i);
end
yy = [];
for i=1:size(tmp,1)
    tmp(i,:) = sort(tmp(i,:));
    if mod(k,2) == 1
        avg = tmp(i,floor(k/2)+1);
    else
        avg = (tmp(i,k/2)+tmp(i,k/2+1))/2;
    end
    yy = [yy avg];
end