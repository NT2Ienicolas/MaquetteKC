/**
 * \file UFMain.c
 * \brief Maquette du carrousel Kryptor Compact.
 * \author E.N.
 * \version 0.1
 * \date 09/11/2018
 *
 * Maquette pour les fonctions d'afficher et de gestion
 * du carrousel du Kryptor Compact
 *
 */

//Modification du fichier pour le commit et remodifier pour le pull request


#include <vcl.h>
#pragma hdrstop

#include "UFMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFMain *FMain;

/**
 * \fn __fastcall TFMain::TFMain(TComponent* Owner)
 * \brief Constructeur de l'écran principal
 *
 * \param Owner
 * \return .
 */
__fastcall TFMain::TFMain(TComponent* Owner)
	: TForm(Owner)
{
	xMouseDown = -1;
	yMouseDown = -1;
	SetOffsetK7(0);
	for (int i = 0; i < iNbK7; i++)
		iK7Type[i] = -1;
}

/**
 * \fn __fastcall TFMain::bCarouselClick(TObject *Sender)
 * \brief Evénement OnClick du bouton "Carousel"
 *
 * \param Sender
 * \return .
 *
 *	Crée une image est dessine le carousel sur son canvas.
 */
void __fastcall TFMain::bCarouselClick(TObject *Sender)
{
	Screen->Cursor = crHourGlass;

	if (FindComponent(L"imgRotation") == NULL)
		bInitRotation->Click();

	TImage *imgSrc = dynamic_cast<TImage*>(FindComponent(L"imgRotation"));

	if (FindComponent(L"imgDestination") == NULL) {
		TImage *imgDestination = new TImage(this);
		imgDestination->Name = L"imgDestination";
		imgDestination->Parent = FMain;
		imgDestination->Visible = true;
		imgDestination->Width = 750;
		imgDestination->Height = 750;
		imgDestination->Left = 0;
		imgDestination->Top = 0;
		imgDestination->OnClick = imgMyClick;
		imgDestination->OnMouseDown = imgMyMouseDown;
		imgDestination->OnMouseUp = imgMyMouseUp;
	}
	TImage *imgDest = dynamic_cast<TImage*>(FindComponent(L"imgDestination"));

	int RayonExt = RayonExtK7;
	int RayonInt = RayonIntK7;
	int RayonCentreRgt = (RayonExt + RayonInt) / 2;
	int RayonTube = (RayonExt + RayonInt) / 2;
	int RayonCentreTube = (RayonExt + RayonTube) / 2;
	int RayonCentreTubeExt = (RayonExt + RayonCentreTube) / 2;
	int RayonCentreTubeInt = (RayonCentreTube + RayonTube) / 2;
	int RayonCentreConso = (RayonTube + RayonInt) / 2;

	int iRayonT = TubeWidth / 2;
	int iRayonB = BottleWidth / 2;
	int iDilWidth = (RayonTube - RayonInt) / 2;
	int Xcentre = imgDest->Width / 2;
	int Ycentre = imgDest->Height / 2;

	//Cercle extérieur
	imgDest->Canvas->Ellipse(Xcentre - RayonExt, Ycentre - RayonExt,
								Xcentre + RayonExt, Ycentre + RayonExt);
	//!Cercle extérieur

	//Cercle Consommables
	/*
	imgDest->Canvas->Ellipse(Xcentre - RayonTube, Ycentre - RayonTube,
								Xcentre + RayonTube, Ycentre + RayonTube);
	*/
	//!Cercle Consommables

	//Cassettes
	double dDelta = - Pi / 2; //Retour pour commencer "en haut"
	for (int i = 0; i < iNbK7; i++)
	{
		int iK7 = i + GetOffsetK7();
		double Angle = (((double)(iK7/* + 0.5*/) * GetAngleObject(3)) + dDelta);

		int X = (int)((double)Xcentre + (RayonExt * cos(Angle)));
		int Y = (int)((double)Ycentre + (RayonExt * sin(Angle)));
		imgDest->Canvas->MoveTo(X, Y);
		X = (int)((double)Xcentre + (RayonInt * cos(Angle)));
		Y = (int)((double)Ycentre + (RayonInt * sin(Angle)));
		imgDest->Canvas->LineTo(X, Y);

		//Etiquette
		if (cbNumObj->Checked) {
			X = (int)((double)Xcentre + ((RayonInt + RayonExt) / 2 * cos(Angle)));
			Y = (int)((double)Ycentre + ((RayonInt + RayonExt) / 2 * sin(Angle)));
			imgDest->Canvas->TextOutW(X, Y, IntToStr(i));
		}
	}
	//!Cassettes

	//Reactifs
	double dAngleReactif = (double)((1.0 / (double)(iNbK7 * iNbReagent)) * 2 * Pi);
	for (int i = 0; i < iNbK7; i++) {
		int iK7 = (i + GetOffsetK7()) % iNbK7;
		if (iK7Type[i] == 0) {
			for (int j = 0; j < iNbReagent; j++) {
				double dAngle = (double)((double)((iK7 * iNbReagent) + j + 0.5) * dAngleReactif) + dDelta;

				int X = (int)((double)Xcentre + (RayonCentreRgt  * cos(dAngle)));
				int Y = (int)((double)Ycentre + (RayonCentreRgt * sin(dAngle)));
				imgDest->Canvas->Pixels[X][Y] = clRed;

				X = X - (imgSrc->Width / 2);
				Y = Y - (imgSrc->Height / 2);
				dAngle = dAngle - (Pi / 2);
				Rotation(dAngle, imgSrc, imgDest, X, Y);

				//Etiquette
				if (cbNumObj->Checked) {
					X = X + (imgSrc->Width / 2);
					Y = Y + (imgSrc->Height / 2);
					imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
				}
			}
		}
	}
	//!Reactifs

	//Tubes
	double dAngletubeInt = (double)((1.0 / (double)(iNbK7 * iNbTubeK7Int)) * 2 * Pi);
	double dAngletubeExt = (double)((1.0 / (double)(iNbK7 * iNbTubeK7Ext)) * 2 * Pi);
	for (int i = 0; i < iNbK7; i++) {
		int iK7 = (i + GetOffsetK7()) % iNbK7;
		if (iK7Type[i] == 1) {
			for (int j = 0; j < iNbTubeK7Int; j++) {
				double dAngle = (double)((double)((iK7 * iNbTubeK7Int) + j + 0.5) * dAngletubeInt) + dDelta;

				int X = (int)((double)Xcentre + (RayonCentreTubeInt  * cos(dAngle)));// + iRayonB;
				int Y = (int)((double)Ycentre + (RayonCentreTubeInt * sin(dAngle)));// + iRayonB;
				imgDest->Canvas->Pixels[X][Y] = clBlue;
				imgDest->Canvas->Ellipse(X - iRayonT, Y - iRayonT, X + iRayonT, Y + iRayonT);

				//Etiquette
				if (cbNumObj->Checked)
					imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
			}

			for (int j = 0; j < iNbTubeK7Ext; j++) {
				double dAngle = (double)((double)((iK7 * iNbTubeK7Ext) + j + 0.5) * dAngletubeExt) + dDelta;

				int X = (int)((double)Xcentre + (RayonCentreTubeExt  * cos(dAngle)));// + iRayonB;
				int Y = (int)((double)Ycentre + (RayonCentreTubeExt * sin(dAngle)));// + iRayonB;
				imgDest->Canvas->Pixels[X][Y] = clBlue;
				imgDest->Canvas->Ellipse(X - iRayonT, Y - iRayonT, X + iRayonT, Y + iRayonT);

				//Etiquette
				if (cbNumObj->Checked)
					imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
			}
		}
	}
	//!Tubes

	//Bouteilles
	double dAngleBouteille = (double)((1.0 / (double)(iNbK7 * iNbBottle)) * 2 * Pi);
	for (int i = 0; i < iNbK7; i++) {
		int iK7 = (i + GetOffsetK7()) % iNbK7;
		if (iK7Type[i] == 1) {
			for (int j = 0; j < iNbBottle; j++) {
				double dAngle = (double)((double)((iK7 * iNbBottle) + j + 0.5) * dAngleBouteille) + dDelta;

				int X = (int)((double)Xcentre + (RayonCentreConso  * cos(dAngle)));// + iRayonB;
				int Y = (int)((double)Ycentre + (RayonCentreConso * sin(dAngle)));// + iRayonB;
				imgDest->Canvas->Pixels[X][Y] = clBlue;
				imgDest->Canvas->Ellipse(X - iRayonB, Y - iRayonB, X + iRayonB, Y + iRayonB);

				//Etiquette
				if (cbNumObj->Checked)
					imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
			}
		}
	}
	//!Bouteilles

	//Plaques de dilution
	int RayonDilExt = RayonCentreConso + iDilWidth + 5;
	int RayonDilInt = RayonCentreConso - iDilWidth - 5;
	//int RayonDilIntBis = RayonDilInt;
	int iTotDil = iNbDil * iNbK7;
	for (int i = 0; i < iTotDil; i++)
	{
		int iK7 = (i / 2 + GetOffsetK7()) % iNbK7;
		if (iK7Type[i / 2] == 1) {
			int iDil = iK7 * 2 + (i % 2);
			double dAngleStart = (((double)(iDil+0.02 ) * GetAngleObject(4))) + dDelta;

			int X1 = (int)((double)Xcentre + (RayonDilExt * cos(dAngleStart)));
			int Y1 = (int)((double)Ycentre + (RayonDilExt * sin(dAngleStart)));
			int X4 = (int)((double)Xcentre + (RayonDilInt * cos(dAngleStart)));
			int Y4 = (int)((double)Ycentre + (RayonDilInt * sin(dAngleStart)));

			double dAngleStop = (((double)(iDil+0.98 ) * GetAngleObject(4))) + dDelta;
			int X3 = (int)((double)Xcentre + (RayonDilExt * cos(dAngleStop)));
			int Y3 = (int)((double)Ycentre + (RayonDilExt * sin(dAngleStop)));
			int X2 = (int)((double)Xcentre + (RayonDilInt * cos(dAngleStop)));
			int Y2 = (int)((double)Ycentre + (RayonDilInt * sin(dAngleStop)));

			imgDest->Canvas->MoveTo(X2, Y2);
			imgDest->Canvas->LineTo(X3, Y3);

			imgDest->Canvas->MoveTo(X4, Y4);
			imgDest->Canvas->LineTo(X1, Y1);

			for (double d = dAngleStart; d <= dAngleStop; d = d + 0.001) {
				int x = Xcentre + (RayonDilExt * cos(d));
				int y = Ycentre + (RayonDilExt * sin(d));
				imgDest->Canvas->Pixels[x][y] = clBlack;
				x = Xcentre + (RayonDilInt * cos(d));
				y = Ycentre + (RayonDilInt * sin(d));
				imgDest->Canvas->Pixels[x][y] = clBlack;
			}
		}
	}
	imgDest->Canvas->Pen->Color = clBlack;
	//!Plaques de dilution

	//Cercle intérieur
	imgDest->Canvas->Ellipse(Xcentre - RayonInt, Ycentre - RayonInt,
								Xcentre + RayonInt, Ycentre + RayonInt);
	//!Cercle intérieur

	Screen->Cursor = crDefault;
}

/**
 * \fn void __fastcall TFMain::bInitRotationClick(TObject *Sender)
 * \brief Evénement OnClick du bouton "Init Rotation"
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::bInitRotationClick(TObject *Sender)
{
	if (FindComponent(L"imgRotation") != NULL)
		FindComponent(L"imgRotation")->Free();

	TImage *imgRotation = new TImage(this);
	imgRotation->Name = L"imgRotation";
	imgRotation->Parent = FMain;
	imgRotation->Visible = true;
	imgRotation->Width = 200;
	imgRotation->Height = 200;
	imgRotation->Canvas->Brush->Style = bsSolid;
	imgRotation->Canvas->Brush->Color = clWhite; // clGray;
	imgRotation->Top = this->Height - imgRotation->Height;
	imgRotation->Left = this->Width - imgRotation->Width;
	int Xcentre = (int)(imgRotation->Width / 2);
	int Ycentre = (int)(imgRotation->Height / 2);

	imgRotation->Canvas->Pen->Color = clBlack;
	imgRotation->Canvas->Pen->Width = 2;
	int Rayon = (int)((imgRotation->Width - 15 )/ 2);
	int Rayon2 = Rayon - 70;
	imgRotation->Canvas->Ellipse(Xcentre - Rayon2, Ycentre - Rayon,
		Xcentre + Rayon2, Ycentre + Rayon);

	//Centre
	imgRotation->Canvas->Pixels[Xcentre][Ycentre] = clRed;
}

/**
 * \fn void __fastcall TFMain::bDoRotationClick(TObject *Sender)
 * \brief Evénement OnClick du bouton "Do Rotation"
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::bDoRotationClick(TObject *Sender)
{
	if (FindComponent(L"imgRotation") != NULL)
	{
		TImage *imgSrc = dynamic_cast<TImage*>(FindComponent(L"imgRotation"));

		if (FindComponent(L"imgDestination") == NULL) {
			TImage *imgDestination = new TImage(this);
			imgDestination->Name = L"imgDestination";
			imgDestination->Parent = FMain;
			imgDestination->Visible = true;
			imgDestination->Width = 750;
			imgDestination->Height = 750;
			imgDestination->Left = 0;
			imgDestination->Top = 0;
		}
		TImage *imgDest = dynamic_cast<TImage*>(FindComponent(L"imgDestination"));

		double dAngle = (seAngleRotation->Value * 2.0 * Pi / 360.0);

		Rotation(dAngle, imgSrc, imgDest, seRotationX->Value, seRotationY->Value);
	}
	else
		ShowMessage("No image");
}


/**
 * \fn void __fastcall TFMain::imgMyClick(TObject *Sender)
 * \brief Evénement OnClick générique affecté par code à l'image lors de sa création
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::imgMyClick(TObject *Sender)
{
	int iTypeObj, iIndObj;
	GetClickObject(dynamic_cast<TImage*>(Sender), xMouseDown, yMouseDown, 1, &iTypeObj, &iIndObj);
	SetInfoBulle(iTypeObj, iIndObj);
}

/**
 * \fn void __fastcall TFMain::imgMyMouseDown(...
 * \brief Evénement OnMouseDown générique affecté par code à l'image lors de sa création
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::imgMyMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft)
	{
		xMouseDown = X;
		yMouseDown = Y;
	}
}

/**
 * \fn void __fastcall TFMain::imgMyMouseUp(...
 * \brief Evénement OnMouseDown générique affecté par code à l'image lors de sa création
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::imgMyMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft)
	{
		int iDistance = CalculDistance(X, Y, xMouseDown, yMouseDown);
		if (iDistance > 10)
			ShowMessage(L"Distance : " + IntToStr(iDistance));
		/*
		if (iDistance > 10)
		{
			int iTypeObj, iIndObj, iTypeObjDown, iIndObjDown;
			GetClickObject(X, Y, 0, &iTypeObj, &iIndObj);
			GetClickObject(xMouseDown, yMouseDown, 0, &iTypeObjDown, &iIndObjDown);
			if (iTypeObjDown == iTypeObj)
			{
				if (iTypeObj == 1)
					OpenReagent(iIndObjDown, iIndObj);
				else if ((iTypeObj == 3) && (iIndObjDown == iIndObj))
					OpenK7(iIndObjDown);
				else
					Memo1->Lines->Add(IntToStr(iTypeObjDown) + L"/"
									+ IntToStr(iIndObjDown) + L" => " + IntToStr(iTypeObj) + L"/"
									+ IntToStr(iIndObj));
			}
		}
		*/
	}
	else
	{
		/*
		int iTypeObj, iIndObj;
		GetClickObject(X, Y, 0, &iTypeObj, &iIndObj);
		ShowMessage(L"Click droit " + IntToStr(iTypeObj) + L"/"
						+ IntToStr(iIndObj));
		*/
	}
}

/**
 * \fn void TFMain::SetInfoBulle(int iTypeObj, int iIndObj)
 * \brief Affichage de l'info bulle de l'objet cliqué
 *
 * \param 	iTypeObj
 *          iIndObj
 * \return .
 *
 *
 */
void TFMain::SetInfoBulle(int iTypeObj, int iIndObj)
{
	if (iTypeObj  > 0)
	{
		mBulleInfo->Clear();
		UnicodeString sObject = "ADU"; //TabTypeObject[iTypeObj];
		UnicodeString sCaption = L"";
		/*
		if (lblFichierIni->Caption != L"...")
		{
			TIniFile *ScanIni = new TIniFile(lblFichierIni->Caption);
			if (iTypeObj == 1) //Reagent
			{
					mBulleInfo->Lines->Add(L"Reagent n° " + IntToStr(iIndObj));
					UnicodeString sReagent = ScanIni->ReadString(L"Reagent", L"Reagent" + IntToStr(iIndObj+1), L"");
					if (sReagent != L"")
						mBulleInfo->Lines->Add("ID ");
					else
						mBulleInfo->Lines->Add("Absent");
			}
			else if (iTypeObj == 2) //Temp
			{
				//Nothing
			}
			else if (iTypeObj == 3) //Cassette
			{
					mBulleInfo->Lines->Add(L"Cassette n° " + IntToStr(iIndObj));
					UnicodeString sTypeK7 = ScanIni->ReadString(L"K7", L"Type" + IntToStr(iIndObj+1), L"");
					UnicodeString sIdK7 = ScanIni->ReadString(L"K7", L"Id" + IntToStr(iIndObj+1), L"");
					if ((sTypeK7 == L"N") || (sTypeK7 == L""))
						mBulleInfo->Lines->Add("Absent");
					else
					{
						if (sTypeK7 == L"C")
							mBulleInfo->Lines->Add(L"Consumables");
						else if (sTypeK7 == L"T")
							mBulleInfo->Lines->Add("Samples");
						mBulleInfo->Lines->Add("ID " + sIdK7);
					}
			}
			else if ((iTypeObj >= 4) && (iTypeObj <= 6))
			{
				int iK7;
				if (iTypeObj == 4) //DilPlate
					iK7 = (int)(iIndObj/iNbDil);
				else if (iTypeObj == 5) //Bottle
					iK7 = (int)(iIndObj/iNbBottle);
				else if ((iTypeObj == 6) || (iTypeObj == 7))//Tube
					iK7 = (int)(iIndObj/iNbTubeK7);
				mBulleInfo->Lines->Add(L"Cassette n° " + IntToStr(iK7));
				UnicodeString sTypeK7 = ScanIni->ReadString(L"K7", L"Type" + IntToStr(iK7+1), L"");
				UnicodeString sIdK7 = ScanIni->ReadString(L"K7", L"Id" + IntToStr(iK7+1), L"");
				if ((sTypeK7 == L"N") || (sTypeK7 == L""))
					mBulleInfo->Lines->Add("Absent");
				else
				{
					if (sTypeK7 == L"C")
						mBulleInfo->Lines->Add(L"Consommables");
					else if (sTypeK7 == L"T")
						mBulleInfo->Lines->Add(L"Samples");
					mBulleInfo->Lines->Add("ID " + sIdK7);
				}
				if (iTypeObj == 4) //DilPlate
				{
					int iDilPlate = (int)(iIndObj%iNbDil);
					mBulleInfo->Lines->Add(L"Diplate n° " + IntToStr(iDilPlate));
					UnicodeString sDiplate = ScanIni->ReadString(L"K7_" + IntToStr(iK7+1), L"Dil" + IntToStr(iDilPlate+1), L"");
					if (sDiplate != L"")
						mBulleInfo->Lines->Add("ID " + sDiplate);
					else
						mBulleInfo->Lines->Add("Absent");
				}
				else if (iTypeObj == 5) //Bottle
				{
					int iBottle = (int)(iIndObj%iNbBottle);
					mBulleInfo->Lines->Add(L"Bottle n° " + IntToStr(iBottle));
					UnicodeString sBottle = ScanIni->ReadString(L"K7_" + IntToStr(iK7+1), L"Bottle" + IntToStr(iBottle+1), L"");
					if (sBottle != L"")
						mBulleInfo->Lines->Add("ID " + sBottle);
					else
						mBulleInfo->Lines->Add("Absent");
				}
				else if ((iTypeObj == 6) || (iTypeObj == 7)) //Tube "intérieur", Tube "Extérieur"
				{
					int iTube = (int)(iIndObj%iNbTubeK7);
					mBulleInfo->Lines->Add(L"Tube n° " + IntToStr(iTube));
					UnicodeString sTube = ScanIni->ReadString(L"K7_" + IntToStr(iK7+1), L"Tube" + IntToStr(iTube+1), L"");
					if (sTube != L"")
						mBulleInfo->Lines->Add("ID " + sTube);
					else
						mBulleInfo->Lines->Add("Absent");
				}
			}
			ScanIni->Free();
		}
		else
		*/
			sCaption = L"Objet : " + sObject + L" n° " + IntToStr(iIndObj);
		pInfoBulle->Caption = sCaption;
		pInfoBulle->Visible = true;
		tInfoBulle->Enabled = true;
	}
}

/**
 * \fn void TFMain::MaskInfoBulle
 * \brief Masquage de l'info bulle
 *
 * \param
 * \return .
 *
 *
 */
void TFMain::MaskInfoBulle()
{
	if (pInfoBulle->Visible == true)
	{
		pInfoBulle->Visible = false;
		tInfoBulle->Enabled = false;
	}
}

/**
 * \fn void __fastcall TFMain::tInfoBulleTimer(TObject *Sender)
 * \brief Evénement timer qui masque l'info bulle
 *
 * \param
 * \return .
 *
 *
 */
void __fastcall TFMain::tInfoBulleTimer(TObject *Sender)
{
	MaskInfoBulle();
}

/**
 * \fn void __fastcall TFMain::bInitScanClick(TObject *Sender)
 * \brief Evénement OnClick du bouton "Scan K7"
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::bInitScanClick(TObject *Sender)
{
	iK7Type[0] = cbCass0->ItemIndex-1;
	iK7Type[1] = cbCass1->ItemIndex-1;
	iK7Type[2] = cbCass2->ItemIndex-1;
	iK7Type[3] = cbCass3->ItemIndex-1;
	iK7Type[4] = cbCass4->ItemIndex-1;
	bCarousel->Click();
}

/**
 * \fn void __fastcall TFMain::bPrevCassetteClick(TObject *Sender)
 * \brief Evénement OnClick du bouton "<< Cassette"
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::bPrevCassetteClick(TObject *Sender)
{
	DeplaceCassette(-1);
}
//---------------------------------------------------------------------------

/**
 * \fn void __fastcall TFMain::bNextCassetteClick(TObject *Sender)
 * \brief Evénement OnClick du bouton "Cassette >>"
 *
 * \param Sender
 * \return .
 *
 *
 */
void __fastcall TFMain::bNextCassetteClick(TObject *Sender)
{
	DeplaceCassette(1);
}

/**
 * \fn void __fastcall TFMain::DeplaceCassette(int iMouv)
 * \brief déplacement d'une cassette (rotation)
 *
 * \param iMouv valeur du déplacement
 * \return .
 *
 *
 */
void TFMain::DeplaceCassette(int iMouv)
{
	int iOffsetK7 = GetOffsetK7();
	iOffsetK7 += iMouv;
	if (iOffsetK7 < 0)
		iOffsetK7 += iNbK7;
	else if (iOffsetK7 >= iNbK7)
		iOffsetK7 -= iNbK7;
	lblDeltaCassette->Caption = IntToStr(iOffsetK7);
	SetOffsetK7(iOffsetK7);
	bCarousel->Click();
}
//---------------------------------------------------------------------------

