#include <iostream>
#include <sstream>
#include <fstream>
#include "TROOT.h"
#include "TSystem.h"
#include "TChain.h"
#include "TH2D.h"
#include "TDirectory.h"
#include "TList.h"
#include "Rtypes.h"
#include "TChainElement.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"
#include "TH2.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TRandom.h"
using namespace std;
int main(int argc, char ** argv)
{
	string inputfilename;
	string filename;
	inputfilename = argv[1];
	cout << "input filename is = " << inputfilename << endl;
	TChain *PhaseSpace = new TChain("PhaseSpace");
	PhaseSpace->Add(inputfilename.c_str());
	filename = argv[2];
	ofstream fileout(filename.c_str());
	
	Float_t X;
	Float_t Y;
	Float_t Z;
	Float_t dX;
	Float_t dY;
	Float_t dZ;
	Float_t Ekine;
	Char_t ParticleName[10];

	PhaseSpace->SetBranchStatus("*",0);
	PhaseSpace->SetBranchAddress("X",&X);
	PhaseSpace->SetBranchAddress("Y",&Y);
	PhaseSpace->SetBranchAddress("Z",&Z);
	PhaseSpace->SetBranchAddress("dX",&dX);
	PhaseSpace->SetBranchAddress("dY",&dY);
	PhaseSpace->SetBranchAddress("dZ",&dZ);
	PhaseSpace->SetBranchAddress("Ekine",&Ekine);
	PhaseSpace->SetBranchAddress("ParticleName",&ParticleName);

	Int_t n_entries = (Int_t)(PhaseSpace->GetEntries());
	Int_t counts = 0;  
	Int_t nbytes= 0;
	for(Int_t i = 0; i < n_entries; i++)
	{
		nbytes += PhaseSpace->GetEntry(i);
		fileout << Ekine << "	" <<  X << "	" << Y << "	" << Z << "	" << dX << "	" << dY << "	" << dZ << "	"<< ParticleName << endl;
		counts++;
	}
	cout << "number of the Single events =	" << n_entries << endl;
	cout << "nbytes =	" << nbytes << endl;
	cout << "counts =	" << counts << endl;
	return 0;
}
