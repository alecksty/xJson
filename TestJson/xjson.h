
#ifndef _X_JSON_API_
#define _X_JSON_API_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//=======================================================================
//
//=======================================================================
//	支持XJSON
#define SUPPORT_XJSON
//	支持内存分配
#define SUPPORT_MALLOC
//	保存缓存
#define SUPPORT_SAVE_BUFFER

//=======================================================================
//
//=======================================================================
//	调试
#define PRINTF						printf
//	文字缓存
#define STRING_MAX_LEN				128
//	输出符号
//#define XJSON_STRING_SIGN			"\""
#define XJSON_STRING_SIGN			"\'"

//=======================================================================
//	起始符号
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
//	字符串
//=======================================================================
//	字符串
typedef char * jstring;
//	常量字符串
typedef const char * jcstring;

//=======================================================================
//	布尔类型
//=======================================================================
typedef enum _e_json_bool{
	FALSE = 0,
	TRUE = 1,
}jbool;

//=======================================================================
//	数值类型
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
//	数据类型
//=======================================================================
typedef struct _s_json_num{
	//	类型
	jnumType type;
	//	数值
	jnumValue value;
}jnum;

typedef struct _s_json_item jobject;

//=======================================================================
//	类型定义
//=======================================================================
typedef enum _e_json_type{
	//	未初始化
	JSON_TYPE_UNINIT = -1,
	//	空
	JSON_TYPE_NULL = 0,
	//	布尔
	JSON_TYPE_BOOL,
	//	数值
	JSON_TYPE_NUMBER,
	//	字符串
	JSON_TYPE_STRING,
	//	对象
	JSON_TYPE_OBJECT,
	//	数组
	JSON_TYPE_ARRAY,

}jsonType;

//=======================================================================
//	对象元素
//=======================================================================
typedef union _u_json_value{
	//	文字
	jcstring  text;
	//	数值
	jnum 	 num;
	//	布尔
	jbool	 boo;

}jsonValue;

//=======================================================================
//	对象元素
//=======================================================================
typedef struct _s_json_item{

	#ifdef SUPPORT_SAVE_BUFFER
	//	名称
	char 		aName[STRING_MAX_LEN];
	//	内容
	char 		aValue[STRING_MAX_LEN];
	#endif //SUPPORT_SAVE_BUFFER

	//	深度
	int 		level;

	//	名称
	jcstring 	name;

	//	类型
	jsonType 	type;

	//	数值
	jsonValue 	value;

	//	对象
	jobject * 	child;

	//	数组
	jobject * 	next;	
}jobject;

//=======================================================================
//=	相关文件
//=======================================================================
#include "xjson_word.h"
#include "xjson_name.h"
#include "xjson_bool.h"
#include "xjson_number.h"
#include "xjson_string.h"
#include "xjson_object.h"
#include "xjson_array.h"

//=======================================================================
//=	通用接口
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

