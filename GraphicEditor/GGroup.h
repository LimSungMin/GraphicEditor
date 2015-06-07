#pragma once
#include "GObject.h"
class GGroup :
	public GObject
{
public:
	GGroup();
	virtual ~GGroup();
	CList<GObject, GObject&> m_group;
};

