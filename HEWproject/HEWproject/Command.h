#pragma once
#include"GameObject.h"
class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameObject& actor) = 0;
};

class jumpCommand : public Command
{
public:
	virtual void execute(GameObject& actor)
	{
		actor.jump();
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