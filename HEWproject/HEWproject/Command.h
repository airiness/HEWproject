#pragma once
#include"GameObject.h"
class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameObject& actor) = 0;
};

class upCommand : public Command
{
public:
	virtual void execute(GameObject& actor)
	{
		actor.up();
	}
};

class downCommand : public Command
{
public:
	virtual void execute(GameObject& actor)
	{
		actor.down();
	}
};

class leftCommand : public Command
{
public:
	virtual void execute(GameObject& actor)
	{
		actor.left();
	}
};

class rightCommand : public Command
{
public:
	virtual void execute(GameObject& actor)
	{
		actor.right();
	}
};