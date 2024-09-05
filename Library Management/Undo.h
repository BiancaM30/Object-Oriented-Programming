#pragma once
#include "Book.h"
#include "AbstractRepo.h"

class Undo {
public:
	virtual void doUndo() = 0;
	virtual void doRedo() = 0;
	virtual ~Undo() = default;
};

class UndoAdd : public Undo {
private:
	Book b;
	Repo& repo;

public:
	UndoAdd(Repo& repo, const Book& b) : repo{ repo }, b{ b }{}

	void doUndo() override {
		repo.remove(b.getTitle(), b.getAuthor());
	}

	void doRedo() override {
		repo.store(b);
	}
};

class UndoDelete : public Undo {
private:
	Book b;
	Repo& repo;

public:
	UndoDelete(Repo& repo, const Book& b) : repo{ repo }, b{ b }{}

	void doUndo() override {
		repo.store(b);
	}

	void doRedo() override {
		repo.remove(b.getTitle(), b.getAuthor());
	}
};

class UndoUpdate :public Undo {
private:
	Book b;
	Repo& repo;

	string prev_genre, new_genre;
	int prev_year, new_year;

public:
	UndoUpdate(Repo& rep, Book& b, string new_genre, int new_year) : repo{ rep }, b{ b }, prev_genre{ b.getGenre() }, prev_year{ b.getYear() }, new_genre{ new_genre }, new_year{ new_year }{};

	void doUndo() override {
		repo.update(b.getTitle(), b.getAuthor(), prev_genre, prev_year);
	}

	void doRedo()override {
		repo.update(b.getTitle(), b.getAuthor(), new_genre, new_year);
	}
};


