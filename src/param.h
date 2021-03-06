//
//  param.c
//  test
//
//  Created by crinq on 07.12.13.
//  Copyright (c) 2013 Rene Hopf. All rights reserved.
//

#define MAX_PARAMS 32
#define MAX_PNAME 8
typedef char PNAME[MAX_PNAME];

struct param{
    PNAME names[MAX_PARAMS];
    enum {
      FLOAT,
      INT
    } types[MAX_PARAMS];
    union{
      volatile float *floats[MAX_PARAMS];
      volatile int *ints[MAX_PARAMS];
    };
		int param_count;
} PARAMS;

int strcmp(const char* s1, const char* s2);
void strncpy(char* dst, char* src, int n);

void param_init();

int is_param(char* name);

int register_float(char* name,volatile float *f);

int register_int(char* name,volatile int *i);

float get_param(char* name);

int set_param(char* name,volatile float f);

void list_param();
