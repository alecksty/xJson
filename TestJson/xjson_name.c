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
//	����: 	json_name_parser
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_name_parser(S_WordItem *pw,jobject * j)
{
	if(pw->type == WT_STRING)
	{
		strcpy_s(j->aName,sizeof(j->aName),pw->buf);
		j->name = j->aName;
		return 1;
	}
	return 0;
}

//=======================================================================
//	����: 	json_value_parser
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_value_parser(S_WordItem * pw,jobject * j)
{
	if(!pw)
		return 0;

	if(!j)
		return 0;

	if(json_bool_parser(pw,j))
	{
		//PRINTF("-->bool\r\n");
	}
	else if(json_number_parser(pw,j))
	{
		//PRINTF("-->number\r\n");
	}
	else if(json_string_parser(pw,j))
	{
		//PRINTF("-->string\r\n");
	}			
	else if(json_object_parser(pw,j))
	{
		//PRINTF("-->object\r\n");
	}
	else if(json_array_parser(pw,j))
	{
		//PRINTF("-->array\r\n");
	}
	else
	{
		//PRINTF("-->unknow\r\n");
		return 0;
	}

	//json_dump(jnew);
	
	return 1;
}

#endif

