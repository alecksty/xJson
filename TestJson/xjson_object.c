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
//	����: 	json_object_create
//	����:
//	����:
//	˵��:	
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
//	����: 	json_object_clear
//	����:
//	����:
//	˵��:	
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
		//	�ͷ�
		json_free(jr);
	}
	
	j->child = NULL;
	return 1;
}

//=======================================================================
//	����: 	json_object_add
//	����:
//	����:
//	˵��:	
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

	//	��һ�����ӡ�
	jo = j->child;

	//	Ϊ��
	if(jo == NULL)
	{
		//	���õ�һ������
		j->child = jsub;
	}	
	else
	{
		//	�ҵ����
		while(jo->next)
		{
			//	�ƶ�����һ��
			jo = jo->next;
		}

		//	���һ��
		jo->next = jsub;
	}

	jsub->level = j->level + 1;

	return 1;
}

//=======================================================================
//	����: 	json_object_parser
//	����:
//	����:
//	˵��:	��������
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
			//	����
			jnew = json_new();
			//	���
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
			
			//	����Ӷ���
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
//	����: 	json_object_tostring
//	����:
//	����:
//	˵��:	��������
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

			//	��һ��
			jo = jo->next;

			if(jo){
				json_cat(pd,l,",");
			}
		}		

		json_cat(pd,l,"}");
	}
}

//=======================================================================
//	����: 	json_object_dump
//	����:
//	����:
//	˵��:	
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

			//	��һ��
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

