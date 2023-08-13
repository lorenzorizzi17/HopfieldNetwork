#include<string>
#include<iostream>
#include<fstream>


void HopfieldROOT() {

    int p = 4;
    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(0);
    gStyle->SetStatBorderSize(4);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.5); 
    gStyle->SetStatH(0.2);

    
    TH1F* histo = new TH1F("", "",p+1,0.5,1.5+p);
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

    
    std::ifstream myfile1 ("/home/lorenzo17/HopfieldNetwork/data/test1_100_4.txt", std::ifstream::in);
    while(myfile1.good()){
        double x = 0;
        myfile1 >> x;
        histo->Fill(x);
    }
    for (int i = 1; i <= p+1; i++)
    {
        std::cout << "Content of bin n." << i <<": " <<histo->GetBinContent(i) <<'\n';
    }
    
    histo->Draw();

    myfile1.close();
}