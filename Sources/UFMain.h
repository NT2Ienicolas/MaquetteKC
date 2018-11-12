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
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "UFonctionsKC.h"
//---------------------------------------------------------------------------
class TFMain : public TForm
{
__published:	// Composants gérés par l'EDI
	TButton *bCarousel;
	TButton *bInitRotation;
	TButton *bDoRotation;
	TSpinEdit *seAngleRotation;
	TLabel *Label6;
	TLabel *Label7;
	TSpinEdit *seRotationX;
	TSpinEdit *seRotationY;
	TLabel *Label8;
	TTimer *tInfoBulle;
	TPanel *pInfoBulle;
	TMemo *mBulleInfo;
	TCheckBox *cbNumObj;
	TComboBox *cbCass0;
	TComboBox *cbCass1;
	TComboBox *cbCass2;
	TComboBox *cbCass3;
	TComboBox *cbCass4;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TButton *bInitScan;
	TButton *bPrevCassette;
	TButton *bNextCassette;
	TLabel *lblDeltaCassette;
	TMemo *mTodo;
	TButton *bColor;
	void __fastcall bCarouselClick(TObject *Sender);
	void __fastcall bInitRotationClick(TObject *Sender);
	void __fastcall bDoRotationClick(TObject *Sender);
	void __fastcall imgMyClick(TObject *Sender);
	void __fastcall imgMyMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall imgMyMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall tInfoBulleTimer(TObject *Sender);
	void __fastcall bInitScanClick(TObject *Sender);
	void __fastcall bPrevCassetteClick(TObject *Sender);
	void __fastcall bNextCassetteClick(TObject *Sender);
private:	// Déclarations utilisateur
	int xMouseDown;
	int yMouseDown;
	int iOffsetK7;
	int iK7Type[iNbK7]; //-1 : absent; 0 : reactif; 2 conso
	void SetInfoBulle(int iTypeObj, int iIndObj);
	void MaskInfoBulle();
	void DeplaceCassette(int iMouv);
public:		// Déclarations utilisateur
	__fastcall TFMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------
#endif
