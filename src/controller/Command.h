#pragma once

class Command
{
public:
	virtual void doCommand () = 0;
	virtual void undoCommand () = 0;
};