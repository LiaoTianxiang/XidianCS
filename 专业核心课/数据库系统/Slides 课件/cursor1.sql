use mytest

--����һ���α꣬������ʾѡ����<���ݿ�>�γ̵�ѧ���������ɼ��͸ÿγ̵�ƽ����

--�������������ֵ
declare @sName char(20)
declare @score smallint
declare @sumscore int, @countscore smallint
set @sumscore=0
set @countscore=0
--�����α�
declare mycur cursor for 
select Sname,Grade
from Student a,Course b,SC c
where a.Sno=c.Sno and b.Cno=c.Cno and b.Cname='���ݿ�'
--���α�
open mycur                                              

fetch mycur into @sName, @score        ---��ȡ��ǰ�α��ֵ�ŵ�����@sName @score
while(@@FETCH_STATUS=0)
begin
	select @sName ѧ������, @score �γ̳ɼ�  
	set @sumscore=@sumscore+@score                      ---�����ܷ�
	set @countscore=@countscore+1                       ---����ѡ������
	fetch mycur into @sName, @score                     ---��ȡ��һ���α�ֵ
end
if @countscore>0
	select @sumscore/@countscore  �γ�ƽ����             
else
	select 0.00 �γ�ƽ����
--�ر��α�
close mycur                                             ---�ر��α�
--�ͷ��α�
deallocate mycur                                        ---�ͷ��α�