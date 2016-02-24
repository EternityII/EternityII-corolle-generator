#include "Jeu.h"

Jeu::Jeu(int sizeJeu){

	//Initialize Variables
	this->size = sizeJeu;
	this->jeu = new Piece[this->size];
	this->TabC = new Piece[4];
	this->TabB = new Piece[(this->size-2)*4];

	int size_of_tab_I = pow(this->size-2,2);

	this->TabI = new Piece[size_of_tab_I];
	this->nb_pieces_presentes = 0;

}

int Jeu::addPiece(Piece p){

	if(this->nb_pieces_presentes < pow(this->size,2)){
		this->jeu[this->nb_pieces_presentes] = p;
		this->nb_pieces_presentes++;
	}

}

// Getters 
int Jeu::getSize(){
	return this->size;
}
Piece* Jeu::getJeu(){
	return this->jeu;
}
Piece* Jeu::getTabC(){
	return this->TabC;
}
Piece* Jeu::getTabB(){
	return this->TabB;
}
Piece* Jeu::getTabI(){
	return this->TabI;
}


