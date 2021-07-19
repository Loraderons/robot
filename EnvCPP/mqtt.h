// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "mosquitto.h"
#include "mosquittopp.h"

class mqtt : public mosqpp::mosquittopp
{
private:
	const char* host;
	const char* id;
	const char* topic;
	int port;
	int keepalive;
	void on_message(const struct mosquitto_message* message);
public:
	char* lastMsg;
	mqtt(const char* _id, const char* _topic, const char* _host, int port);
	~mqtt();
};
