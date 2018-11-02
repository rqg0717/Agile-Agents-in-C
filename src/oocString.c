/** @file oocString.c
*
* @brief string.
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/


#include <string.h>
#include <stdio.h>

#include "oocString.h"

static void init_string(oocString * this_, const char * c_str) 
{
	this_->p_string = (char *)obj_malloc(sizeof(char) * strlen(c_str) * 2,
		"oocString", __FILE__, __LINE__);
	strncpy(this_->p_string, c_str, strlen(c_str) + 1);
}

static int32_t get_len(oocString * this_) 
{
	return strlen((const char*)this_->p_string);
}

static char * get_c_str(oocString * this_) 
{
	return this_->p_string;
}

static void print_str(oocString * this_) 
{
	printf("%s\r\n", this_->p_string);
}

static oocString * get_substr(oocString * this_, int32_t off, int32_t len)
{
	if (off < 0) 
	{
		return NULL;
	}
	if (off + len > this_->length(this_) || len == 0) 
	{
		len = this_->length(this_) - off;
	}
	oocString* p_child = oocString_new(__FILE__, __LINE__);
	p_child->p_string = (char *)obj_malloc(sizeof(char) * len * 2,
		"oocString_substr", __FILE__, __LINE__);
	memcpy(p_child->p_string, this_->p_string + off, len);
	p_child->p_string[len] = '\0';

	return p_child;
}

static int32_t find_string(oocString * this_, const char * str)
{
	char *p = NULL;
	int32_t fLen = 0;
	int32_t cLen = 0;
	int32_t i = 0, j = 0;

	if (this_ == NULL || str == NULL || this_->p_string == NULL)
	{
		return -1;
	}

	fLen = this_->length(this_);
	cLen = strlen(str);
	if (cLen > fLen) 
	{
		return -1;
	}

	while (i <= fLen - cLen)
	{
		p = this_->p_string + i;
		if (*p == *str) {
			for (j = 1; j < cLen; j++) 
			{
				if (*(p + j) != *(str + j))
				{
					break;
				}
			}
			if (j >= cLen) 
			{
				break;
			}
		}
		i++;
	}
	if (i > fLen - cLen) 
	{
		return -1;
	}
	else
	{
		return i;
	}
}


static int32_t rfind_string(oocString * this_, const char * str)
{
	char *p = NULL;
	int32_t fLen = 0;
	int32_t cLen = 0;
	int32_t i = 0, j = 0;

	if (this_ == NULL || str == NULL || this_->p_string == NULL) 
	{
		return -1;
	}
	
	fLen = this_->length(this_);
	cLen = strlen(str);
	if (cLen > fLen)
	{
		return -1;
	}

	while (i <= fLen - cLen) 
	{
		p = this_->p_string + fLen - cLen - i;

		if (*p == *str)
		{
			for (j = 1; j < cLen; j++)
			{
				if (*(p + j) != *(str + j))
				{
					break;
				}
			}
			if (j >= cLen) 
			{
				break;
			}
		}
		i++;
	}
	if (i > fLen - cLen) 
	{
		return -1;
	}
	else 
	{
		return fLen - cLen - i;
	}
}


static oocString * trim_string(oocString * this_)
{
	char *p = this_->c_str(this_);
	char *q = p;
	while (*p)
	{
		while (*p && *p != ' ') 
		{
			*q++ = *p++;
		}
		while (*p == ' ') 
		{
			p++;
		}
		if (q != this_->c_str(this_) && *p) 
		{
			*q++ = ' ';
		}
	}
	*q = '\0';
	return this_;
}

static void finalize_string(oocObject* object)
{
	oocString *str = SUB_PTR(object, oocObject, oocString);
	if (str->p_string) {
		obj_free(str->p_string);
	}
}


CTOR(oocString)
SUPER_CTOR(oocObject);
this_->p_string = NULL;
FUNCTION_BIND(init, init_string);
FUNCTION_BIND(length, get_len);
FUNCTION_BIND(c_str, get_c_str);
FUNCTION_BIND(substr, get_substr);
FUNCTION_BIND(find, find_string);
FUNCTION_BIND(rfind, rfind_string);
FUNCTION_BIND(trim, trim_string);
FUNCTION_BIND(print, print_str);
FUNCTION_BIND(oocObject.finalize, finalize_string);END_CTOR


DTOR(oocString)
SUPER_DTOR(oocObject);END_DTOR


/*** end of file ***/
