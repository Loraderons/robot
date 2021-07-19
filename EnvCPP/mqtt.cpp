// Fill out your copyright notice in the Description page of Project Settings.

#include <cstdio>
#include <cstring>
#include <cmath>
#include "mqtt.h"


mqtt::mqtt(const char* _id, const char* _topic, const char* _host, int _port) : mosquittopp(_id){
	mosqpp::lib_init();        
	this->keepalive = 60;
	this->id = _id;
	this->port = _port;
	this->host = _host;
	this->topic = _topic;
	this->lastMsg = "0";
	connect_async(host, port, keepalive);
	subscribe(NULL, this->topic, 1);
	loop_start();           
};

mqtt::~mqtt() {
	loop_stop();            
	mosqpp::lib_cleanup();   
}

void mqtt::on_message(const struct mosquitto_message* message){
	if (abs(atof(this->lastMsg) - atof(static_cast<char*>(message->payload))) > 0.5)
		this->lastMsg = static_cast<char*>(message->payload);
}