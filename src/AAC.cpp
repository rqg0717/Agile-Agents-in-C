//============================================================================
// Name        : AAC.cpp
// Author      : James Ren
// Version     :
// Copyright   : (c) 2017 James Ren. All rights reserved.
// Description : agile agents in C
//============================================================================


#include <oocString.h>
#include <Sensor.h>
//#include <sys/time.h>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

#define BILLION 1E9

class  cppObject
{
protected:
	int n_count;

public:
	cppObject()
	{
		this->n_count = 0;
	}

	virtual ~cppObject()
	{
		cout << "cppObject is being deleted" << endl;
	}

	int getCount()
	{
		return this->n_count;
	}

	void setCount(int count)
	{
		this->n_count = count;
	}

	virtual void finalize()=0;

};

class  cppAgent : public cppObject
{
protected:
	string *p_strName;
	string *p_strID;

public:
	cppAgent(string name, string id)
	{
		this->p_strName = new string(name);
		this->p_strID = new string(id);

	}

	~cppAgent()
	{
		finalize();
	}

	string getName()
	{
		string str = this->p_strName->c_str();
		return str;
	}

	void setName(string name)
	{
		this->p_strName->assign(name);
	}

	void finalize()
	{
		if(p_strName)
		{
			delete p_strName;
			p_strName = NULL;
		}

		if(p_strID)
		{
			delete p_strID;
			p_strID = NULL;
		}

		cout << "cppAgent is being deleted" << endl;
	}
};

class  cppSensor : public cppAgent
{
protected:
	int n_speed;

public:
	cppSensor(string name, string id):cppAgent(name, id)
	{
		n_speed = 0;
	}

	int getSpeed()
	{
		return this->n_speed;
	}

	void setSpeed(int speed)
	{
		this->n_speed = speed;
	}
};

string* ltrim(string* str, const string& chars = "\t\n\v\f\r ")
{
    str->erase(0, str->find_first_not_of(chars));
    return str;
}

string* rtrim(string* str, const string& chars = "\t\n\v\f\r ")
{
    str->erase(str->find_last_not_of(chars) + 1);
    return str;
}

string* trim(string* str, const string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

int main()
{
	//struct timeval start, end;
	struct timespec ts_start, ts_end;

	printf("\======================= C++ performance test ======================\r\n\n");
	clock_gettime(CLOCK_REALTIME, &ts_start);
	/////////////////////////////////////////
	//on heap
	string *p_string, *p_substring, *p_strName;
	cppSensor *p_cppSensor;

	p_string = new string("  agent rocks rock agents  ");
	trim(p_string);

	cout << p_string->c_str() << endl;

	p_substring = new string(p_string->substr(6, 5));


	cout << p_substring->c_str() << endl;

	cout << p_string->find("rocks") << endl;

	cout << p_string->rfind("rock") << endl;

	p_cppSensor = new cppSensor(" speed sensor ", "002");

	p_cppSensor->setSpeed(120);
	p_cppSensor->setName("speed sensor 2");

	p_strName = new string(p_cppSensor->getName());
	trim(p_strName);

	cout << "Sensor name is " << p_strName->c_str() <<  " and current speed is " << p_cppSensor->getSpeed() << endl;

	delete p_string;
	p_string = NULL;
	delete p_substring;
	p_substring = NULL;
	delete p_strName;
	p_strName = NULL;
	delete p_cppSensor;
	p_cppSensor = NULL;

	//////////////////////////////////////
	clock_gettime(CLOCK_REALTIME, &ts_end);

	printf("C++ time elapsed in second: %lf\n\n", ( ts_end.tv_sec - ts_start.tv_sec ) + ( ts_end.tv_nsec - ts_start.tv_nsec )
			  / BILLION);

	printf("\======================= C performance test ======================\r\n\n");
	//gettimeofday(&start, NULL);
	clock_gettime(CLOCK_REALTIME, &ts_start);
	///////////////////////////////
	oocString *p_str, *p_substr;
	Sensor *p_sensor = NULL;
	oocString *p_name = NULL;

	/* test String on heap*/
	p_str = oocString_new(__FILE__, __LINE__);
	p_str->init(p_str, "  agent rocks rock agents  ");

	p_str->trim(p_str);
	p_str->print(p_str);

	p_substr = p_str->substr(p_str, 6, 5);
	p_substr->print(p_substr);

	printf("%d\r\n", p_str->find(p_str, "rocks"));

	printf("%d\r\n", p_str->rfind(p_str, "rock"));

	oocString_delete(p_substr);
	oocString_delete(p_str);

	//check_mem_leak();

	/* test Polymorphism, Encapsulation, Inheritance on heap*/
	p_sensor = Sensor_new(__FILE__, __LINE__);

	p_sensor->init(p_sensor, "001", " speed sensor ");

	p_sensor->setSpeed(p_sensor, 120);
	p_name = p_sensor->getName(p_sensor);
	p_name->trim(p_name);

	printf("Sensor name is %s and current speed is %d \r\n", p_name->c_str(p_name), p_sensor->getSpeed(p_sensor));

	//Polymorphism
	/*IAction *p_action;

	p_action = SUPER_PTR(p_sensor, IAction);
	p_action->action(p_action);

	oocAgent *p_agent;
	p_agent = oocAgent_new(__FILE__, __LINE__);
	p_action = SUPER_PTR(p_agent, IAction);
	p_action->action(p_action);

	oocAgent_delete(p_agent);*/
	Sensor_delete(p_sensor);

	//check_mem_leak();
	///////////////////////////
	//gettimeofday(&end, NULL);
	//printf("C: %ld\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

	clock_gettime(CLOCK_REALTIME, &ts_end);
	printf("C time elapsed in second: %lf \n\n", ( ts_end.tv_sec - ts_start.tv_sec ) + ( ts_end.tv_nsec - ts_start.tv_nsec )
			  / BILLION);

	printf("\======================= End of test ======================\r\n");

	return 0;
}
