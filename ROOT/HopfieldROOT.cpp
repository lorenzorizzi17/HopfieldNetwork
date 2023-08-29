#include<string>
#include<iostream>
#include<fstream>


void histo() {

    int p = 5;
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

    
    std::ifstream myfile1 ("/home/lorenzo17/HopfieldNetwork/data/test1_100_5.txt", std::ifstream::in);
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

void graph(){
    int const N = 7;
    double successRate1[N] = {0,0,2.4,16.55,17.3,34.3,75.8};
    double successRate2[N] = {0,2.5,9.9,18.5,19,34.8,79.3,};
    double memories[N]={5,8,10,12,13,15,20};
    TCanvas* c = new TCanvas(""," ",800,600);
    TGraph* graph = new TGraph(N,memories,successRate1);
    graph->SetTitle("Failure Rate of the Hopfield Network");
    graph->GetXaxis()->SetTitle("N. of memories stored");
    graph->GetYaxis()->SetTitle("Failure rate");
    graph->SetMinimum(-0.2);
    graph->SetMaximum(100);
    graph->SetMarkerSize(.5);
    graph->SetMarkerStyle(21);
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);
    graph->Draw("ALP");

    TGraph* graph2 = new TGraph(N,memories,successRate2);
    graph2->SetMinimum(-0.2);
    graph2->SetMaximum(100);
    graph2->SetMarkerSize(.7);
    graph2->SetMarkerStyle(22);
    graph2->SetLineColor(kRed);
    graph2->SetLineWidth(2);
    graph2->Draw("PL,SAME");

    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph,"Failure rate altering 5 starting neurons over 100");
    leg->AddEntry(graph2, "Failure rate altering 10 starting neurons over 100");
    leg->Draw();
}