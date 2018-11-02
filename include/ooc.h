/** @file ooc.h
*
* @brief base.
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*
* @discussion OOC structure inspired from C99 Library, e.g.:
*
 * 	typedef struct __sFILE   __FILE;
 *  struct __sFILE {
		unsigned char *_p;
		int	_r;
		int	_w;
		short	_flags;
		short	_file;
		struct __sbuf _bf;
		int	_lbfsize;
		...
		void *	_cookie;
		...
		_READ_WRITE_RETURN_TYPE (*_read) (struct _reent *, void *,
						   char *, _READ_WRITE_BUFSIZE_TYPE);
		_READ_WRITE_RETURN_TYPE (*_write) (struct _reent *, void *,
							const char *,
							_READ_WRITE_BUFSIZE_TYPE);
		_fpos_t (*_seek) (struct _reent *, void *, _fpos_t, int);
		int (*_close) (struct _reent *, void *);
		...
	};
 *
 * ///////////////////////////////////////////////
 *  __FILE *p_file = NULL;
	p_file = fopen("D:/test.txt", "w+");
	p_file->_close(p_file->_data, p_file->_cookie);
	//////////////////////////////////////////////
	 * p_file->_close = __sclose; //FUNCTION BIND
	 * =>
	//////////////////////////////////////////////
	 * int __sclose (struct _reent *ptr, void *cookie)
		{
		  FILE *fp = (FILE *) cookie;

		  return _close_r (ptr, fp->_file);
		}
		=>
		...

 ***********************************************/
#pragma once

#ifndef OOC_H
#define OOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#define MAX_PATH_LEN			(128)			/* the maximum length for a path */

/* Abstract Class is used as a base class */
#define ABS_CLASS(obj)						\
	typedef struct stru_##obj obj;				\
	extern void obj##_ctor(obj * this_); 	\
	extern void obj##_dtor(obj * this_);  	\
	extern void obj##_delete(obj * this_);	\
	struct stru_##obj

/* Abstract Class Constructor */
#define ABS_CTOR(obj)								\
	void obj##_ctor(obj* this_){
#define END_ABS_CTOR 	}

/* A class template */
#define CLASS(obj)									\
	typedef struct stru_##obj obj;						\
	extern obj * obj##_new(const char * p_file, int32_t n_line);	\
	extern void obj##_ctor(obj* this_);				\
	extern void obj##_dtor(obj * this_);			\
	extern void obj##_delete(obj * this_);			\
	struct stru_##obj

/**
 * Class Constructor
 * inspired form new operator in C++
 * allocate memory and put the object to a object list in obj_malloc
 * Note: const char * p_file, int32_t n_line are only for debugging memory leak
 */
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

/**
 * Class Destructor
 * inspired form delete operator in C++
 * deallocate the memory allocated with CTOR and remove the object form the list.
 */
#define DTOR(obj)						\
	void obj##_delete(obj* this_){		\
		obj##_dtor(this_);				\
		obj_free((void *)this_);		\
	}									\
	void obj##_dtor(obj * this_){
#define END_DTOR 		}

/* Inheritance inspired from Java */
#define EXTENDS(obj)		struct stru_##obj obj

/**
 * this_ is child class pointer
 * parent is parent class pointer
 * return parent class pointer
 */
#define SUPER_PTR(this_, parent)		\
	((parent *)(&(this_->parent)))

/**
 * this_ is child class pointer
 * parent is parent class pointer
 * grandfather is grandparent class pointer
 * return grandparent class pointer
 */
#define SUPER_PTR_2(this_, parent, grandparent)		\
	SUPER_PTR(SUPER_PTR(this_, parent), grandparent)

/**
 * this_ is parent class pointer
 * child is child class pointer
 * return child class pointer
 */
#define SUB_PTR(this_, self, child)		\
	((child *)((char *)this_ - offsetof(child, self)))

/**
 * this_ is grandparent class pointer
 * child is child class pointer
 * grandchild is grandchild class pointer
 * return grandchild class pointer
 */
#define SUB_PTR_2(this_, self, child, grandchild)\
	SUB_PTR(SUB_PTR(this_, self, child), child, grandchild)

/* Superclass Constructor */
#define SUPER_CTOR(parent)				\
	parent##_ctor(SUPER_PTR(this_, parent))

/* Superclass destructor */
#define SUPER_DTOR(parent)				\
	parent##_dtor(SUPER_PTR(this_, parent))

/* Function Bind */
#define FUNCTION_BIND(func_1, func_2)	\
	this_->func_1 = func_2

/* allocate memory to an object and put the object to a object list */
extern void * obj_malloc(size_t size, const char * p_obj, const char * p_file, int32_t n_line);

/* deallocate memory and remove the object from the list */
extern void obj_free(void * p_mem_block);

/* debug for memory leak */
extern void check_mem_leak();


#ifdef __cplusplus
}
#endif

#endif /* OOC_H */
/*** end of file ***/
