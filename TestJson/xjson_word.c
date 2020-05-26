
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

//#define _DEBUG_THIS

//=======================================================================
//	函数: 	char_is_space
//	参数:
//	返回:
//	说明:	判断空格
//=======================================================================
static int char_is_space(int c)
{
	switch(c)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return 1;
	}
	return 0;
}

//=======================================================================
//	函数: 	char_is_digit
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
static int char_is_digit(int c)
{
	if(c >= '0' && c <= '9')
	{
		return 1;
	}
	return 0;
}

//=======================================================================
//	函数: 	char_is_indent
//	参数:
//	返回:
//	说明:	分配数据
//=======================================================================
static int char_is_indent(int c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return 1;
	}
	else if(c >= 'a' && c <= 'z')
	{
		return 1;
	}
	else if(c =='_')
	{
		return 1;
	}
	return 0;
}

//=======================================================================
//	函数: 	word_init
//	参数:
//	返回:
//	说明:	初始化 - 词法分析
//=======================================================================
int word_init(S_WordItem *pw,const char * s)
{
	if(!pw)
		return 0;

	memset(pw,0,sizeof(S_WordItem));
	
	pw->ps 			= s;
	pw->pos 		= 0;
	
	pw->idx			= 0;
	pw->max			= strlen(s);
	pw->buf[0] 		= 0;

	pw->type 		= WT_UNKNOW;

#ifdef _DEBUG_THIS
	PRINTF("word_init(){\r\n");
	PRINTF("json=%s\r\n",s);
	PRINTF("max=%d}\r\n",pw->max);	
#endif

	return 1;
}

//=======================================================================
//	函数: 	word_getch
//	参数:
//	返回:
//	说明:	读取字符
//=======================================================================
int word_getch(S_WordItem *pw)
{
	if(!pw)
		return 0;

	if(pw->pos < pw->max){
		return pw->ps[pw->pos++];
	}
	
	return 0;
}

//=======================================================================
//	函数: 	word_unget
//	参数:
//	返回:
//	说明:	回退字符
//=======================================================================
int word_unget(S_WordItem *pw)
{
	if(!pw)
		return 0;

	if(pw->pos > 0){
		pw->pos--;
	}
	return pw->ps[pw->pos];
}

//=======================================================================
//	函数: 	word_read
//	参数:
//	返回:
//	说明:	读取单词
//=======================================================================
int word_read(S_WordItem *pw)
{
	int ch = 0;

	if(!pw)
		return 0;

	pw->idx = 0;
	
	//	过滤空格
	while(char_is_space(ch = word_getch(pw)));

	//	{
	if(ch == XJSON_CHAR_OBJ_BEGIN)
	{
		pw->type = WT_OBJECT_LEFT;
		pw->buf[pw->idx++] = ch;
	}
	// }
	else if(ch == XJSON_CHAR_OBJ_END)
	{
		pw->type = WT_OBJECT_RIGHT;
		pw->buf[pw->idx++] = ch;
	}
	// [
	else if(ch == XJSON_CHAR_ARR_BEGIN)
	{
		pw->type = WT_ARRAY_LEFT;
		pw->buf[pw->idx++] = ch;
	}
	// ]
	else if(ch == XJSON_CHAR_ARR_END)
	{
		pw->type = WT_ARRAY_RIGHT;
		pw->buf[pw->idx++] = ch;
	}
	// ,
	else if(ch == XJSON_CHAR_SPLITE)
	{
		pw->type = WT_SIGNAL_SPLITE;
		pw->buf[pw->idx++] = ch;
	}
	// :
	else if(ch == XJSON_CHAR_SEMECOM)
	{
		pw->type = WT_SIGNAL_HYPEN;
		pw->buf[pw->idx++] = ch;
	}
	//-----------------------
	//	字符串
	//-----------------------
	else if(ch == XJSON_CHAR_STR1_BEGIN)
	{
		pw->type 	= WT_STRING;
		do{
			ch = word_getch(pw);
			if(ch != XJSON_CHAR_STR1_END){
				pw->buf[pw->idx++] = ch;
			}else{
				break;				
			}
		}while(ch);
	}
	//-----------------------
	//	字符串
	//-----------------------
	else if(ch == XJSON_CHAR_STR2_BEGIN)
	{
		pw->type 	= WT_STRING;
		do{
			ch = word_getch(pw);
			if(ch != XJSON_CHAR_STR2_END){
				pw->buf[pw->idx++] = ch;
			}else{
				break;
			}
		}while(ch);
	}
	//-----------------------
	//	数字
	//-----------------------
	else if(char_is_digit(ch))
	{
		pw->type 	= WT_NUMBER;
		do{
			pw->buf[pw->idx++] = ch;
			ch = word_getch(pw);
		}while(char_is_digit(ch) || (ch == '.'));
		word_unget(pw);
	}
	//-----------------------
	//	标识符(关键字)
	//-----------------------
	else if(char_is_indent(ch))
	{
		pw->type 	= WT_IDENTIFY;
		do{
			pw->buf[pw->idx++] = ch;
			ch = word_getch(pw);
		}while(char_is_indent(ch)||char_is_digit(ch));
		word_unget(pw);
	}
	//-----------------------
	//	错误
	//-----------------------
	else
	{
		pw->type = WT_UNKNOW;
		PRINTF("#ERROR:unknow char(%c) at pos : %d.\r\n",ch,pw->pos);	
		return 0;
	}

	pw->buf[pw->idx++] = 0;

#ifdef _DEBUG_THIS
	PRINTF("[%03d],word(type:%d,buf:%s)\r\n",pw->pos,pw->type,pw->buf);
#endif

	return 1;
}

#endif

