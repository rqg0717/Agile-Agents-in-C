/** @file oocString.h
*
* @brief string
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/

#ifndef OOCSTRING_H
#define OOCSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "oocObject.h"

	/**
	 * String Class
	 */
	CLASS(oocString) {
		EXTENDS(oocObject);

		char * p_string;

		void(*init)(oocString * this_, const char * c_str);

		int32_t (*length)(oocString * this_);

		char * (*c_str)(oocString * this_);

		void (*print)(oocString * this_);

		oocString* (*substr)(oocString * this_, int32_t off, int32_t len);

		int32_t (*find)(oocString * this_, const char * str);

		int32_t (*rfind)(oocString * this_, const char * str);

		oocString * (*trim)(oocString * this_);
	};
	
#ifdef __cplusplus
}
#endif

#endif /* OOCSTRING_H */
/*** end of file ***/
