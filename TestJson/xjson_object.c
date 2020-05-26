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
//	函数: 	json_object_create
//	参数:
//	返回:
//	说明:	
//=======================================================================
jobject * json_object_create( jobject * j,jcstring name,jobject a[],int l)
{
	if(!j)
	{
		j = json_new();
		json_init(j);
	}
	
	j->type = JSON_TYPE_OBJECT;
	j->name = name;

#ifdef SUPPORT_SAVE_BUFFER	
	strcpy_s(j->aName,sizeof(j->aName),name);
	j->name = j->aName;
#endif //SUPPORT_SAVE_BUFFER

	if(a && l > 0)
	{
		for(int i = 0; i < l; i++)
		{
			json_object_add(j,&a[i]);
		}
	}
	return j;
}

//=======================================================================
//	函数: 	json_object_clear
//	参数:
//	返回:
//	说明:	
//=======================================================================
int json_object_clear(jobject * j)
{
	if(!j)
		return 0;
	
	jobject *jr = NULL;
	jobject *jo = j->child;

	while(jo)
	{
		jr = jo;
		jo = jo->next;
		//	释放
		json_free(jr);
	}
	
	j->child = NULL;
	return 1;
}

//=======================================================================
//	函数: 	json_object_add
//	参数:
//	返回:
//	说明:	
//=======================================================================
int json_object_add(jobject * j,jobject * jsub)
{
	jobject *jo = NULL;

	if(!j)
		return 0;

	if(!jsub)
		return 0;

	if(j->type != JSON_TYPE_OBJECT)
		return 0;

	//	第一个孩子。
	jo = j->child;

	//	为空
	if(jo == NULL)
	{
		//	设置第一个孩子
		j->child = jsub;
	}	
	else
	{
		//	找到最后
		while(jo->next)
		{
			//	移动到下一个
			jo = jo->next;
		}

		//	最后一个
		jo->next = jsub;
	}

	jsub->level = j->level + 1;

	return 1;
}

//=======================================================================
//	函数: 	json_object_parser
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
int json_object_parser( S_WordItem *pw,jobject * j)
{
	jobject *jnew = NULL;
	
	if(!pw)
		return 0;

	if(!j)
		return 0;

	//============
	// {
	//============
	if(pw->type == WT_OBJECT_LEFT){

		j->type 		= JSON_TYPE_OBJECT;
		j->child 		= NULL;
		
		do{
			//	分配
			jnew = json_new();
			//	清空
			json_init(jnew);
			
			//============
			// NAME
			//============
			word_read(pw);
			if(!json_name_parser(pw,jnew)){
				PRINTF("#ERROR : miss {NAME}\r\n");
				return 0;
			}

			//============
			// :
			//============
			word_read(pw);
			if(pw->type != WT_SIGNAL_HYPEN){
				PRINTF("#ERROR : miss \':\'\r\n");
				return 0;
			}

			//============
			// VALUE
			//============
			word_read(pw);
			if(!json_value_parser(pw,jnew)){
				PRINTF("#ERROR : miss {VALUE}\r\n");
				break;
			}
			
			//	添加子对象
			json_object_add(j,jnew);

			//============
			// ,
			//============
			word_read(pw);
		}while(pw->type == WT_SIGNAL_SPLITE);

		//============
		// }
		//============
		if(pw->type != WT_OBJECT_RIGHT){
			PRINTF("#ERROR:miss \'}\'\r\n");
			return 0;
		}

		return 1;
	}
	return 0;
}

//=======================================================================
//	函数: 	json_object_tostring
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
void json_object_tostring(const jobject * j,char * pd,int l)
{
	const jobject *jo = NULL;

	if(!j)
		return;
	
	if(j->type == JSON_TYPE_OBJECT){

		json_cat(pd,l,"{");
		
		jo = j->child;

		if(!jo){
			json_cat(pd,l,"(null)");
		}
		
		while(jo){

			json_cat(pd,l,XJSON_STRING_SIGN);
			json_cat(pd,l,jo->name);
			json_cat(pd,l,XJSON_STRING_SIGN);
			json_cat(pd,l,":");

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
				json_cat(pd,l,"<unknow>");
			}

			//	下一个
			jo = jo->next;

			if(jo){
				json_cat(pd,l,",");
			}
		}		

		json_cat(pd,l,"}");
	}
}

//=======================================================================
//	函数: 	json_object_dump
//	参数:
//	返回:
//	说明:	
//=======================================================================
void json_object_dump(const jobject * j)
{
	jobject *jo = NULL;

	if(!j)
		return;
	
	if(j->type == JSON_TYPE_OBJECT){

		PRINTF("{");

		jo = j->child;

		if(!jo){
			PRINTF("(null)");
		}

		PRINTF("\r\n");

		while(jo){

			jo->level = j->level+1;

			json_level(jo);
			
			PRINTF("%s : ",jo->name);
			
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
				PRINTF("<unknow>");
			}

			//	下一个
			jo = jo->next;

			if(jo){
				PRINTF(",");				
			}
			PRINTF("\r\n");
		}		

		json_level(j);
		PRINTF("}");
	}
}

#endif

