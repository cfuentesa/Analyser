void write_tree()
{
    gSystem->Load("libClasBanks.so");
    gSystem->Load("libClasTool.so");
    gSystem->Load("libTIdentificator.so");
   

    TClasTool *input = new TClasTool();

    input->InitDSTReader("ROOTDSTR");
    input->AddFile("clas_42011_01_1.pass2.root");

    TIdentificator *t = new TIdentificator(input);

    Int_t nEntries = input->GetEntries();

    TFile *output = new TFile("particle_data.root", "RECREATE", "Data of particles");
    TTree *tree = new TTree("data", "Tree that holds the data");

    Double_t betta, moment;
    Int_t id;

    tree->Branch("betta", &betta, "betta/D");
    tree->Branch("moment", &moment, "moment/D");
    tree->Branch("particle", &id, "id/I");

    input->Next();

    for (Int_t k = 0; k < nEntries; k++) {
        Int_t nRows = input->GetNRows("EVNT");
        for (Int_t i = 0; i < nRows; i++) {
            TString category = t->GetCategorization(i);
            if (category == "electron")
                id = 1;
            else if (category == "high energy pion +")
                id = 2;
            else if (category == "low energy pion +")
                id = 3;
            else if (category == "low energy proton")
                id = 4;
            else if (category == "positron")
                id = 5;
            else
                id = 0;
            moment = t->Momentum(i);
            betta = t->Betta(i);
            tree->Fill();
        }
        input->Next();
    };

    output->Write();
    output->Close();
    cout << "Done." << endl;
}
