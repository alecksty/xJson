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
#include "xjson.h"

#ifdef SUPPORT_XJSON

//=======================================================================
//	����: 	json_bool_create
//	����:
//	����:
//	˵��:	
//=======================================================================
jobject * json_bool_create(jobject * j,jcstring name,jbool value)
{
	if(!j)
	{
		j = json_new();
		json_init(j);
	}
	j->type 		= JSON_TYPE_BOOL;
	j->name 		= name;

#ifdef SUPPORT_SAVE_BUFFER	
	strcpy_s(j->aName,sizeof(j->aName),name);
	j->name = j->aName;
#endif //SUPPORT_SAVE_BUFFER

	j->value.boo 	= value;
	return j;
}

//=======================================================================
//	����: 	json_bool_parser
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_bool_parser(S_WordItem *pw, jobject * j)
{
	if(pw->type == WT_IDENTIFY)
	{
		if(!strcmp(pw->buf,"true"))
		{
			j->type 		= JSON_TYPE_BOOL;
			j->value.boo 	= TRUE;
			return 1;
		}
		else if(!strcmp(pw->buf,"false"))
		{
			j->type 		= JSON_TYPE_BOOL;
			j->value.boo 	= FALSE;
			return 1;
		}
		else
		{
			PRINTF("#ERROR:unknow identify: %s\r\n",pw->buf);
		}
	}
	return 0;
}

//=======================================================================
//	����: 	json_bool_value
//	����:
//	����:
//	˵��:
//=======================================================================
jbool json_bool_value(const jobject * j)
{
	if(!j)
		return FALSE;
	if(j->type != JSON_TYPE_BOOL)
	{
		return FALSE;	
	}
	return j->value.boo;
}

//=======================================================================
//	����: 	json_bool_tostring
//	����:
//	����:
//	˵��:	��������
//=======================================================================
void json_bool_tostring(const jobject * j,char *pd,int l)
{
	if(!j)
		return;
	
	if(j->type == JSON_TYPE_BOOL)
	{
		if(j->value.boo)
		{
			json_cat(pd,l,"true");
		}
		else
		{
			json_cat(pd,l,"false");
		}		
	}
}

//=======================================================================
//	����: 	json_bool_dump
//	����:
//	����:
//	˵��:	��������
//=======================================================================
void json_bool_dump(const jobject * j)
{
	if(!j)
		return;
	
	if(j->type == JSON_TYPE_BOOL)
	{
		if(j->value.boo)
		{
			PRINTF("true");
		}
		else
		{
			PRINTF("false");
		}		
	}
}

#endif

