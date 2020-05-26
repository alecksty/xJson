#ifndef _JSON_BOOL_H_
#define _JSON_BOOL_H_

jobject * 	json_bool_create(jobject * j,jcstring name,jbool value);
int 		json_bool_parser(S_WordItem *pw, jobject * j);
jbool 		json_bool_value(const jobject * j);
void 		json_bool_tostring(const jobject * j,char *pd,int l);
void 		json_bool_dump(const jobject * j);

#endif

