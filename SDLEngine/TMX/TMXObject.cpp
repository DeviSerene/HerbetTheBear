#include "TMXObject.h"



TMXObject::TMXObject(int x, int y, int width, int height, int id, std::string type, TMX_OBJECT_SHAPES shape)
	:x(x), y(y), width(width), height(height), id(id), type(type), shape(shape)
{

}


TMXObject::~TMXObject()
{
}
