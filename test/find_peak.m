function [peak yy] = find_peak(y,flag)
% y: ���������
% yy: �˲��������
% peak����ֵ�����ڵ����
% flag: 1-->��ʾ�󲨷�;2-->��ʾ�󲨹�

% step 0: Ԥ����
if (flag==2)
    y = y .* -1;
end
% step 1: �˲�
% yy = median_filter(y,5);
yy = mean_filter(y,6);

% step 2: �󼫴�ֵ��
[~, tmp_peak] = findpeaks(yy); 

% step 3: ��ֵ���Է�ֵ�����
max_y = max(yy);
e = (max(yy)-min(yy))*0.4; %�趨��ֵ
peak=[];
for i=1:size(tmp_peak,2)
    if(max_y - yy(tmp_peak(i)) <= e) %�Ƿ�������ֵ
        found = 1;
    else 
        continue;
    end
    for j = tmp_peak(i)-40:tmp_peak(i)+40 %���������Ƿ������ֵ�������������뾶Ϊ40
       if(j<1 || j>size(yy,2))
           continue;
       end
       if(yy(tmp_peak(i))<yy(j))
           found = 0;
       end
    end
    if(found==1)   
        peak = [peak tmp_peak(i)];%��¼�ò�������
    end
end

if(flag==2)
    yy = -1.*yy;
end
