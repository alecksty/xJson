#ifndef _JSON_STRING_H_
#define _JSON_STRING_H_

jobject * 	json_string_create(jobject * j,const char *name,const char * value);
int 		json_string_parser(S_WordItem *pw, jobject * j);
const char *json_string_value(const jobject * j);
void 		json_string_tostring(const jobject * j,char * pd,int l);
void 		json_string_dump(const jobject * j);

#endif //_JSON_STRING_H_

