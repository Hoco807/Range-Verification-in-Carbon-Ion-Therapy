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
	TChain *Singles = new TChain("Singles");
	Singles->Add(inputfilename.c_str());
	filename = argv[2];
	ofstream fileout(filename.c_str());
	
	Int_t eventID,level1ID;
	Float_t energy;
	Float_t globalPosX;
	Float_t globalPosY;
	Float_t globalPosZ;

	Singles->SetBranchStatus("*",0);
	Singles->SetBranchAddress("eventID",&eventID);
	Singles->SetBranchAddress("level1ID",&level1ID);
	Singles->SetBranchAddress("globalPosX",&globalPosX);
	Singles->SetBranchAddress("globalPosY",&globalPosY);
	Singles->SetBranchAddress("globalPosZ",&globalPosZ);
	Singles->SetBranchAddress("energy",&energy);

	Int_t n_entries = (Int_t)(Singles->GetEntries());
	Int_t counts = 0;  
	Int_t nbytes= 0;
	for(Int_t i = 0; i < n_entries; i++)
	{
		nbytes += Singles->GetEntry(i);
		fileout << eventID << "	" <<  level1ID << "	" << energy << "	" << globalPosX << "	" << globalPosY << "	" << globalPosZ << endl;
		counts++;
	}
	cout << "number of the Single events =	" << n_entries << endl;
	cout << "nbytes =	" << nbytes << endl;
	cout << "counts =	" << counts << endl;
	return 0;
}
