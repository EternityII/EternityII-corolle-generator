#include "File_In.h"

File_In::File_In(int taille){

	this->size = taille;

	string extention = ".txt";

	ostringstream s;
	s << "Pieces_";
	s << taille;
	s << "x";
	s << taille;
	s << extention;

	this->pathFile  = s.str();

}

	void File_In::InitJeu(){


		Jeu jeu (this->size);

		string stringPiece;

		int id = 0;

		int nbLignesLus = 0;
		int startPiece = 4;

		//Ouverture du fichier
		in_file.open(this->pathFile.c_str(),ifstream::in);


		int * couleur = new int[4];
		int color;

		string str; // 4 premieres lignes
		for (int i = 0; i < 4; ++i)
		{
			in_file >> str;
		}


		for (int i=0;i<(size*size);i++){
			for(int j=0;j<4;j++){
				in_file >> color;
				couleur[i] = color;
			}

			Piece p(id,couleur);
			cout << p.toString() << endl;
			id++;
		}
	}


int main(){
	File_In in(4);
	in.InitJeu();
}
