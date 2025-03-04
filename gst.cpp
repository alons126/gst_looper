#define gst_cxx
#include "gst.h"

#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>

void gst::Loop() {
    //   In a ROOT session, you can do:
    //      root> .L gst.C
    //      root> gst t
    //      root> t.GetEntry(12); // Fill t data members with entry number 12
    //      root> t.Show();       // Show values of entry 12
    //      root> t.Show(16);     // Read and show values of entry 16
    //      root> t.Loop();       // Loop on all entries
    //

    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    // by  b_branchname->GetEntry(ientry); //read only this branch
    TH1D *h_El = new TH1D("", "", 100, 0, 1);
    TH1D *h_Q2 = new TH1D("Q2 in (e,e')", "Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6);

    int limiter = 1000000;

    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        
        if (jentry > limiter) { break; }

        Long64_t ientry = LoadTree(jentry);

        if (ientry < 0) break;

        nb = fChain->GetEntry(jentry);

        nbytes += nb;

        h_El->Fill(El);
        h_Q2->Fill(Q2);

    }

    int pixelx = 1980, pixely = 1530;
    TCanvas *canvas = new TCanvas("myText", "myText", pixelx, pixely);
    canvas->cd();

    h_El->Draw();
    canvas->SaveAs("./h_El.pdf");
    canvas->Clear();

    h_Q2->Draw();
    canvas->SaveAs("./h_Q2.pdf");
    canvas->Clear();
}
