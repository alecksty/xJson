#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

jobject * 	json_object_create( jobject * j,jcstring name,jobject a[],int l);
int 		json_object_clear(jobject * j);
int 		json_object_add(jobject * j,jobject * jsub);
int 		json_object_parser(S_WordItem *pw,jobject * j);
void 		json_object_tostring(const jobject * j,char * pd,int l);
void 		json_object_dump(const jobject * j);

#endif //_JSON_OBJECT_H_

