//---------------------------------------------------------------------------

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
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TFMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------
#endif
