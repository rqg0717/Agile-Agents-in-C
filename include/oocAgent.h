/** @file oocAgent.h
*
* @brief agent
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/

#ifndef OOCAGENT_H
#define OOCAGENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "oocString.h"

	INTERFACE(IAction)
	{
		void (*action)(IAction* a);
	};

	/**
	 * Agent Class
	 */
	CLASS(oocAgent) {
		EXTENDS(oocObject);
		IMPLEMENTS(IAction);

		oocString  *p_name;
		oocString  *p_id;
	};
	
#ifdef __cplusplus
}
#endif

#endif /* OOCAGENT_H */
/*** end of file ***/
