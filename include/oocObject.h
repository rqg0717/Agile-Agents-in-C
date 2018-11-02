/** @file oocObject.h
*
* @brief object
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/

#ifndef OOCOBJECT_H
#define OOCOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ooc.h"

	ABS_CLASS(oocObject) {
		int32_t n_count;
		void(* finalize)(oocObject* p_obj);
	};

#ifdef __cplusplus
}
#endif

#endif /* OOCOBJECT_H */
/*** end of file ***/
