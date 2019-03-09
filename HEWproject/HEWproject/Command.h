/*
author:zhang ruisong
date:2019.3.7
class command 
*/
#pragma once
#include"GameActor.h"
class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameActor& actor) = 0;
};

class upCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.up();
	}
};

class downCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.down();
	}
};

class leftCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.left();
	}
};

class rightCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.right();
	}
};

class shootCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.shoot();
	}
};

class powerCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.plusPower();
	}
};