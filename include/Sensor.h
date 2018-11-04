/** @file Sensor.h
*
* @brief sensor
*
* @par
* COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
*/

#ifndef SENSOR_H
#define SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "oocString.h"
#include "oocAgent.h"

	/**
	 * Sensor Class
	 */
	CLASS(Sensor) {
		EXTENDS(oocAgent);
		IMPLEMENTS(IAction);

		int32_t n_speed;

		int32_t (*getSpeed)(Sensor * this_);
		void(*setSpeed)(Sensor * this_, int32_t n_speed);
		oocString* (*getID)(Sensor * this_);
		oocString* (*getName)(Sensor * this_);
		void(*init)(Sensor *this_, const char * p_id, const char * p_name);
	};
	
#ifdef __cplusplus
}
#endif

#endif /* SENSOR_H */
/*** end of file ***/
