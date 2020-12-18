#pragma once

class TypeID
{
protected:
	static int typeID;
public:
	template<typename C>
	static int getID()
	{
		static int ID = typeID++;
		return ID;
	}
};