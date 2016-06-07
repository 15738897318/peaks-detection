clear;clc;close all;
y = importdata('data1.txt');  % ��������
[peak, ~] = find_peak(y,1);   % ����
[trough, yy] = find_peak(y,2);  % ����
%������
disp('���������')
peak
disp('���ȵ�����')
trough
%ͼ�λ���ʾ
figure(1);
h = plot(1:size(yy,2),yy);
xlabel('���');
ylabel('��ֵ');
% title('�˲����ͼ��')
% set(h,'Color',[1 0 1])
hold on;
for i=1:size(peak,2)  % ���ݽ����ǲ���λ��
    tmpx = peak(i);
    tmpy = yy(tmpx);
    h = plot(tmpx,tmpy,'o');
    set(h,'MarkerFaceColor',[1 0 0])
%     text(tmpx+2,tmpy,['(' num2str(tmpx) ',' num2str(tmpy) ')'],'FontSize',3);
     text(tmpx+5,tmpy, num2str(tmpx),'FontSize',6);
end
for i=1:size(trough,2)  % ���ݽ����ǲ��ȵ�λ��
    tmpx = trough(i);
    tmpy = yy(tmpx);
    h = plot(tmpx,tmpy,'o');
    set(h,'MarkerFaceColor',[0 1 0])
%     text(tmpx+2,tmpy,['(' num2str(tmpx) ',' num2str(tmpy) ')'],'FontSize',3);
    text(tmpx+5,tmpy, num2str(tmpx),'FontSize',6);
end