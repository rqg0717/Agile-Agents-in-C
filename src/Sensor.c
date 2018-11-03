/** @file Sensor.c
 *
 * @brief sensor.
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2017 James Ren. All rights reserved.
 */

#include <string.h>
#include <stdio.h>
#include <Sensor.h>


static void init_Sensor(Sensor *this_, const char * p_id, const char * p_name)
{
	this_->n_speed = 0;
	this_->oocAgent.p_id = oocString_new(__FILE__, __LINE__);
	this_->oocAgent.p_id->init(this_->oocAgent.p_id, p_id);

	this_->oocAgent.p_name = oocString_new(__FILE__, __LINE__);
	this_->oocAgent.p_name->init(this_->oocAgent.p_name, p_name);
}

static oocString * get_sensor_id(Sensor * this_)
{
	return this_->oocAgent.p_id;
}

static oocString * get_sensor_name(Sensor * this_)
{
	return this_->oocAgent.p_name;
}

static void set_sensor_speed(Sensor * this_, int32_t n_speed)
{
	this_->n_speed = n_speed;
}

static int32_t get_sensor_speed(Sensor * this_)
{
	return this_->n_speed;
}

CTOR(Sensor)
	SUPER_CTOR(oocAgent);
	FUNCTION_BIND(get_ID, get_sensor_id);
	FUNCTION_BIND(get_Name, get_sensor_name);
	FUNCTION_BIND(get_Speed, get_sensor_speed);
	FUNCTION_BIND(set_Speed, set_sensor_speed);
	FUNCTION_BIND(init, init_Sensor);END_CTOR

DTOR(Sensor)
	SUPER_DTOR(oocAgent);END_DTOR

/*** end of file ***/
