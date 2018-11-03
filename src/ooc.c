/** @file ooc.c
*
* @brief base.
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*
* Permission to use, copy, modify, and distribute this software and
* its documentation for any purpose, without fee, and without a
* written agreement is hereby granted, provided that the above
* copyright notice and this paragraph and the following two
* paragraphs appear in all copies.
*
* IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
* LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
* DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS
* IS" BASIS, AND THE AUTHOR HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE,
* SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*
*/

#include <ooc.h>
#include <stdio.h>
#include <string.h>

/* object linked list */
typedef struct
{
	char file[MAX_PATH_LEN];		//source file - only for debugging memory leak
	int32_t n_line;					//line number - only for debugging memory leak
	void* p_addr;					//address
	size_t size;					//memory block size
	struct mem_block_list * next;	//next block
} mem_block_list;

static mem_block_list * p_obj_list_s = NULL;

/**
 * [allocate memory and record]
 * @param size [memory block size]
 * @param p_obj [name of the object]
 * @param p_file [source file]
 * @param n_line [line]
 */
void* obj_malloc(size_t size, const char * p_obj, const char * p_file, int32_t n_line)
{
	void *p_addr = malloc(size);
	assert(p_addr != NULL);
	if (p_addr) {
		mem_block_list *p_objlist = (mem_block_list*)malloc(
			sizeof(mem_block_list));
		if (!p_objlist) {
			printf("Error! allocate mem_block_list failed.\r\n");
			exit(1);
		}

		if (strlen(p_file) >= MAX_PATH_LEN) {
			printf("Error! file name is more than %d characters:%s.\r\n",
				MAX_PATH_LEN, p_file);
			exit(1);
		}

		strncpy(p_objlist->file, p_file, strlen(p_file));
		p_objlist->n_line = n_line;
		p_objlist->p_addr = p_addr;
		p_objlist->size = size;
		p_objlist->next = p_obj_list_s;
		p_obj_list_s = p_objlist;

		//printf("allocate memory in %p, size: %lu, object: %s, file: %s, line: %d.\r\n",
		//	p_addr, size, p_obj, p_file, n_line);
	}
	return p_addr;
}

/**
 * [deallocate memory and remove the object]
 * @param void * p_mem_block [object pointer]
 */
void obj_free(void * p_mem_block)
{
	mem_block_list *p_pre = NULL;
	mem_block_list *p_cur = p_obj_list_s;
	while (p_cur) {
		if (p_cur->p_addr == p_mem_block) {

			printf("free memory at %p, size: %lu.\r\n",	p_cur->p_addr, p_cur->size);

			if (p_pre == NULL) {
				p_obj_list_s = p_cur->next;
			}
			else {
				p_pre->next = p_cur->next;
			}
			free(p_cur);
			p_cur = NULL;
			free(p_mem_block);
			p_mem_block = NULL;
			return;
		}
		else {
			p_pre = p_cur;
			p_cur = p_cur->next;
		}
	}
	if (!p_cur) {
		printf("Error! attemped to free invalid memory.\r\n");
		exit(1);
	}
}

/**
 * [check memory leak]
 */
void check_mem_leak(void)
{
	mem_block_list *p_cur = p_obj_list_s;
	if (p_cur != 0) {
		printf("Warning! memory leak:\r\n");
		while (p_cur) {
			printf("memory leaking at: %p, size: %lu, file: %s, line: %d.\r\n",
				p_cur->p_addr, p_cur->size, p_cur->file, p_cur->n_line);
			p_cur = p_cur->next;
		}
	}
	else {
		printf("No memory leak.\r\n");
	}
}


/*** end of file ***/
