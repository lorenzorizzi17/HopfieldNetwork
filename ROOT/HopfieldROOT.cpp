#include<string>
#include<iostream>
#include<fstream>


void test1() {
    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(0);
    gStyle->SetStatBorderSize(4);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.5); 
    gStyle->SetStatH(0.2);

    
    TH1F* histo = new TH1F("", "",5,0.5,5.5);
    histo->SetFillColor(kBlue);
    histo->SetLineColor(kBlack);
    histo->SetMarkerStyle(kFullCircle);
    histo->SetMarkerSize(0.8);
    /* histo->GetYaxis()->SetTitleOffset(1.2);
    histo->GetXaxis()->SetTitleSize(0.04);
    histo->GetYaxis()->SetTitleSize(0.04); */
    histo->GetXaxis()->SetTitle("N.of cars");
    histo->GetYaxis()->SetTitle("Occurrences");
    histo->StatOverflows(true);
    histo->SetLabelSize(0.04);

    
    std::ifstream myfile1 ("/home/lorenzo17/HopfieldNetwork/source/test1.txt", std::ifstream::in);
    while(myfile1.good()){
        double x = 0;
        myfile1 >> x;
        std::cerr << x << '\n';
        histo->Fill(x);
    }
    histo->Draw();
    myfile1.close();
}