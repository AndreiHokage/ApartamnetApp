#include "UndoAction.h"

void UndoAdauga::doUndo() {
	repo.delete_locatar(locatar.get_apart());
}

void UndoSterge::doUndo() {
	repo.add_locatar(locatar);
}

void UndoModifica::doUndo(){
	repo.update_locatar(locatar);
}