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

#include <vcl.h>
#pragma hdrstop

#include "UFMain.h"
#include "UFonctionsKC.h"
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

	int RayonExt = 370;
	int RayonInt = 150;
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
	imgDest->Canvas->Ellipse(Xcentre - RayonTube, Ycentre - RayonTube,
								Xcentre + RayonTube, Ycentre + RayonTube);
	//!Cercle Consommables

	//Cassettes
	double dDelta = - Pi / 2; //Retour pour commencer "en haut"
	for (int i = 0; i < iNbK7; i++)
	{
		double Angle = (((double)(i/* + 0.5*/) * GetAngleObject(3)) + dDelta);

		int X = (int)((double)Xcentre + (RayonExt * cos(Angle)));
		int Y = (int)((double)Ycentre + (RayonExt * sin(Angle)));
		imgDest->Canvas->MoveTo(X, Y);
		X = (int)((double)Xcentre + (RayonInt * cos(Angle)));
		Y = (int)((double)Ycentre + (RayonInt * sin(Angle)));
		imgDest->Canvas->LineTo(X, Y);

		//Etiquette
		X = (int)((double)Xcentre + ((RayonInt + RayonExt) / 2 * cos(Angle)));
		Y = (int)((double)Ycentre + ((RayonInt + RayonExt) / 2 * sin(Angle)));
		imgDest->Canvas->TextOutW(X, Y, IntToStr(i));
	}
	//!Cassettes

	//Reactifs
	/*
	double dAngleReactif = (double)((1.0 / (double)(iNbK7 * iNbReagent)) * 2 * Pi);
	for (int i = 0; i < iNbK7; i++) {
		for (int j = 0; j < iNbReagent; j++) {
			double dAngle = (double)((double)((i * iNbReagent) + j + 0.5) * dAngleReactif) + dDelta;

			int X = (int)((double)Xcentre + (RayonCentreRgt  * cos(dAngle)));
			int Y = (int)((double)Ycentre + (RayonCentreRgt * sin(dAngle)));
			imgDest->Canvas->Pixels[X][Y] = clRed;

			X = X - (imgSrc->Width / 2);
			Y = Y - (imgSrc->Height / 2);
			dAngle = dAngle - (Pi / 2);
			Rotation(dAngle, imgSrc, imgDest, X, Y);

			//Etiquette
			X = X + (imgSrc->Width / 2);
			Y = Y + (imgSrc->Height / 2);
			imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
		}
	}
	*/
	//!Reactifs

	//Tubes
	double dAngletubeInt = (double)((1.0 / (double)(iNbK7 * iNbTubeK7Int)) * 2 * Pi);
	double dAngletubeExt = (double)((1.0 / (double)(iNbK7 * iNbTubeK7Ext)) * 2 * Pi);
	for (int i = 0; i < iNbK7; i++) {
		for (int j = 0; j < iNbTubeK7Int; j++) {
			double dAngle = (double)((double)((i * iNbTubeK7Int) + j + 0.5) * dAngletubeInt) + dDelta;

			int X = (int)((double)Xcentre + (RayonCentreTubeInt  * cos(dAngle)));// + iRayonB;
			int Y = (int)((double)Ycentre + (RayonCentreTubeInt * sin(dAngle)));// + iRayonB;
			imgDest->Canvas->Pixels[X][Y] = clBlue;
			imgDest->Canvas->Ellipse(X - iRayonT, Y - iRayonT, X + iRayonT, Y + iRayonT);

			//Etiquette
			imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
		}

		for (int j = 0; j < iNbTubeK7Ext; j++) {
			double dAngle = (double)((double)((i * iNbTubeK7Ext) + j + 0.5) * dAngletubeExt) + dDelta;

			int X = (int)((double)Xcentre + (RayonCentreTubeExt  * cos(dAngle)));// + iRayonB;
			int Y = (int)((double)Ycentre + (RayonCentreTubeExt * sin(dAngle)));// + iRayonB;
			imgDest->Canvas->Pixels[X][Y] = clBlue;
			imgDest->Canvas->Ellipse(X - iRayonT, Y - iRayonT, X + iRayonT, Y + iRayonT);

			//Etiquette
			imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
		}
	}
	//!Tubes

	//Bouteilles
	double dAngleBouteille = (double)((1.0 / (double)(iNbK7 * iNbBottle)) * 2 * Pi);
	for (int i = 0; i < iNbK7; i++) {
		for (int j = 0; j < iNbBottle; j++) {
			double dAngle = (double)((double)((i * iNbBottle) + j + 0.5) * dAngleBouteille) + dDelta;

			int X = (int)((double)Xcentre + (RayonCentreConso  * cos(dAngle)));// + iRayonB;
			int Y = (int)((double)Ycentre + (RayonCentreConso * sin(dAngle)));// + iRayonB;
			imgDest->Canvas->Pixels[X][Y] = clBlue;
			imgDest->Canvas->Ellipse(X - iRayonB, Y - iRayonB, X + iRayonB, Y + iRayonB);

			//Etiquette
			imgDest->Canvas->TextOutW(X, Y, IntToStr(i) + "-" + IntToStr(j));
		}
	}
	//!Bouteilles

	//Plaques de dilution
	int RayonDilExt = RayonCentreConso + iDilWidth + 5;
	int RayonDilInt = RayonCentreConso - iDilWidth - 5;
	int RayonDilIntBis = RayonDilInt;
	int iTotDil = iNbDil * iNbK7;
	for (int i = 0; i < iTotDil; i++)
	{
		double dAngleStart = (((double)(i+0.02 /* + 0.5 */) * GetAngleObject(4))) + dDelta;

		int X1 = (int)((double)Xcentre + (RayonDilExt * cos(dAngleStart)));
		int Y1 = (int)((double)Ycentre + (RayonDilExt * sin(dAngleStart)));
		int X4 = (int)((double)Xcentre + (RayonDilInt * cos(dAngleStart)));
		int Y4 = (int)((double)Ycentre + (RayonDilInt * sin(dAngleStart)));

		double dAngleStop = (((double)(i+0.98 /* + 0.5 */) * GetAngleObject(4))) + dDelta;
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
	imgDest->Canvas->Pen->Color = clBlack;
	//!Plaques de dilution

	//Cercle intérieur
	imgDest->Canvas->Ellipse(Xcentre - RayonInt, Ycentre - RayonInt,
								Xcentre + RayonInt, Ycentre + RayonInt);
	//!Cercle intérieur

	Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
