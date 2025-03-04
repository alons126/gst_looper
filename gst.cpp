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
    TH1D *h_El_all_Int = new TH1D("El_all_Int", "E_{e} in (e,e');E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_all_Int = new TH1D("Q2_all_Int", "Q2 in (e,e');Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_QE = new TH1D("El_QE", "E_{e} in (e,e') and QE;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_QE = new TH1D("Q2_QE", "Q2 in (e,e') and QE;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_MEC = new TH1D("El_MEC", "E_{e} in (e,e') and MEC;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_MEC = new TH1D("Q2_MEC", "Q2 in (e,e') and MEC;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_RES = new TH1D("El_RES", "E_{e} in (e,e') and RES;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_RES = new TH1D("Q2_RES", "Q2 in (e,e') and RES;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_DIS = new TH1D("El_DIS", "E_{e} in (e,e') and DIS;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_DIS = new TH1D("Q2_DIS", "Q2 in (e,e') and DIS;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);

    TH1D *h_El_all_Int_2p = new TH1D("El_all_Int_2p", "E_{e} in 2p;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_all_Int_2p = new TH1D("Q2_all_Int_2p", "Q2 in 2p;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_QE_2p = new TH1D("El_QE_2p", "E_{e} in 2p and QE;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_QE_2p = new TH1D("Q2_QE_2p", "Q2 in 2p and QE;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_MEC_2p = new TH1D("El_MEC_2p", "E_{e} in 2p and MEC;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_MEC_2p = new TH1D("Q2_MEC_2p", "Q2 in 2p and MEC;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_RES_2p = new TH1D("El_RES_2p", "E_{e} in 2p and RES;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_RES_2p = new TH1D("Q2_RES_2p", "Q2 in 2p and RES;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_DIS_2p = new TH1D("El_DIS_2p", "E_{e} in 2p and DIS;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_DIS_2p = new TH1D("Q2_DIS_2p", "Q2 in 2p and DIS;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);

    TH1D *h_El_all_Int_1n1p = new TH1D("El_all_Int_1n1p", "E_{e} in 1n1p;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_all_Int_1n1p = new TH1D("Q2_all_Int_1n1p", "Q2 in 1n1p;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_QE_1n1p = new TH1D("El_QE_1n1p", "E_{e} in 1n1p and QE;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_QE_1n1p = new TH1D("Q2_QE_1n1p", "Q2 in 1n1p and QE;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_MEC_1n1p = new TH1D("El_MEC_1n1p", "E_{e} in 1n1p and MEC;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_MEC_1n1p = new TH1D("Q2_MEC_1n1p", "Q2 in 1n1p and MEC;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_RES_1n1p = new TH1D("El_RES_1n1p", "E_{e} in 1n1p and RES;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_RES_1n1p = new TH1D("Q2_RES_1n1p", "Q2 in 1n1p and RES;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);
    TH1D *h_El_DIS_1n1p = new TH1D("El_DIS_1n1p", "E_{e} in 1n1p and DIS;E_{e} [GeV]", 50, 0, 6.5);
    TH1D *h_Q2_DIS_1n1p = new TH1D("Q2_DIS_1n1p", "Q2 in 1n1p and DIS;Q^{2} [GeV^{2}/c^{2}]", 50, 0, 6.5);

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

        if (acos(pzl / sqrt(pxl * pxl + pyl * pyl + pzl * pzl)) * 180.0 / 3.14159265359 < 7.) { continue; }

        bool Is2p = (nf == 2 && nfn == 0 && nfp == 2);
        bool Is1n1p = (nf == 2 && nfn == 1 && nfp == 1);

        if (!(Is2p || Is1n1p)) { continue; }

        if (Is2p) {
            double theta_p1 = acos(pzf[0] / sqrt(pxf[0] * pxf[0] + pyf[0] * pyf[0] + pzf[0] * pzf[0])) * 180.0 / 3.14159265359;
            double theta_p2 = acos(pzf[1] / sqrt(pxf[1] * pxf[1] + pyf[1] * pyf[1] + pzf[1] * pzf[1])) * 180.0 / 3.14159265359;
            bool isInAcceptance =
                (((theta_p1 >= 5. && theta_p1 <= 40.) && (theta_p2 >= 40. && theta_p2 <= 140.)) || ((theta_p2 >= 5. && theta_p2 <= 40.) && (theta_p1 >= 40. && theta_p1 <= 140.)));
            bool ispFDpCD = (isInAcceptance && (pf[0] >= 0.4) && (pf[1] >= 0.4));

            if (ispFDpCD) {
                h_El_all_Int_2p->Fill(El);
                h_Q2_all_Int_2p->Fill(Q2);
        
                if (qel) {
                    h_El_QE_2p->Fill(El);
                    h_Q2_QE_2p->Fill(Q2);
                } else if (mec) {
                    h_El_MEC_2p->Fill(El);
                    h_Q2_MEC_2p->Fill(Q2);
                } else if (res) {
                    h_El_RES_2p->Fill(El);
                    h_Q2_RES_2p->Fill(Q2);
                } else if (dis) {
                    h_El_DIS_2p->Fill(El);
                    h_Q2_DIS_2p->Fill(Q2);
                }        
            }
        } else if (Is1n1p) {
            int neutron_ind, proton_ind;

            if (pdgf[0] == 2112) {
                neutron_ind = 0;
                proton_ind = 1;
            } else {
                neutron_ind = 1;
                proton_ind = 0;
            }

            double theta_n =
                acos(pzf[neutron_ind] / sqrt(pxf[neutron_ind] * pxf[neutron_ind] + pyf[neutron_ind] * pyf[neutron_ind] + pzf[neutron_ind] * pzf[neutron_ind])) * 180.0 / 3.14159265359;
            double theta_p = acos(pzf[proton_ind] / sqrt(pxf[proton_ind] * pxf[proton_ind] + pyf[proton_ind] * pyf[proton_ind] + pzf[proton_ind] * pzf[proton_ind])) * 180.0 / 3.14159265359;
            bool isInAcceptance = ((theta_n >= 5. && theta_n <= 40.) && (theta_p >= 40. && theta_p <= 140.));
            bool isnFDpCD = (isInAcceptance && (pf[0] >= 0.4) && (pf[1] >= 0.4));
        
            if (isnFDpCD) {
                h_El_all_Int_1n1p->Fill(El);
                h_Q2_all_Int_1n1p->Fill(Q2);
        
                if (qel) {
                    h_El_QE_1n1p->Fill(El);
                    h_Q2_QE_1n1p->Fill(Q2);
                } else if (mec) {
                    h_El_MEC_1n1p->Fill(El);
                    h_Q2_MEC_1n1p->Fill(Q2);
                } else if (res) {
                    h_El_RES_1n1p->Fill(El);
                    h_Q2_RES_1n1p->Fill(Q2);
                } else if (dis) {
                    h_El_DIS_1n1p->Fill(El);
                    h_Q2_DIS_1n1p->Fill(Q2);
                }        
            }
        }

        h_El_all_Int->Fill(El);
        h_Q2_all_Int->Fill(Q2);

        if (qel) {
            h_El_QE->Fill(El);
            h_Q2_QE->Fill(Q2);
        } else if (mec) {
            h_El_MEC->Fill(El);
            h_Q2_MEC->Fill(Q2);
        } else if (res) {
            h_El_RES->Fill(El);
            h_Q2_RES->Fill(Q2);
        } else if (dis) {
            h_El_DIS->Fill(El);
            h_Q2_DIS->Fill(Q2);
        }
    }

    int pixelx = 1980, pixely = 1530;
    TCanvas *canvas = new TCanvas("myText", "myText", pixelx, pixely);
    canvas->cd();

    h_El_all_Int->Draw();
    canvas->SaveAs("./h_El_all_Int.pdf");
    canvas->Clear();

    h_Q2_all_Int->Draw();
    canvas->SaveAs("./h_Q2_all_Int.pdf");
    canvas->Clear();

    h_El_QE->Draw();
    canvas->SaveAs("./h_El_QE.pdf");
    canvas->Clear();

    h_Q2_QE->Draw();
    canvas->SaveAs("./h_Q2_QE.pdf");
    canvas->Clear();

    h_El_MEC->Draw();
    canvas->SaveAs("./h_El_MEC.pdf");
    canvas->Clear();

    h_Q2_MEC->Draw();
    canvas->SaveAs("./h_Q2_MEC.pdf");
    canvas->Clear();

    h_El_RES->Draw();
    canvas->SaveAs("./h_El_RES.pdf");
    canvas->Clear();

    h_Q2_RES->Draw();
    canvas->SaveAs("./h_Q2_RES.pdf");
    canvas->Clear();

    h_El_DIS->Draw();
    canvas->SaveAs("./h_El_DIS.pdf");
    canvas->Clear();

    h_Q2_DIS->Draw();
    canvas->SaveAs("./h_Q2_DIS.pdf");
    canvas->Clear();

    h_El_all_Int_2p->Draw();
    canvas->SaveAs("./h_El_all_Int_2p.pdf");
    canvas->Clear();

    h_Q2_all_Int_2p->Draw();
    canvas->SaveAs("./h_Q2_all_Int_2p.pdf");
    canvas->Clear();

    h_El_QE_2p->Draw();
    canvas->SaveAs("./h_El_QE_2p.pdf");
    canvas->Clear();

    h_Q2_QE_2p->Draw();
    canvas->SaveAs("./h_Q2_QE_2p.pdf");
    canvas->Clear();

    h_El_MEC_2p->Draw();
    canvas->SaveAs("./h_El_MEC_2p.pdf");
    canvas->Clear();

    h_Q2_MEC_2p->Draw();
    canvas->SaveAs("./h_Q2_MEC_2p.pdf");
    canvas->Clear();

    h_El_RES_2p->Draw();
    canvas->SaveAs("./h_El_RES_2p.pdf");
    canvas->Clear();

    h_Q2_RES_2p->Draw();
    canvas->SaveAs("./h_Q2_RES_2p.pdf");
    canvas->Clear();

    h_El_DIS_2p->Draw();
    canvas->SaveAs("./h_El_DIS.pdf");
    canvas->Clear();

    h_Q2_DIS_2p->Draw();
    canvas->SaveAs("./h_Q2_DIS_2p.pdf");
    canvas->Clear();
    
    h_El_all_Int_1n1p->Draw();
    canvas->SaveAs("./h_El_all_Int_1n1p.pdf");
    canvas->Clear();

    h_Q2_all_Int_1n1p->Draw();
    canvas->SaveAs("./h_Q2_all_Int_1n1p.pdf");
    canvas->Clear();

    h_El_QE_1n1p->Draw();
    canvas->SaveAs("./h_El_QE_1n1p.pdf");
    canvas->Clear();

    h_Q2_QE_1n1p->Draw();
    canvas->SaveAs("./h_Q2_QE_1n1p.pdf");
    canvas->Clear();

    h_El_MEC_1n1p->Draw();
    canvas->SaveAs("./h_El_MEC_1n1p.pdf");
    canvas->Clear();

    h_Q2_MEC_1n1p->Draw();
    canvas->SaveAs("./h_Q2_MEC_1n1p.pdf");
    canvas->Clear();

    h_El_RES_1n1p->Draw();
    canvas->SaveAs("./h_El_RES_1n1p.pdf");
    canvas->Clear();

    h_Q2_RES_1n1p->Draw();
    canvas->SaveAs("./h_Q2_RES_1n1p.pdf");
    canvas->Clear();

    h_El_DIS_1n1p->Draw();
    canvas->SaveAs("./h_El_DIS.pdf");
    canvas->Clear();

    h_Q2_DIS_1n1p->Draw();
    canvas->SaveAs("./h_Q2_DIS_1n1p.pdf");
    canvas->Clear();
}
