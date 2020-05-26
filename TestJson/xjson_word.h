#ifndef _JSON_WORD_API_H_
#define _JSON_WORD_API_H_

//=======================================================================
//	�궨��
//=======================================================================
//	���ʻ���
#define WORD_MAX_LEN		128

//=======================================================================
//	���Ͷ���
//=======================================================================
//	ʶ������
typedef enum _e_word_type{
	//	δ֪
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

//	�ʷ�����
typedef struct _s_word_item{
	//	����
	E_WordType 	type;

	//	����
	char 		buf[WORD_MAX_LEN];
	//	λ��
	int 		idx;
	
	//	����Դ
	const char * ps;
	//	λ��
	int 		pos;
	//	����
	int 		max;
}S_WordItem;

//=======================================================================
//	����
//=======================================================================
int char_is_space(int c);
int char_is_digit(int c);
int char_is_indent(int c);

int word_init(S_WordItem *pw,const char * s);
int word_getch(S_WordItem *pw);
int word_unget(S_WordItem *pw);
int word_read(S_WordItem *pw);

#endif //_JSON_WORD_API_H_

