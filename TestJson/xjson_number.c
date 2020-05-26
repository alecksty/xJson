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
//	����: 	json_number_create
//	����:
//	����:
//	˵��:	
//=======================================================================
jobject * json_number_create(jobject * j,jcstring name,int value)
{
	if(!j)
	{
		j = json_new();
		json_init(j);
	}
	
	j->type = JSON_TYPE_NUMBER;
	j->name = name;

#ifdef SUPPORT_SAVE_BUFFER	
	strcpy_s(j->aName,sizeof(j->aName),name);
	j->name = j->aName;
#endif //SUPPORT_SAVE_BUFFER

	j->value.num.type 			= NT_INT;
	j->value.num.value.intValue	= value;
	return j;
}

//=======================================================================
//	����: 	json_number_parser
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_number_parser(S_WordItem * pw,jobject * j)
{
	if(!pw)
		return 0;

	if(!j)
		return 0;

	if(pw->type == WT_NUMBER){
		j->type 						= JSON_TYPE_NUMBER;

		j->value.num.type 				= NT_INT;
		j->value.num.value.intValue 	= atoi(pw->buf);
		
		return 1;
	}
	return 0;
}

//=======================================================================
//	����: 	json_number_value
//	����:
//	����:
//	˵��:	��ȡֵ
//=======================================================================
jnumValue json_number_value(const jobject * j)
{
	jnumValue v;
	v.intValue = 0;
	
	if(!j)
		return v;

	if(j->type != JSON_TYPE_NUMBER){
		return v;
	}

	return j->value.num.value;
}

//=======================================================================
//	����: 	json_number_ivalue
//	����:
//	����:
//	˵��:	��ȡ����
//=======================================================================
int json_number_ivalue(const jobject * j)
{
	if(!j)
		return 0;

	if(j->type != JSON_TYPE_NUMBER){
		return 0;
	}

	return j->value.num.value.intValue;
}

//=======================================================================
//	����: 	json_number_fvalue
//	����:
//	����:
//	˵��:	��ȡ����
//=======================================================================
float json_number_fvalue(const jobject * j)
{
	if(!j)
		return 0;

	if(j->type != JSON_TYPE_NUMBER){
		return 0;
	}

	return j->value.num.value.floatValue;
}

//=======================================================================
//	����: 	json_number_tostring
//	����:
//	����:
//	˵��:	��������
//=======================================================================
void json_number_tostring(const jobject * j,char * pd,int l)
{
	static char buf[16] = {0};
	
	if(!j)
		return;

	if(j->type == JSON_TYPE_NUMBER)
	{
		switch(j->value.num.type)
		{
		case NT_CHAR:
			sprintf_s(buf,sizeof(buf),"%d",j->value.num.value.byteValue);
			break;

		case NT_SHORT:
			sprintf_s(buf,sizeof(buf),"%d",j->value.num.value.shortValue);
			break;

		case NT_INT:
			sprintf_s(buf,sizeof(buf),"%d",j->value.num.value.intValue);
			break;

		case NT_LONG:
			sprintf_s(buf,sizeof(buf),"%ld",j->value.num.value.longValue);
			break;

		case NT_FLOAT:
			sprintf_s(buf,sizeof(buf),"%f",j->value.num.value.floatValue);
			break;

		case NT_DOUBLE:
			sprintf_s(buf,sizeof(buf),"%lf",j->value.num.value.doubleValue);
			break;

		case NT_NULL:
			sprintf_s(buf,sizeof(buf),"(null)");
			break;

		default:
			sprintf_s(buf,sizeof(buf),"<UNKNOW>");
			break;
		}

		//	��ӵ�ĩβ
		json_cat(pd,l,buf);
	}

}

//=======================================================================
//	����: 	json_number_dump
//	����:
//	����:
//	˵��:	��������
//=======================================================================
void json_number_dump(const jobject * j)
{
	if(!j)
		return;

	if(j->type == JSON_TYPE_NUMBER)
	{
		switch(j->value.num.type)
		{
		case NT_CHAR:
			PRINTF("%d",j->value.num.value.byteValue);
			break;

		case NT_SHORT:
			PRINTF("%d",j->value.num.value.shortValue);
			break;

		case NT_INT:
			PRINTF("%d",j->value.num.value.intValue);
			break;

		case NT_LONG:
			PRINTF("%d",j->value.num.value.longValue);
			break;

		case NT_FLOAT:
			PRINTF("%f",j->value.num.value.floatValue);
			break;

		case NT_DOUBLE:
			PRINTF("%f",j->value.num.value.doubleValue);
			break;

		case NT_NULL:
			PRINTF("(null)");
			break;

		default:
			PRINTF("<UNKNOW>");
			break;
		}
	}
}

#endif

