//=======================================================================
//
//	模块:	JSON 数据的生成和解析
//	
//	版本:	1.00
//
//	日期:	2015-12-16
//
//	作者:	施探宇
//
//	说明:	解析和生成
//
//=======================================================================
#include "xjson.h"

#ifdef SUPPORT_XJSON

//=======================================================================
//	函数: 	json_number_create
//	参数:
//	返回:
//	说明:	
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
//	函数: 	json_number_parser
//	参数:
//	返回:
//	说明:	分配数据
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
//	函数: 	json_number_value
//	参数:
//	返回:
//	说明:	获取值
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
//	函数: 	json_number_ivalue
//	参数:
//	返回:
//	说明:	获取整数
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
//	函数: 	json_number_fvalue
//	参数:
//	返回:
//	说明:	获取浮点
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
//	函数: 	json_number_tostring
//	参数:
//	返回:
//	说明:	分配数据
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

		//	添加到末尾
		json_cat(pd,l,buf);
	}

}

//=======================================================================
//	函数: 	json_number_dump
//	参数:
//	返回:
//	说明:	分配数据
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

