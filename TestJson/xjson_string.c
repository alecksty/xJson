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
//
//=======================================================================
#include "xjson.h"

#ifdef SUPPORT_XJSON

//=======================================================================
//	����: 	json_string_create
//	����:
//	����:
//	˵��:	
//=======================================================================
jobject * json_string_create( jobject * j,jcstring name,jcstring value)
{
	if(!j)
	{
		j = json_new();
		json_init(j);
	}
	
	j->type 		= JSON_TYPE_STRING;
	j->name 		= name;

#ifdef SUPPORT_SAVE_BUFFER	
	strcpy_s(j->aName,sizeof(j->aName),name);
	j->name = j->aName;
#endif //SUPPORT_SAVE_BUFFER

	j->value.text	= value;

#ifdef SUPPORT_SAVE_BUFFER	
	strcpy_s(j->aValue,sizeof(j->aValue),value);
	j->value.text	= j->aValue;
#endif //SUPPORT_SAVE_BUFFER

	return j;
}

//=======================================================================
//	����: 	json_string_parser
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_string_parser(S_WordItem *pw, jobject * j)
{
	if(!pw)
		return 0;

	if(!j)
		return 0;

	if(pw->type == WT_STRING){
		//	���浽����
		strcpy_s(j->aValue,sizeof(j->aValue),pw->buf);

		j->type 		= JSON_TYPE_STRING;
		j->value.text 	= j->aValue;		
		return 1;
	}
	return 0;
}

//=======================================================================
//	����: 	json_string_value
//	����:
//	����:
//	˵��:	��ȡֵ
//=======================================================================
jcstring json_string_value(const jobject * j)
{
	if(!j)
		return NULL;

	if(j->type != JSON_TYPE_STRING){
		return NULL;
	}

	return j->value.text;
}

//=======================================================================
//	����: 	json_string_tostring
//	����:
//	����:
//	˵��:	��������
//=======================================================================
void json_string_tostring(const jobject * j,char * pd,int l)
{
	if(!j)
		return;

	if(j->type == JSON_TYPE_STRING)
	{
		json_cat(pd,l,XJSON_STRING_SIGN);
		json_cat(pd,l,j->value.text);
		json_cat(pd,l,XJSON_STRING_SIGN);
	}
}

//=======================================================================
//	����: 	json_string_dump
//	����:
//	����:
//	˵��:	��������
//=======================================================================
void json_string_dump(const jobject * j)
{
	if(!j)
		return;

	if(j->type == JSON_TYPE_STRING)
	{
		PRINTF(XJSON_STRING_SIGN "%s" XJSON_STRING_SIGN,j->value.text);
	}
}

#endif


