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
//=======================================================================

#include "xjson.h"

#ifdef SUPPORT_XJSON

//=======================================================================
//	函数: 	json_array_create
//	参数:
//	返回:
//	说明:	
//=======================================================================
jobject * json_array_create( jobject * j,jcstring name,jobject a[],int l)
{
	if(!j)
	{
		j = json_new();
		json_init(j);
	}
	
	j->type = JSON_TYPE_ARRAY;
	j->name = name;

#ifdef SUPPORT_SAVE_BUFFER	
	strcpy_s(j->aName,sizeof(j->aName),name);
	j->name = j->aName;
#endif //SUPPORT_SAVE_BUFFER

	if(a && l > 0)
	{
		for(int i = 0; i < l; i++)
		{
			json_array_add(j,&a[i]);
		}
	}
	return j;
}

//=======================================================================
//	函数: 	json_array_clear
//	参数:
//	返回:
//	说明:	清空
//=======================================================================
int json_array_clear(jobject * j)
{
	jobject *jr = NULL;
	jobject *jo = j->child;

	while(jo)
	{
		jr = jo;
		jo = jo->next;
		//	释放
		json_release(jr);
	}
	
	j->next = NULL;
	return 1;
}

//=======================================================================
//	函数: 	json_array_add
//	参数:
//	返回:
//	说明:	添加成员
//=======================================================================
int json_array_add(jobject * j,jobject * jsub)
{
	jobject *jo = NULL;

	if(!j)
		return 0;

	if(!jsub)
		return 0;

	jo = j->child;

	if(jo == NULL)
	{
		j->child = jsub;
	}	
	else
	{
		//	找到最后
		while(jo->next)
		{
			jo = jo->next;
		}
		
		//	最后一个
		jo->next = jsub;
	}

	jsub->level = (j->level + 1);

	return 1;
}

//=======================================================================
//	函数: 	json_array_parser
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
int json_array_parser(S_WordItem *pw,jobject * j)
{
	jobject *jnew = NULL;

	//============
	// [
	//============
	if(pw->type == WT_ARRAY_LEFT){

		j->type 	= JSON_TYPE_ARRAY;
		j->child 	= NULL;
		
		do{
			//	分配
			jnew = json_new();

			//	初始化
			json_init(jnew);
			
			//============
			// Value
			//============
			word_read(pw);
			if(!json_value_parser(pw,jnew)){
				break;
			}
			
			//============
			//	添加
			//============
			json_array_add(j,jnew);
			
			//============
			// ,
			//============
			word_read(pw);			
		}while(pw->type == WT_SIGNAL_SPLITE);

		//============
		// ]
		//============
		if(pw->type != WT_ARRAY_RIGHT){
			PRINTF("#ERROR : miss \']\'\r\n");
			return 0;
		}

		return 1;
	}
	return 0;
}

//=======================================================================
//	函数: 	json_array_tostring
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
void json_array_tostring(const jobject * j,char *pd,int l)
{
	const jobject *jo = NULL;

	if(!j)
		return;
	
	if(j->type == JSON_TYPE_ARRAY){

		json_cat(pd,l,"[");

		jo = j->child;

		if(!jo){
			json_cat(pd,l,"(null)");
		}

		while(jo){

			if(jo->type == JSON_TYPE_BOOL){
				json_bool_tostring(jo,pd,l);
			}else if(jo->type == JSON_TYPE_NUMBER){
				json_number_tostring(jo,pd,l);
			}else if(jo->type == JSON_TYPE_STRING){
				json_string_tostring(jo,pd,l);
			}else if(jo->type == JSON_TYPE_OBJECT){
				json_object_tostring(jo,pd,l);
			}else if(jo->type == JSON_TYPE_ARRAY){
				json_array_tostring(jo,pd,l);
			}else{
				json_cat(pd,l,"(unknow)");
			}

			jo = jo->next;

			if(jo){
				json_cat(pd,l,",");
			}
		}
		
		json_cat(pd,l,"]");
	}
}

//=======================================================================
//	函数: 	json_array_dump
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
void json_array_dump(const jobject * j)
{
	jobject *jo = NULL;

	if(!j)
		return;
	
	if(j->type == JSON_TYPE_ARRAY){

		PRINTF("[");

		jo = j->child;

		if(!jo){
			PRINTF("(null)");
		}
		
		PRINTF("\r\n");

		while(jo){
			
			jo->level = j->level + 1;

			json_level(jo);
			if(jo->type == JSON_TYPE_BOOL){
				json_bool_dump(jo);
			}else if(jo->type == JSON_TYPE_NUMBER){
				json_number_dump(jo);
			}else if(jo->type == JSON_TYPE_STRING){
				json_string_dump(jo);
			}else if(jo->type == JSON_TYPE_OBJECT){
				json_object_dump(jo);
			}else if(jo->type == JSON_TYPE_ARRAY){
				json_array_dump(jo);
			}else{
				PRINTF("ERROR:unknow array\r\n");
			}

			jo = jo->next;

			if(jo){
				PRINTF(",");				
			}
			PRINTF("\r\n");
		}

		json_level(j);
		
		PRINTF("]");
	}
}

#endif

