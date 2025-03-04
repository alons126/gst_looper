//
// Created by alons on 12/05/2023.
//

#ifndef DATA_ANALYSER_BETAFITAPPRAX_H
#define DATA_ANALYSER_BETAFITAPPRAX_H

#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TDatabasePDG.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TLatex.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <string>

#include "../../classes/DSCuts/DSCuts.h"
#include "../../classes/hPlots/hPlot1D.h"
#include "../../constants.h"
#include "../EventProperties/GetParticleName.h"
#include "../EventProperties/GetParticleNameShort.h"
#include "../GeneralFunctions.h"
#include "../drawtext.h"
#include "FitFunction.h"

using namespace std;

void BetaFitApprax(const string &SampleName, DSCuts &Beta_cut, DSCuts &Momentum_cuts, const hPlot1D &BetaPlot, TList *Histogram_list, const double beamE) {
    double W_yLLim = -0.1, W_yULim = 0.1, W_xLLim = 0.9, W_xULim = 1.;
    double deltaPRel_UncertaintyU = 0.2, deltaPRel_UncertaintyL = 0.1;

    system(("mkdir -p " + BetaPlot.GetHistogram1DSaveNamePath() + "Approximatied_beta/").c_str());

    //<editor-fold desc="Canvas definitions">
    TCanvas *Canvas = new TCanvas("Canvas", "Canvas", 1000 * 2, 750 * 2);  // normal res
    Canvas->SetGrid();
    Canvas->SetBottomMargin(0.14);

    Canvas->SetLeftMargin(0.18);
    Canvas->SetRightMargin(0.12);

    float DefStatX = gStyle->GetStatX(), DefStatY = gStyle->GetStatY();

    Canvas->cd();

    //    cout << "\n\n\n\n" << BetaPlot.GetHistogram1DSaveNamePath() << "Approximatied_beta/" << "\n\n\n\n";
    //    exit(0);
    //</editor-fold>

    //<editor-fold desc="Setting sNameFlag">
    string sNameFlag;

    if (findSubstring(SampleName, "sim")) {
        sNameFlag = "s";
    } else if (findSubstring(SampleName, "data")) {
        sNameFlag = "d";
    }
    //</editor-fold>

    //<editor-fold desc="Setting particle">
    string BetaParticle = GetParticleName(BetaPlot.GetHistogramTitle());
    string BetaParticleShort = GetParticleNameShort(BetaPlot.GetHistogramTitle());

    //    if (findSubstring(BetaPlot.GetHistogramTitle(), "neutrals") || findSubstring(BetaPlot.GetHistogramTitle(), "Neutrals")
    //        || findSubstring(BetaPlot.GetHistogramTitle(), "neut.") || findSubstring(BetaPlot.GetHistogramTitle(), "Neut.")) {
    //        BetaParticle = "Neutrals";
    //        BetaParticleShort = "neut";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "Electron") || findSubstring(BetaPlot.GetHistogramTitle(), "electron")) {
    //        BetaParticle = "Electron";
    //        BetaParticleShort = "e";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "Proton") || findSubstring(BetaPlot.GetHistogramTitle(), "proton")) {
    //        BetaParticle = "Proton";
    //        BetaParticleShort = "p";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "Neutron") || findSubstring(BetaPlot.GetHistogramTitle(), "neutron")) {
    //        BetaParticle = "Neutron";
    //        BetaParticleShort = "n";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "#pi^{+}")) {
    //        BetaParticle = "Piplus";
    //        BetaParticleShort = "#pi^{+}";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "#pi^{-}")) {
    //        BetaParticle = "Piminus";
    //        BetaParticleShort = "#pi^{-}";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "K^{+}")) {
    //        BetaParticle = "Kplus";
    //        BetaParticleShort = "K^{+}";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "K^{-}")) {
    //        BetaParticle = "Kminus";
    //        BetaParticleShort = "K^{-}";
    //    } else if (findSubstring(BetaPlot.GetHistogramTitle(), "#gamma") || findSubstring(BetaPlot.GetHistogramTitle(), "photon")
    //               || findSubstring(BetaPlot.GetHistogramTitle(), "Photon")) {
    //        BetaParticle = "Photon";
    //        BetaParticleShort = "#gamma";
    //    }
    //</editor-fold>

    //<editor-fold desc="Setting histogram">
    TH1D *hBeta = BetaPlot.GetHistogram();
    TH1D *hBeta_Clone = (TH1D *)hBeta->Clone((BetaPlot.GetHistogramStatTitle() + " - fitted").c_str());
    Int_t Color = hBeta_Clone->GetLineColor();
    //</editor-fold>

    if (hBeta_Clone->Integral() != 0.) {
        //<editor-fold desc="Preforming a fit">
        TF1 *func = new TF1("fit", FitFunction, 0, 2, 3);  // create a function with 3 parameters in the range [-3,3]
        func->SetLineColor(kRed);

        double BetaMax = hBeta_Clone->GetMaximum();
        double BetaMean = hBeta_Clone->GetMean();

        func->SetParameters(BetaMax, BetaMean, 0.001);  // start fit with histogram's max and mean
        func->SetParNames("Constant", "Mean_value", "Sigma");

        cout << "Beta histogram {max, mean}:\t{" << BetaMax << ", " << BetaMean << "}\n\n\n\n";

        // Adding limits to "Constant"
        double BetaConstantUlim = 1.2 * BetaMax;
        double BetaConstantLlim = 0.90 * BetaMax;
        //    double BetaConstantLlim = 0.67 * BetaMax;
        func->SetParLimits(0, BetaConstantLlim, BetaConstantUlim);
        cout << "Beta Constant {Llim, Ulim}:\t{" << BetaConstantLlim << ", " << BetaConstantUlim << "}\n\n";

        // Adding limits to "Mean_value"
        //    double BetaMean_valueUlim = 1.0075;
        double BetaMean_valueUlim = 1.02;
        double BetaMean_valueLlim = 1.0075;
        //        double BetaMean_valueLlim = 1.005;
        func->SetParLimits(1, BetaMean_valueLlim, BetaMean_valueUlim);
        cout << "Beta Mean_value {Llim, Ulim}:\t{" << BetaMean_valueLlim << ", " << BetaMean_valueUlim << "}\n\n";

        //    // Adding limits to "Sigma"
        ////    double BetaSigmaUlim = 0.015;
        //    double BetaSigmaUlim = 0.01;
        //    double BetaSigmaLlim = 0.00001;
        //    func->SetParLimits(2, BetaSigmaLlim, BetaSigmaUlim);
        //    cout << "Beta Sigma {Llim, Ulim}:\t{" << BetaSigmaLlim << ", " << BetaSigmaUlim << "}\n\n";

        cout << "\n";
        hBeta_Clone->Fit("fit");
        hBeta_Clone->Draw();
        cout << "\n";

        TF1 *fit = hBeta_Clone->GetFunction("fit");
        double FitAmp = fit->GetParameter(0);   // get p0
        double FitMean = fit->GetParameter(1);  // get p1
        double FitStd = fit->GetParameter(2);   // get p2

        Beta_cut.SetUpperCut(fit->GetParameter(2));
        //</editor-fold>

        //<editor-fold desc="Drawing fit parameters and saving">
        double x_1_Cut_legend = gStyle->GetStatX(), y_1_Cut_legend = gStyle->GetStatY() - 0.2;
        double x_2_Cut_legend = gStyle->GetStatX() - 0.2, y_2_Cut_legend = gStyle->GetStatY() - 0.3;

        double x_1_FitParam = x_1_Cut_legend, y_1_FitParam = y_1_Cut_legend;
        double x_2_FitParam = x_2_Cut_legend, y_2_FitParam = y_2_Cut_legend;
        //    double x_1_FitParam = gStyle->GetStatX(), y_1_FitParam = y_1_Cut_legend - 0.14;
        //    double x_2_FitParam = gStyle->GetStatX() - 0.2, y_2_FitParam = y_1_Cut_legend - 0.245;

        TPaveText *FitParam = new TPaveText(x_1_FitParam, y_1_FitParam, x_2_FitParam, y_2_FitParam, "NDC");
        FitParam->SetBorderSize(1);
        FitParam->SetTextFont(0);
        FitParam->SetFillColor(0);
        FitParam->SetTextAlign(12);
        FitParam->AddText(("Fit amp = " + to_string_with_precision(FitAmp, 8)).c_str());
        FitParam->AddText(("Fit mean = " + to_string_with_precision(FitMean, 8)).c_str());
        FitParam->AddText(("Fit std = " + to_string_with_precision(FitStd, 8)).c_str());
        ((TText *)FitParam->GetListOfLines()->Last())->SetTextColor(kRed);
        FitParam->Draw("same");

        string hBeta_CloneSaveNameDir = BetaPlot.GetHistogram1DSaveNamePath() + "Approximatied_beta/" + sNameFlag + BetaPlot.GetHistogram1DSaveName() + "_fitted.png";
        const char *hBeta_CloneSaveDir = hBeta_CloneSaveNameDir.c_str();
        Canvas->SaveAs(hBeta_CloneSaveDir);

        Canvas->Clear();
        //</editor-fold>

        //<editor-fold desc="Plot deltaP as function of beta">
        string deltaPStatsTitle = "#deltaP_{" + BetaParticleShort + "} (" + BetaPlot.GetFinalState() + ")";
        string deltaPTitle = BetaParticle + " momentum uncertainty #deltaP_{" + BetaParticleShort + "} (" + BetaPlot.GetFinalState() + ")";
        string deltaPfunc = to_string(m_n * FitStd) + "/ ( (1 - x*x) * sqrt(1 - x*x) )";

        auto *deltaP = new TF1(deltaPStatsTitle.c_str(), deltaPfunc.c_str(), 0.9, 1);
        deltaP->SetTitle(deltaPTitle.c_str());
        deltaP->GetXaxis()->SetTitleSize(0.06);
        deltaP->GetXaxis()->SetLabelSize(0.0425);
        deltaP->GetXaxis()->CenterTitle(true);
        deltaP->GetXaxis()->SetTitle("#beta");
        deltaP->GetYaxis()->SetRangeUser(0., 30.);
        deltaP->GetYaxis()->SetTitleSize(0.06);
        deltaP->GetYaxis()->SetLabelSize(0.0425);
        deltaP->GetYaxis()->CenterTitle(true);
        deltaP->GetYaxis()->SetTitle(("#deltaP_{" + BetaParticleShort + "} = #frac{m_{" + BetaParticleShort + "}#delta#beta}{(1 - #beta^{2})^{3/2}}").c_str());
        //    deltaP->GetYaxis()->SetTitle(("#deltaP_{" + BetaParticleShort + "} = #frac{m_{" + BetaParticleShort + "}#cdot#delta#beta}{(1-#beta^{2})^{3/2}}").c_str());

        //    deltaP->SetLineColor(kBlack);
        deltaP->SetLineColor(Color);
        deltaP->Draw();
        Histogram_list->Add(deltaP);

        TPaveText *deltaPParam = new TPaveText(x_1_FitParam, y_1_FitParam - 0.05 + 0.15, x_2_FitParam, y_2_FitParam + 0.15, "NDC");
        //    TPaveText *deltaPParam = new TPaveText(x_1_FitParam, y_1_FitParam - 0.1, x_2_FitParam, y_2_FitParam, "NDC");
        //    TPaveText *deltaPParam = new TPaveText(x_1_FitParam, y_1_FitParam, x_2_FitParam, y_2_FitParam, "NDC");
        deltaPParam->SetBorderSize(1);
        deltaPParam->SetTextFont(0);
        deltaPParam->SetTextSize(0.03);
        deltaPParam->SetFillColor(0);
        deltaPParam->SetTextAlign(12);
        deltaPParam->AddText(("d#beta = " + to_string(FitStd)).c_str());
        //    deltaPParam->AddText(("#delta#beta = " + to_string_with_precision(FitStd, 8)).c_str());
        deltaPParam->Draw("same");

        string deltaPSaveNameDir =
            BetaPlot.GetHistogram1DSaveNamePath() + "Approximatied_beta/" + sNameFlag + "02a_P_" + BetaParticleShort + "_uncertainty_" + BetaPlot.GetFinalState() + ".png";
        const char *deltaPSaveDir = deltaPSaveNameDir.c_str();
        Canvas->SaveAs(deltaPSaveDir);

        Canvas->Clear();
        //</editor-fold>

        //<editor-fold desc="Solve deltaP/P for beta in range 0.9<=beta<1">
        double Beta_Max_Apprax, P_Beta_Max_Apprax, Beta_Min_Apprax, P_Beta_Min_Apprax;

        cout << "\nSolutions for deltaP/P = 20%:\n";

        Beta_Max_Apprax = sqrt(1 - FitStd / deltaPRel_UncertaintyU);
        P_Beta_Max_Apprax = m_n * Beta_Max_Apprax / sqrt(1 - Beta_Max_Apprax * Beta_Max_Apprax);

        cout << "Beta_Max_Apprax = " << Beta_Max_Apprax << " is chosen\n";
        cout << "P(Beta_Max_Apprax) = " << P_Beta_Max_Apprax << "\n\n";

        cout << "Solutions for deltaP/P = 10%:\n";

        Beta_Min_Apprax = sqrt(1 - FitStd / deltaPRel_UncertaintyL);
        P_Beta_Min_Apprax = m_n * Beta_Min_Apprax / sqrt(1 - Beta_Min_Apprax * Beta_Min_Apprax);

        cout << "Beta_Min_Apprax = " << Beta_Min_Apprax << " is chosen\n";
        cout << "P(Beta_Min_Apprax) = " << P_Beta_Min_Apprax << "\n\n";

        ////        cout << "\n\n\n\n" << BetaPlot.GetHistogram1DSaveNamePath() << "Approximatied_beta/" << "\n\n\n\n";
        //        exit(0);

        Momentum_cuts.SetUpperCut(P_Beta_Max_Apprax);
        //</editor-fold>

        //<editor-fold desc="Plot deltaP/P as function of beta">
        string Rel_deltaPStatsTitle = "#deltaP_{" + BetaParticleShort + "} (" + BetaPlot.GetFinalState() + ")";
        string Rel_deltaPTitle = BetaParticle + " relative uncertainty #deltaP_{" + BetaParticleShort + "}/P_{" + BetaParticleShort + "}" + " (apprax. ," + BetaPlot.GetFinalState() + ")";
        string Rel_deltaPfunc = to_string(FitStd) + "/ (1 - x*x)";

        auto *Rel_deltaP = new TF1(Rel_deltaPStatsTitle.c_str(), Rel_deltaPfunc.c_str(), 0.9, 1);
        Rel_deltaP->SetTitle(Rel_deltaPTitle.c_str());
        Rel_deltaP->GetXaxis()->SetTitleSize(0.06);
        Rel_deltaP->GetXaxis()->SetLabelSize(0.0425);
        Rel_deltaP->GetXaxis()->CenterTitle(true);
        Rel_deltaP->GetXaxis()->SetTitle("#beta");
        Rel_deltaP->GetYaxis()->SetRangeUser(0., 0.5);
        Rel_deltaP->GetYaxis()->SetTitleSize(0.06);
        Rel_deltaP->GetYaxis()->SetLabelSize(0.0425);
        Rel_deltaP->GetYaxis()->CenterTitle(true);
        Rel_deltaP->GetYaxis()->SetTitle(("#frac{#deltaP_{" + BetaParticleShort + "}}{P_{" + BetaParticleShort + "}} = #frac{#delta#beta}{1 - #beta^{2}}").c_str());
        Rel_deltaP->SetLineColor(kBlack);
        Rel_deltaP->SetLineWidth(2);
        Rel_deltaP->Draw();
        Histogram_list->Add(Rel_deltaP);

        TPaveText *deltaPRel_deltaP = new TPaveText(x_1_FitParam, y_1_FitParam - 0.05, x_2_FitParam, y_2_FitParam, "NDC");
        deltaPRel_deltaP->SetBorderSize(1);
        deltaPRel_deltaP->SetTextFont(0);
        deltaPRel_deltaP->SetTextSize(0.03);
        deltaPRel_deltaP->SetFillColor(0);
        deltaPRel_deltaP->SetTextAlign(12);
        deltaPRel_deltaP->AddText(("d#beta = " + to_string(FitStd)).c_str());
        deltaPRel_deltaP->Draw("same");

        TLine *upper_cut = new TLine(gPad->GetFrame()->GetX2() - 0.1, deltaPRel_UncertaintyU, gPad->GetFrame()->GetX2(), deltaPRel_UncertaintyU);
        upper_cut->SetLineWidth(2);
        upper_cut->SetLineColor(kBlue);
        upper_cut->Draw("same");

        TLine *lower_cut = new TLine(gPad->GetFrame()->GetX2() - 0.1, deltaPRel_UncertaintyL, gPad->GetFrame()->GetX2(), deltaPRel_UncertaintyL);
        lower_cut->SetLineWidth(2);
        lower_cut->SetLineColor(kRed);
        lower_cut->Draw("same");

        auto Cut_legend = new TLegend(gStyle->GetStatX(), gStyle->GetStatY() - 0.2 + 0.125, gStyle->GetStatX() - 0.2, gStyle->GetStatY() - 0.3 + 0.1);
        TLegendEntry *Cut_legend_deltaPRel_deltaP = Cut_legend->AddEntry(deltaPRel_deltaP, ("#deltaP_{" + BetaParticleShort + "}/P_{" + BetaParticleShort + "}").c_str(), "l");
        TLegendEntry *Cut_legend_upper_lim = Cut_legend->AddEntry(upper_cut, "20% cut", "l");
        TLegendEntry *Cut_legend_lower_lim = Cut_legend->AddEntry(lower_cut, "10% cut", "l");
        Cut_legend->Draw("same");

        string Rel_deltaPSaveNameDir =
            BetaPlot.GetHistogram1DSaveNamePath() + "Approximatied_beta/" + sNameFlag + "02b_P_" + BetaParticleShort + "_apprax_rel_uncertainty_" + BetaPlot.GetFinalState() + ".png";

        const Int_t n = 2;
        auto gr = new TGraph(n);
        gr->SetMarkerStyle(20);
        gr->SetMarkerSize(20);
        auto ex = new TExec("ex", "drawtext();");
        gr->GetListOfFunctions()->Add(ex);
        gr->SetPoint(0, Beta_Max_Apprax, deltaPRel_UncertaintyU);
        gr->SetPoint(1, Beta_Min_Apprax, deltaPRel_UncertaintyL);
        gr->Draw("same");

        const char *Rel_deltaPSaveDir = Rel_deltaPSaveNameDir.c_str();
        Canvas->SaveAs(Rel_deltaPSaveDir);
        Canvas->Clear();
        //</editor-fold>

    } else {
        Momentum_cuts.SetUpperCut(beamE);
    }
}

#endif  // DATA_ANALYSER_BETAFITAPPRAX_H
