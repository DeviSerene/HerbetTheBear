#define _CRT_SECURE_NO_WARNINGS
#include "TMXMap.h"

#include <string.h>

using namespace tinyxml2;

TMXMap::TMXMap(const char *workingDir, const char *fileName)
{
	char filePath[128] = "";
	strcat(filePath, workingDir);
	strcat(filePath, fileName);
	XMLDocument doc;
	doc.LoadFile(filePath);
	if (doc.Error())
		throw std::exception("Could not load/parse TMX file");

	XMLElement *mapElement = doc.FirstChildElement("map");
	mapElement->QueryIntAttribute("width", &width);
	mapElement->QueryIntAttribute("width", &height);
	mapElement->QueryIntAttribute("tilewidth", &tileWidth);
	mapElement->QueryIntAttribute("tileheight", &tileHeight);

	XMLElement *ts = mapElement->FirstChildElement("tileset");
	while (ts != NULL) {
		int tsWidth = 0, tsHeight = 0, tsCount = 0, tsFirst = 0;
		std::string tsFileName, tsName;
		char tsFile[128] = "";
		ts->QueryIntAttribute("tilewidth", &tsWidth);
		ts->QueryIntAttribute("tileheight", &tsHeight);
		ts->QueryIntAttribute("tilecount", &tsCount);
		ts->QueryIntAttribute("firstgid", &tsFirst);
		tsName = ts->Attribute("name");
		if (ts->FirstChildElement("image") != NULL)
			tsFileName = ts->FirstChildElement("image")->Attribute("source");
		else
			tsFileName = "";
		strcat(tsFile, workingDir);
		strcat(tsFile, tsFileName.c_str());
		tileSets.push_back(new TMXTileSet(tsWidth, tsHeight, tsCount, tsFirst, tsName.c_str(), tsFile));
		ts = ts->NextSiblingElement("tileset");
	}

	XMLElement *layer = mapElement->FirstChildElement("layer");
	while (layer != NULL) {
		int lWidth = 0, lHeight = 0;
		char lName[128];
		const char *lData;
		layer->QueryIntAttribute("width", &lWidth);
		layer->QueryIntAttribute("height", &lHeight);
		strcpy(lName, layer->Attribute("name"));
		XMLElement *data = layer->FirstChildElement("data");
		XMLText *child = (XMLText*)data->FirstChild();
		lData = child->Value();
		TMXLayer *l = new TMXLayer(lWidth, lHeight, lName, lData);
		layers.push_back(l);
		XMLElement *p = layer->FirstChildElement("properties");
		if (p != NULL)
			p = p->FirstChildElement("property");
		while (p != NULL) {
			char type[128];
			std::string name = p->Attribute("name");
			strcpy(type, p->Attribute("type"));
			if (!strcmp(type, "int")) {
				int val;
				p->QueryIntAttribute("value", &val);
				l->intProperties[name] = val;
			}
			else if (!strcmp(type, "string")) {
				const char *val = p->Attribute("value");
				l->stringProperties[name] = val;
			}
			else if (!strcmp(type, "float")) {
				float val;
				p->QueryFloatAttribute("value", &val);
				l->floatProperties[name] = val;
			}
			else if (!strcmp(type, "bool")) {
				bool val;
				p->QueryBoolAttribute("value", &val);
				l->boolProperties[name] = val;
			}
			p = p->NextSiblingElement("property");
		}
		layer = layer->NextSiblingElement("layer");
	}

	XMLElement *group = mapElement->FirstChildElement("objectgroup");
	while (group != NULL) {
		char gName[128];
		strcpy(gName, group->Attribute("name"));
		TMXObjectGroup *og = new TMXObjectGroup(gName);
		objectGroups.push_back(og);
		XMLElement *o = group->FirstChildElement("object");
		while (o != NULL) {
			int oId, oX, oY, oWidth, oHeight;
			TMX_OBJECT_SHAPES shape = TMX_RECTANGLE;
			std::string oType;
			std::string oName;
			oName = o->Attribute("name");
			o->QueryIntAttribute("id", &oId);
			o->QueryIntAttribute("x", &oX);
			o->QueryIntAttribute("y", &oY);
			o->QueryIntAttribute("width", &oWidth);
			o->QueryIntAttribute("height", &oHeight);
			oType = o->Attribute("type") != NULL ? o->Attribute("type") : "";
			if (!o->NoChildren())
				if(o->FirstChildElement("ellipse") != NULL)
					shape = TMX_ELLIPSE;
			TMXObject *ob = new TMXObject(oName, oX, oY, oWidth, oHeight, oId, oType, shape);
			og->objects.push_back(ob);
			XMLElement *p = o->FirstChildElement("properties");
			if (p != NULL)
				p = p->FirstChildElement("property");
			while (p != NULL) {
				char type[128];
				std::string name = p->Attribute("name");
				strcpy(type, p->Attribute("type"));
				if (!strcmp(type, "int")) {
					int val;
					p->QueryIntAttribute("value", &val);
					ob->intProperties[name.c_str()] = val;
				}
				else if (!strcmp(type, "string")) {
					const char *val = p->Attribute("value");
					ob->stringProperties[name.c_str()] = val;
				}
				else if (!strcmp(type, "float")) {
					float val;
					p->QueryFloatAttribute("value", &val);
					ob->floatProperties[name.c_str()] = val;
				}
				else if (!strcmp(type, "bool")) {
					bool val;
					p->QueryBoolAttribute("value", &val);
					ob->boolProperties[name.c_str()] = val;
				}
				p = p->NextSiblingElement("property");
			}
			o = o->NextSiblingElement("object");
		}
		group = group->NextSiblingElement("objectgroup");
	}
}


TMXMap::~TMXMap()
{
}
