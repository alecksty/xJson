
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

//#define _DEBUG_THIS

//=======================================================================
//	����: 	char_is_space
//	����:
//	����:
//	˵��:	�жϿո�
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
//	����: 	char_is_digit
//	����:
//	����:
//	˵��:	��������
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
//	����: 	char_is_indent
//	����:
//	����:
//	˵��:	��������
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
//	����: 	word_init
//	����:
//	����:
//	˵��:	��ʼ�� - �ʷ�����
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
//	����: 	word_getch
//	����:
//	����:
//	˵��:	��ȡ�ַ�
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
//	����: 	word_unget
//	����:
//	����:
//	˵��:	�����ַ�
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
//	����: 	word_read
//	����:
//	����:
//	˵��:	��ȡ����
//=======================================================================
int word_read(S_WordItem *pw)
{
	int ch = 0;

	if(!pw)
		return 0;

	pw->idx = 0;
	
	//	���˿ո�
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
	//	�ַ���
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
	//	�ַ���
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
	//	����
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
	//	��ʶ��(�ؼ���)
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
	//	����
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

