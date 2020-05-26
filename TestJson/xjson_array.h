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
#ifndef _JSON_ARRAY_H_
#define _JSON_ARRAY_H_

jobject * 	json_array_create(jobject * j,jcstring name,jobject a[],int l);
int 		json_array_clear(jobject * j);
int 		json_array_add(jobject * j,jobject * sub);
int 		json_array_parser(S_WordItem *pw,jobject * j);
void 		json_array_tostring(const jobject * j,char *pd,int l);
void 		json_array_dump(const jobject * j);

#endif //_JSON_ARRAY_H_

