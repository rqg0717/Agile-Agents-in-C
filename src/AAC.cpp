//============================================================================
// Name        : AAC.cpp
// Author      : James Ren
// Version     :
// Copyright   : (c) 2017 James Ren. All rights reserved.
// Description : agile agents in C
//============================================================================

#include "oocString.h"
#include "Sensor.h"


int main()
{
	oocString *p_str, *p_substr;
	Sensor *p_sensor = NULL;
	oocString *p_name = NULL;
	/*test String*/
	p_str = oocString_new(__FILE__, __LINE__);
	p_str->init(p_str, "  agent rocks    rock agents  ");
	p_str->trim(p_str);
	p_str->print(p_str);
	p_substr = p_str->substr(p_str, 6, 5);
	p_substr->print(p_substr);

	printf("%d\r\n", p_str->find(p_str, "rocks"));

	printf("%d\r\n", p_str->rfind(p_str, "rock"));

	oocString_delete(p_substr);
	oocString_delete(p_str);

	check_mem_leak();

	/*test Polymorphism, Encapsulation, Inheritance */
	p_sensor = Sensor_new(__FILE__, __LINE__);

	p_sensor->init(p_sensor, "001", " speed sensor ");

	p_sensor->set_Speed(p_sensor, 120);
	p_name = p_sensor->get_Name(p_sensor);
	p_name->trim(p_name);

	printf("Sensor name is %s and current speed is %d \r\n", p_name->c_str(p_name), p_sensor->get_Speed(p_sensor));

	Sensor_delete(p_sensor);

	check_mem_leak();

	return 0;
}
