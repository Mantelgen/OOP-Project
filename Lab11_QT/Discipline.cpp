#include "Discipline.h"

string Discipline::setName(const string& newName) noexcept {
	this->name = newName;
	return this->name;
}
string Discipline::setTeacher(const string& newTeacher) noexcept {
	this->teacher = newTeacher;
	return this->teacher;
};
string Discipline::setType(const string& newType) noexcept {
	this->type = newType;
	return this->type;
};
unsigned int Discipline::setNumClasses(const unsigned int newNumClassess) noexcept {
	this->numClasses = newNumClassess;
	return this->numClasses;
};
Discipline& Discipline::operator =(const Discipline& d) {
	this->name = d.name;
	this->numClasses = d.numClasses;
	this->teacher = d.teacher;
	this->type = d.type;
	return *this;
}
bool Discipline::operator ==(const Discipline& d) const noexcept {
	return name == d.getName() && teacher == d.getTeacher() && type == d.getType() && numClasses == d.getNumClasses();
};
bool Discipline::operator !=(const Discipline& d) const noexcept {
	return !(*this == d);
};
