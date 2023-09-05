#include<string>
#include<iostream>
#include<fstream>
#include<vector>


void histo() {

    int p = 4;
    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(0);
    gStyle->SetStatBorderSize(4);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.5); 
    gStyle->SetStatH(0.2);
    

    
    TH1F* histo = new TH1F("Geometry of phase space (N=100, p=5)", "Geometry of phase space (N=100, p=5)",p+1,0.5,1.5+p);
    histo->SetStats(kFALSE);
    histo->SetFillColor(kBlue);
    histo->SetLineColor(kBlack);
    histo->SetMarkerStyle(kFullCircle);
    histo->SetMarkerSize(0.8);
    /* histo->GetYaxis()->SetTitleOffset(1.2);
    histo->GetXaxis()->SetTitleSize(0.04);
    histo->GetYaxis()->SetTitleSize(0.04); */
    histo->GetXaxis()->SetTitle("Memories n.");
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

void graph(){
    int const N = 7;
    double successRate001N[N] = {0,0,0,13.4,19.0,27,54.1};
    double successRate005N[N] = {0,0,2.4,16.55,25.7,34.3,75.8};
    double successRate01N[N] = {0,2.5,9.9,18.5,26.6,34.8,79.3,};
    double successRate05N[N] = {12.8,24.9,44.5,65.6,73.9,82.2,97.4};
    double successRate075N[N] = {46.1,67.4,77.0,86.2,89.2,94.8,100.0};
    double memories[N]={5,8,10,12,13,15,20};
    TCanvas* c = new TCanvas(""," ",800,600);

    TGraph* graph[5];
    graph[0] = new TGraph(N,memories,successRate001N);
    graph[1] = new TGraph(N,memories,successRate005N);
    graph[2] = new TGraph(N,memories,successRate01N);
    graph[3] = new TGraph(N,memories,successRate05N);
    graph[4] = new TGraph(N,memories,successRate075N);

    for (int i = 0; i < 5; i++)
    {
    graph[i]->SetTitle("Failure Rate of the Hopfield Network");
    graph[i]->GetXaxis()->SetTitle("N. of memories stored");
    graph[i]->GetYaxis()->SetTitle("Failure rate");
    graph[i]->SetMinimum(-0.2);
    graph[i]->SetMaximum(100);
    graph[i]->SetMarkerSize(.5);
    graph[i]->SetMarkerStyle(21);
    graph[i]->SetLineWidth(2);
    }

    graph[0]->SetLineColor(kOrange);
    graph[1]->SetLineColor(kRed);
    graph[2]->SetLineColor(kBlue);
    graph[3]->SetLineColor(kGreen);
    graph[4]->SetLineColor(kBlack);

    graph[0]->Draw("ALP");
    graph[1]->Draw("LP, SAME");
    graph[2]->Draw("LP, SAME");
    graph[3]->Draw("LP, SAME");
    graph[4]->Draw("LP, SAME");

    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph[0],"Failure rate altering 1 starting neurons over 100");
    leg->AddEntry(graph[1], "Failure rate altering 5 starting neurons over 100");
    leg->AddEntry(graph[2], "Failure rate altering 10 starting neurons over 100");
    leg->AddEntry(graph[3], "Failure rate altering 50 starting neurons over 100");
    leg->AddEntry(graph[4], "Failure rate altering 75 starting neurons over 100");
    leg->Draw();
}