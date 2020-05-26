#ifndef _JSON_WORD_API_H_
#define _JSON_WORD_API_H_

//=======================================================================
//	宏定义
//=======================================================================
//	单词缓存
#define WORD_MAX_LEN		128

//=======================================================================
//	类型定义
//=======================================================================
//	识别类型
typedef enum _e_word_type{
	//	未知
	WT_UNKNOW = 0,
	// 	{
	WT_OBJECT_LEFT,
	// 	}
	WT_OBJECT_RIGHT,
	// 	[
	WT_ARRAY_LEFT,
	// 	]
	WT_ARRAY_RIGHT,
	// 	,
	WT_SIGNAL_SPLITE,
	//  :
	WT_SIGNAL_HYPEN,
	// 	"STRING"
	WT_STRING,
	// 	01239
	WT_NUMBER,
	//	KEYWORD
	WT_IDENTIFY,
}E_WordType;

//	词法分析
typedef struct _s_word_item{
	//	类型
	E_WordType 	type;

	//	缓存
	char 		buf[WORD_MAX_LEN];
	//	位置
	int 		idx;
	
	//	输入源
	const char * ps;
	//	位置
	int 		pos;
	//	长度
	int 		max;
}S_WordItem;

//=======================================================================
//	函数
//=======================================================================
int char_is_space(int c);
int char_is_digit(int c);
int char_is_indent(int c);

int word_init(S_WordItem *pw,const char * s);
int word_getch(S_WordItem *pw);
int word_unget(S_WordItem *pw);
int word_read(S_WordItem *pw);

#endif //_JSON_WORD_API_H_

