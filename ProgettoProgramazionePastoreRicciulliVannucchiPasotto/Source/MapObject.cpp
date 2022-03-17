#include "MapObject.hpp"



void Object::ChangeAppearance() {
	switch (type)
	{
	case air:
		this->appearance = ' ';
		break;
	case wall:
		this->appearance = char(219);  // questo carattere è il blocchetto colorato
		break;
	case gas:
		this->appearance = 'G';
		break;
	case obstacle:
		this->appearance = 'X';
		break;
	case pit:
		this->appearance = 'U';
		break;
	case nails:
		this->appearance = '^';
		break;
	default:
		break;
	}
}

Object::Object() {

	this->type = air;
	this->appearance = ' ';
}

Object::Object(ObjectType x) {
	this->type = x;
	switch (type)
	{
	case air:
		this->appearance = ' ';
		break;
	case wall:
		this->appearance = char(219);
		break;
	case gas:
		this->appearance = 'G';
		break;
	case obstacle:
		this->appearance = 'X';
		break;
	case pit:
		this->appearance = 'U';
		break;
	case nails:
		this->appearance = '^';
		break;
	default:
		break;
	}
}

ObjectType Object::GetType() {
	return this->type;
}

void Object::PrintAppearance() {
	cout << appearance;
}

void Object::ChangeType(ObjectType new_ob) {
	this->type = new_ob;
	ChangeAppearance();
}

char Object::GetAppearance() {
	return this->appearance;
}