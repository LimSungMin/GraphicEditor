#pragma once
#include "GObject.h"
class GGroup :
	public GObject
{
public:
	GGroup();
	virtual ~GGroup();
	CUIntArray group;
	CArray<GObject, GObject&> m_group;
	UINT m_index;
	BOOL m_isUsing;
};

