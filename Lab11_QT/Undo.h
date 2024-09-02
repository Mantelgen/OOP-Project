#pragma once
#include "Discipline.h"
#include "Repository.h"
#include <functional>

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd :public UndoAction {
private:
	Discipline dsp;
	AbstractRepository* repo;
public:
	UndoAdd(AbstractRepository* repo, const Discipline& dsp) : dsp{ dsp }, repo{ repo } {};
	void doUndo() override {
		repo->deleteDiscipline(dsp.getName());
	};
};
class UndoDelete :public UndoAction {
private:
	Discipline dsp;
	AbstractRepository* repo;
public:
	UndoDelete(AbstractRepository* repo, const Discipline& dsp) :dsp{ dsp }, repo{ repo } {};
	void doUndo() override {
		repo->addDiscipline(dsp);
	};
};
class UndoUpdate :public UndoAction {
private:
	Discipline dsp;
	AbstractRepository* repo;
public:
	UndoUpdate(AbstractRepository* repo, const Discipline& dsp) : dsp{ dsp }, repo{ repo } {};
	void doUndo() override {
		repo->updateDiscipline(dsp);
	};
};