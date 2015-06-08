#pragma once
#include "GObject.h"
class GGroup :
	public GObject
{
public:
	GGroup();
	virtual ~GGroup();
	CUIntArray group;
};

