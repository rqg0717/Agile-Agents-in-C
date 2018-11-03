/** @file oocObject.c
*
* @brief object.
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/

#include <oocObject.h>

ABS_CTOR(oocObject)
this_->n_count = 0;
END_ABS_CTOR

DTOR(oocObject)
this_->finalize(this_);
END_DTOR

/*** end of file ***/
