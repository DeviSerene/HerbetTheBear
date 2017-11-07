#include "TMXObject.h"



TMXObject::TMXObject(std::string name, int x, int y, int width, int height, int id, std::string type, TMX_OBJECT_SHAPES shape)
	:name(name), x(x), y(y), width(width), height(height), id(id), type(type), shape(shape)
{

}


TMXObject::~TMXObject()
{
}
