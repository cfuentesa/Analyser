#include "Riostream.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TIdentificator.h"
#include "TClasTool.h"


int main(int argc, char **argv)
{
    gROOT->Reset();

    TClasTool *f = new TClasTool();

    f->InitDSTReader("ROOTDSTR");
    f->AddFile("clas_42011_01_1.pass2.root");
    TIdentificator *t = new TIdentificator(f);
    f->Next();
    Int_t n = f->GetEntries();

    TH2F *h1 = new TH2F("electron", "Betta vs Momentum", 50, 0.0, 5.0, 50, 0.0, 1.2);
    TH2F *h2 = new TH2F("he_pion", "Betta vs Momentum", 50, 0.0, 5.0, 50, 0.0, 1.2);
    TH2F *h3 = new TH2F("le_pion", "Betta vs Momentum", 50, 0.0, 5.0, 50, 0.0, 1.2);
    TH2F *h4 = new TH2F("le_proton", "Betta vs Momentum", 50, 0.0, 5.0, 50, 0.0, 1.2);
    TH2F *h5 = new TH2F("positron", "Betta vs Momentum", 50, 0.0, 5.0, 50, 0.0, 1.2);

    TFile *file = new TFile("particle_histograms.root","RECREATE","Histograms of particles");

    for (int k = 0; k < n; k++) {
        int nr = f->GetNRows("EVNT");
        for (int i = 0; i < nr; i++) {
            if (t->GetCategorization(i) == "electron")
                h1->Fill(t->Moment(i), t->Betta(i));
            else if (t->GetCategorization(i) == "high energy pion +")
                h2->Fill(t->Moment(i), t->Betta(i));
            else if (t->GetCategorization(i) == "low energy pion +")
                h3->Fill(t->Moment(i), t->Betta(i));
            else if (t->GetCategorization(i) == "low energy proton")
                h4->Fill(t->Moment(i), t->Betta(i));
            else if (t->GetCategorization(i) == "positron")
                h5->Fill(t->Moment(i), t->Betta(i));
        }
        f->Next();
    };

    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();
    file->Close();

    cout << "Done." << endl;

    TCanvas *c = new TCanvas("c", "Histograms", 1280, 800);
    c->Divide(2, 3);    

    c->cd(1);
    h1->Draw();
    c->cd(2);
    h5->Draw();
    c->cd(3);
    h2->Draw();
    c->cd(4);
    h3->Draw();
    c->cd(5);
    h4->Draw();

    return 0;
}
