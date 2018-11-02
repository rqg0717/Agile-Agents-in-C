/** @file ooc.h
*
* @brief base.
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/

#ifndef OOC_H
#define OOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#define MAX_PATH_LEN			(128)

#define ABS_CLASS(obj)						\
	typedef struct s_##obj obj;				\
	extern void obj##_ctor(obj * this_); 	\
	extern void obj##_dtor(obj * this_);  	\
	extern void obj##_delete(obj * this_);	\
	struct s_##obj

#define CLASS(obj)									\
	typedef struct s_##obj obj;						\
	extern obj * obj##_new(const char * p_file, int32_t n_line);	\
	extern void obj##_ctor(obj* this_);				\
	extern void obj##_dtor(obj * this_);			\
	extern void obj##_delete(obj * this_);			\
	struct s_##obj

#define ABS_CTOR(obj)								\
	void obj##_ctor(obj* this_){
#define END_ABS_CTOR 	}

#define CTOR(obj)									\
	obj * obj##_new(const char * p_file, int32_t n_line){ 	\
		obj *this_;									\
		this_ = (obj *)obj_malloc(sizeof(obj), #obj, p_file, n_line);	\
		if(!this_){									\
			return NULL;							\
		}											\
		obj##_ctor(this_);							\
		return this_;								\
	}												\
	void obj##_ctor(obj * this_){
#define END_CTOR		}

#define DTOR(obj)						\
	void obj##_delete(obj* this_){		\
		obj##_dtor(this_);				\
		obj_free((void *)this_);		\
	}									\
	void obj##_dtor(obj * this_){
#define END_DTOR 		}

#define EXTENDS(obj)		struct s_##obj obj

#define SUPER_PTR(this_, father)		\
	((father *)(&(this_->father)))
#define SUPER_PTR_2(this_, father, grandfather)		\
	SUPER_PTR(SUPER_PTR(this_, father), grandfather)

#define SUB_PTR(this_, self, child)		\
	((child *)((char *)this_ - offsetof(child, self)))
#define SUB_PTR_2(this_, self, child, grandchild)\
	SUB_PTR(SUB_PTR(this_, self, child), child, grandchild)

#define SUPER_CTOR(father)				\
	father##_ctor(SUPER_PTR(this_, father))

#define SUPER_DTOR(father)				\
	father##_dtor(SUPER_PTR(this_, father))

#define FUNCTION_BIND(func_1, func_2)	\
	this_->func_1 = func_2


	extern void * obj_malloc(size_t size, const char * p_obj, const char * p_file, int32_t n_line);

	extern void obj_free(void * p_mem_block);

	extern void check_mem_leak();


#ifdef __cplusplus
}
#endif

#endif /* OOC_H */
/*** end of file ***/
