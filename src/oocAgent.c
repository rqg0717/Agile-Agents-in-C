/** @file oocAgent.c
 *
 * @brief Agent.
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
 */

#include <oocAgent.h>
#include <string.h>
#include <stdio.h>


static void finalize_agent(oocObject* object)
{
	oocAgent *p_agent = SUB_PTR(object, oocObject, oocAgent);
	if (p_agent->p_id)
	{
		oocString_delete(p_agent->p_id);
	}
	if (p_agent->p_name)
	{
		oocString_delete(p_agent->p_name);
	}
}

static void action_agent(IAction* a)
{
    printf("this is agent action! \n");
}

CTOR(oocAgent)
	SUPER_CTOR(oocObject);
	this_->p_id = NULL;
	this_->p_name = NULL;
	FUNCTION_BIND(IAction.action, action_agent);
	FUNCTION_BIND(oocObject.finalize, finalize_agent);END_CTOR

DTOR(oocAgent)
	SUPER_DTOR(oocObject);END_DTOR

/*** end of file ***/
