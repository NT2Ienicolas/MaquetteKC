/**
 * \file UFMain.h
 * \brief Maquette du carrousel Kryptor Compact.
 * \author E.N.
 * \version 0.1
 * \date 09/11/2018
 *
 * Maquette pour les fonctions d'afficher et de gestion
 * du carrousel du Kryptor Compact
 *
 */

#ifndef UFMainH
#define UFMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFMain : public TForm
{
__published:	// Composants gérés par l'EDI
	TButton *bCarousel;
	void __fastcall bCarouselClick(TObject *Sender);
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TFMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------
#endif
