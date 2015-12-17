#ifndef DATA_H
#define DATA_H

void rawTob64(char * data, int length, char** out, int *o_length);
void hexToraw(char * data, int length, char** out, int *o_length);
void b64Toraw(char * data, int length, char** out, int *o_length);
void rawTohex(char * data, int length, char** out, int *o_length);


#endif
