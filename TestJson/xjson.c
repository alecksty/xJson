//=======================================================================
//
//	ģ��:	JSON ����
//	
//	�汾:	1.00
//
//	����:	2019-5-25
//
//	����:	ʩ̽��
//
//	˵��:	����������Json
//
//=======================================================================

#include "xjson.h"

#ifdef SUPPORT_XJSON

//	�ʷ�����
static S_WordItem g_words;

//=======================================================================
//	����: 	json_new
//	����:
//	����:
//	˵��:	�����ڴ�(��Ƭ������ʹ������������)
//=======================================================================
jobject * json_new(void)
{
	jobject * j = NULL;

	#ifdef SUPPORT_MALLOC
	j = (jobject *)malloc(sizeof(jobject));
	#endif //SUPPORT_MALLOC

	return j;
}

//=======================================================================
//	����: 	json_free
//	����:
//	����:
//	˵��:	�ͷ��ڴ�
//=======================================================================
void json_free(jobject* j)
{
	#ifdef SUPPORT_MALLOC
	free(j);
	#endif //SUPPORT_MALLOC
}

//=======================================================================
//	����: 	json_init
//	����:
//	����:
//	˵��:	��ʼ��
//=======================================================================
void json_init(jobject * j)
{
	memset(j,0,sizeof(jobject));
}

//=======================================================================
//	����: 	json_find
//	����:
//	����:
//	˵��:	����
//=======================================================================
jobject *json_find(jobject * j,jcstring key)
{
	jobject * jo = NULL;

	if(!j)
		return NULL;

	if(!key)
		return NULL;

	//	��ǰƥ��
	if(j->name)
	{
		if(!strcmp(j->name,key))
		{
			return j;
		}
	}

	//	����������
	if(j->type == JSON_TYPE_OBJECT)
	{
		jo = j->child;
	}
	else if(j->type == JSON_TYPE_ARRAY)
	{
		jo = j->child;
	}
	else
	{
		return NULL;
	}

	while(jo)
	{
		//	����ƥ��
		if(!strcmp(jo->name,key))
		{
			return jo;
		}
		jo = jo->next;
	}
	return NULL;
}

//=======================================================================
//	����: 	json_enum
//	����:
//	����:
//	˵��:	ö��
//=======================================================================
jobject *json_enum(jobject * j,int index)
{
	int n 	= 0;
	jobject *jo = NULL;

	if(!j)
		return NULL;

	if(j->type == JSON_TYPE_OBJECT)
	{
		jo = j->child;
	}
	else if(j->type == JSON_TYPE_ARRAY)
	{
		jo = j->child;
	}
	else
	{
		return NULL;
	}

	while(jo){
		//	����ƥ��
		if(n == index)
		{
			return jo;
		}
		jo = jo->next;
		n++;
	}
	
	return NULL;
}

//=======================================================================
//	����: 	json_parser
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_parser(jobject *j,jcstring s)
{
	S_WordItem *pw = &g_words;

	if(!j)
		return 0;

	if(!s)
		return 0;

	PRINTF("parser : %s\r\n",s);

	//	��ʼ��
	word_init(pw,s);

	//	��ȡ
	word_read(pw);

	//	����
	if(json_value_parser(pw,j))
	{
		PRINTF("+-----------------+\r\n");
		PRINTF("| Parser Success! |\r\n");
		PRINTF("+-----------------+\r\n");
		return 1;
	}

	PRINTF("+-----------------+\r\n");
	PRINTF("| Parser Failed!  |\r\n");
	PRINTF("+-----------------+\r\n");
	return 0;
}

//=======================================================================
//	����: 	json_release
//	����:
//	����:
//	˵��:	��������
//=======================================================================
int json_release(jobject *j)
{	
	jobject *jr = NULL;	
	jobject *jo = NULL;

	if(!j)
		return 0;

	if(j->type == JSON_TYPE_OBJECT)
	{
		jo = j->child;
	}
	else if(j->type == JSON_TYPE_ARRAY)
	{
		jo = j->child;
	}
	else
	{
		//	ֱ���ͷ�
		json_free(j);
		return 1;
	}

	while(jo)
	{
		jr = jo;
		//	��һ��
		jo = jo->next;
		//	�ͷ�
		json_release(jr);
	}

	j->child 	= NULL;
	j->next 	= NULL;		
	return 1;
}

//=======================================================================
//	����: 	json_add
//	����:
//	����:
//	˵��:	���
//=======================================================================
int json_add(jobject * j,jobject * jsub)
{
	if(!j)
		return 0;
	
	if(j->type == JSON_TYPE_OBJECT)
	{
		json_object_add(j,jsub);
	}
	else if(j->type == JSON_TYPE_ARRAY)
	{
		json_array_add(j,jsub);
	}
	else
	{
		//	��ͨ���󣬲�������Ӷ���
		return 0;
	}
	return 1;
}

//=======================================================================
//	����: 	json_cat
//	����:
//	����:
//	˵��:	���Ϊ�ַ���
//=======================================================================
void json_cat(char *d,int l,jcstring s)
{
	char *pd 	= d;
	char *ps 	= s;
	int len 	= strlen(d);

	if(!d)
		return;

	if(!l)
		return;

	if(!s)
		return;
	
	while(len < l - 1){
		pd[len] = *ps;

		ps ++;
		len ++;
	}

	pd[len] = 0;
}

//=======================================================================
//	����: 	json_tostring
//	����:
//	����:
//	˵��:	���Ϊ�ַ���
//=======================================================================
jcstring json_tostring(const jobject *j,char *pd,int l)
{
	if(!j)
	{
		PRINTF("j is (null)\r\n");
		return NULL;
	}

	if(!pd)
	{
		PRINTF("pd is (null)\r\n");
		return NULL;
	}

	if(!l)
	{
		PRINTF("l == 0\r\n");
		return NULL;
	}

	json_cat(pd,l,XJSON_STRING_SIGN);
	json_cat(pd,l,j->name);
	json_cat(pd,l,XJSON_STRING_SIGN);
	json_cat(pd,l,":");

	switch(j->type)
	{
	case JSON_TYPE_BOOL:
		json_bool_tostring(j,pd,l);
		break;

	case JSON_TYPE_NUMBER:
		json_number_tostring(j,pd,l);
		break;

	case JSON_TYPE_STRING:
		json_string_tostring(j,pd,l);
		break;

	case JSON_TYPE_OBJECT:
		json_object_tostring(j,pd,l);
		break;

	case JSON_TYPE_ARRAY:
		json_array_tostring(j,pd,l);
		break;

	default:
		PRINTF("#unknow type:%d,",j->type);
		break;
	}

	return pd;
}

//=======================================================================
//	����: 	json_level
//	����:
//	����:
//	˵��:	������
//=======================================================================
void json_level(const jobject *j)
{
	for(int i = 0; i <= j->level; i++)
	{
		PRINTF("\t");
//		PRINTF("    ");
	}
}

//=======================================================================
//	����: 	json_dump
//	����:
//	����:
//	˵��:	���Ϊ�ַ���
//=======================================================================
void json_dump(const jobject *j)
{
	if(!j)
	{
		PRINTF("j is (null)\r\n");
		return;
	}

	PRINTF("%s : ",j->name);

	switch(j->type)
	{
	case JSON_TYPE_BOOL:
		json_bool_dump(j);
		break;

	case JSON_TYPE_NUMBER:
		json_number_dump(j);
		break;

	case JSON_TYPE_STRING:
		json_string_dump(j);
		break;

	case JSON_TYPE_OBJECT:
		json_object_dump(j);
		break;

	case JSON_TYPE_ARRAY:
		json_array_dump(j);
		break;

	default:
		PRINTF("#unknow type:%d,",j->type);
		break;
	}

	PRINTF("\r\n");
}

//=======================================================================
//	����: 	json_test
//	����:
//	����:
//	˵��:	���Ϊ�ַ���
//=======================================================================
void json_test(void)
{
	jobject js;

	json_init(&js);

	json_parser(&js,"{"
			"'boolean':true,"
			"'num':1234,"
			"'text':'string',"
			"'obj':{"
				"'sub1':0,"
				"'sub2':true,"
				"'sub3':{'a':true,'b':false,'c':'Good Bye!'},"
				"'sub3':[4,3,2,1]"
			"},"
			"'array':[1,2,3,'test array',5]"
			"}");

	jbool a 		= json_bool_value(json_find(&js,"boolean"));
	int b 			= json_number_ivalue(json_find(&js,"num"));
	jcstring c 		= json_string_value(json_find(&js,"text"));

	PRINTF("boolean = %d\r\n",a);
	PRINTF("num     = %d\r\n",b);
	PRINTF("text    = %s\r\n",c);

	jobject *j1 = json_bool_create(NULL,"Boolean",TRUE);
	jobject *j2 = json_number_create(NULL,"Integer",12345);
	jobject *j3 = json_string_create(NULL,"String","Text is Here!");

	json_add(&js,j1);
	json_add(&js,j2);
	json_add(&js,j3);
	
	{
		char out[200];
		memset(out,0,sizeof(out));
		json_tostring(&js,out,sizeof(out));
		PRINTF("\r\njson=%s\r\n",out);
	}
	
	json_dump(&js);
}

#endif //SUPPORT_XJSON

