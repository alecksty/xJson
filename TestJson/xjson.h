
#ifndef _X_JSON_API_
#define _X_JSON_API_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//=======================================================================
//
//=======================================================================
//	֧��XJSON
#define SUPPORT_XJSON
//	֧���ڴ����
#define SUPPORT_MALLOC
//	���滺��
#define SUPPORT_SAVE_BUFFER

//=======================================================================
//
//=======================================================================
//	����
#define PRINTF						printf
//	���ֻ���
#define STRING_MAX_LEN				128
//	�������
//#define XJSON_STRING_SIGN			"\""
#define XJSON_STRING_SIGN			"\'"

//=======================================================================
//	��ʼ����
//=======================================================================
#define XJSON_CHAR_OBJ_BEGIN		'{'
#define XJSON_CHAR_OBJ_END			'}'

#define XJSON_CHAR_ARR_BEGIN		'['
#define XJSON_CHAR_ARR_END			']'

#define XJSON_CHAR_STR1_BEGIN		'\"'
#define XJSON_CHAR_STR1_END			'\"'

#define XJSON_CHAR_STR2_BEGIN		'\''
#define XJSON_CHAR_STR2_END			'\''

#define XJSON_CHAR_SPLITE			','
#define XJSON_CHAR_SEMECOM			':'

#ifdef __cplusplus
extern "C" {
#endif

//=======================================================================
//	�ַ���
//=======================================================================
//	�ַ���
typedef char * jstring;
//	�����ַ���
typedef const char * jcstring;

//=======================================================================
//	��������
//=======================================================================
typedef enum _e_json_bool{
	FALSE = 0,
	TRUE = 1,
}jbool;

//=======================================================================
//	��ֵ����
//=======================================================================
typedef enum _e_json_num_type{
	NT_NULL = 0,
	NT_CHAR,
	NT_SHORT,
	NT_INT,
	NT_LONG,
	NT_FLOAT,
	NT_DOUBLE,
}jnumType;

typedef union _u_json_num_value{
	char 	byteValue;
	short 	shortValue;
	int 	intValue;
	long 	longValue;

	float 	floatValue;
	double 	doubleValue;
}jnumValue;

//=======================================================================
//	��������
//=======================================================================
typedef struct _s_json_num{
	//	����
	jnumType type;
	//	��ֵ
	jnumValue value;
}jnum;

typedef struct _s_json_item jobject;

//=======================================================================
//	���Ͷ���
//=======================================================================
typedef enum _e_json_type{
	//	δ��ʼ��
	JSON_TYPE_UNINIT = -1,
	//	��
	JSON_TYPE_NULL = 0,
	//	����
	JSON_TYPE_BOOL,
	//	��ֵ
	JSON_TYPE_NUMBER,
	//	�ַ���
	JSON_TYPE_STRING,
	//	����
	JSON_TYPE_OBJECT,
	//	����
	JSON_TYPE_ARRAY,

}jsonType;

//=======================================================================
//	����Ԫ��
//=======================================================================
typedef union _u_json_value{
	//	����
	jcstring  text;
	//	��ֵ
	jnum 	 num;
	//	����
	jbool	 boo;

}jsonValue;

//=======================================================================
//	����Ԫ��
//=======================================================================
typedef struct _s_json_item{

	#ifdef SUPPORT_SAVE_BUFFER
	//	����
	char 		aName[STRING_MAX_LEN];
	//	����
	char 		aValue[STRING_MAX_LEN];
	#endif //SUPPORT_SAVE_BUFFER

	//	���
	int 		level;

	//	����
	jcstring 	name;

	//	����
	jsonType 	type;

	//	��ֵ
	jsonValue 	value;

	//	����
	jobject * 	child;

	//	����
	jobject * 	next;	
}jobject;

//=======================================================================
//=	����ļ�
//=======================================================================
#include "xjson_word.h"
#include "xjson_name.h"
#include "xjson_bool.h"
#include "xjson_number.h"
#include "xjson_string.h"
#include "xjson_object.h"
#include "xjson_array.h"

//=======================================================================
//=	ͨ�ýӿ�
//=======================================================================
jobject * 	json_new(void);
void 		json_init(jobject * j);
void 		json_free(jobject * j);
int 		json_release(jobject * j);

jobject *	json_find(jobject * j,jcstring key);
jobject *	json_enum(jobject * j,int index);
int 		json_parser(jobject * j,jcstring s);
int 		json_add(jobject * j,jobject *jsub);
void 		json_cat(char * d,int l,jcstring s);

jcstring 	json_tostring(const jobject *j,char *pd,int l);

void 		json_level(const jobject *j);
void 		json_dump(const jobject *j);

void 		json_test(void);

#ifdef __cplusplus
};
#endif

#endif //_XJSON_API_

