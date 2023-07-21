---����������,�Զ��޸İ༶���еİ༶����,
---һ�ν����޸�һ��ѧ����¼��

/*���봥������inserted��ṹ��Student��ṹ��ͬ*/
create trigger classIns
on Student
for insert
as   
	--�������@classNo,���ڽ����������ѧ���������
	declare @classNo char(8)
	--��������¼����1������ع�
	if(select count(*) from inserted)>1
		rollback
	else
		begin
		--�ҳ�Ҫ����ѧ���İ�ŷ������@classNo
			select @classNo=ClassNo from inserted 
			--���°༶���ж�Ӧ���Ϊ@classNo�İ༶����
			update Class set StudentNum=StudentNum+1
			where ClassId=@classNo
		end

/*
/*ɾ��������,deleted��ṹ��Student��ṹ��ͬ*/
create trigger classDel
on Student
for delete
as
	--�������@classNo�����ڽ�����ɾ��ѧ�������İ��
	declare @classNo char(8)
	--���ɾ����¼����1������ع�
	if(select count(*) from inserted)>1
		rollback
	else
		begin
		--�ҳ�Ҫɾ��ѧ���İ�ŷ������@classNo
			select @classNo=ClassNo from deleted 
			--���°༶���ж�Ӧ���Ϊ@classNo�İ༶����
			update Class set StudentNum=StudentNum-1
			where ClassId=@classNo
		end
*/

/*
--���´�������deleted��inserted��ṹ��Student��ṹ��ͬ*/
create trigger classUpt
on Student
for update
as
	--�������@newclassNo�����ڽ���������ѧ���������°��
	--�������@oldclassNo�����ڽ���������ѧ�������ľɰ��
	declare @newclassNo char(8)
	declare @oldclassNo char(8)
	--������¼�¼����1������ع�
	if(select count(*) from inserted)>1
		rollback
	else
		begin
		--�ҳ�Ҫ����ѧ�����°�ŷ������@newclassNo
		--�ҳ�Ҫ����ѧ���ľɰ�ŷ������@oldclassNo
			select @newclassNo=ClassNo from inserted 
			select @oldclassNo=ClassNo from deleted
			--���¾ɰ༶���°༶�еİ༶����
			update Class set StudentNum=StudentNum-1
			where ClassId=@oldclassNo
			update Class set StudentNum=StudentNum+1
			where ClassId=@newclassNo
		end
*/
