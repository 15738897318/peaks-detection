function yy = mean_filter(y,k)
% ��ֵ�˲�
% yy: �˲��������
% y����������
% k: ���ֵ�������г���
n = max(size(y));
for i=1:k
    tmp(:,i) = y(i:n-k+i);
end
yy = [];
for i=1:size(tmp,1)
    yy = [yy sum(tmp(i,:))/k];
end