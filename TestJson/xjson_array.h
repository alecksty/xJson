//=======================================================================
//
//	ģ��:	JSON ���ݵ����ɺͽ���
//	
//	�汾:	1.00
//
//	����:	2015-12-16
//
//	����:	ʩ̽��
//
//	˵��:	����������
//=======================================================================
#ifndef _JSON_ARRAY_H_
#define _JSON_ARRAY_H_

jobject * 	json_array_create(jobject * j,jcstring name,jobject a[],int l);
int 		json_array_clear(jobject * j);
int 		json_array_add(jobject * j,jobject * sub);
int 		json_array_parser(S_WordItem *pw,jobject * j);
void 		json_array_tostring(const jobject * j,char *pd,int l);
void 		json_array_dump(const jobject * j);

#endif //_JSON_ARRAY_H_

