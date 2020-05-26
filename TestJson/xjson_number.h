
#ifndef _JSON_NUMBER_H_
#define _JSON_NUMBER_H_

jobject * 	json_number_create(jobject * j,jcstring name,int value);
int 		json_number_parser(S_WordItem *pw,jobject * j);
jnumValue 	json_number_value(const jobject * j);
int 		json_number_ivalue(const jobject * j);
float 		json_number_fvalue(const jobject * j);
void 		json_number_tostring(const jobject * j,char * pd,int l);
void 		json_number_dump(const jobject * j);

#endif //_JSON_NUMBER_H_

