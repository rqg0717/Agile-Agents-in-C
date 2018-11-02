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
		int32_t n_speed;
		int32_t (*get_Speed)(Sensor * this_);
		void(*set_Speed)(Sensor * this_, int32_t n_speed);
		oocString* (*get_ID)(Sensor * this_);
		oocString* (*get_Name)(Sensor * this_);
		void(*init)(Sensor *this_, const char * p_id, const char * p_name);
	};
	
#ifdef __cplusplus
}
#endif

#endif /* SENSOR_H */
/*** end of file ***/
