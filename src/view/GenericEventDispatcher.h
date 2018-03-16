#pragma once

#include "src\controller\Controller.h"
#include "GenericViewer.h"

class GenericEventDispatcher
{
public:
	GenericEventDispatcher (Controller* controller, GenericViewer* viewer) :
		m_controller (controller),
		m_viewer(viewer) {}


protected:
	Controller* m_controller;
	GenericViewer* m_viewer;

};