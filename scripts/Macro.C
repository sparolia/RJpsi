#include <iostream>
#include <ostream>
#include <cmath>
#include <TMath.h>
#include <TRandom2.h>
#include <TH1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TArrayD.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <math.h>
#include <TLegend.h>



using namespace std;

void Macro(){

  //declaring all the required variable for normalization channel
  float bc_pt_norm=0,bc_eta_norm=0,bc_phi_norm=0,bc_mass_norm=0;
  float mu_pt_norm=0,mu_eta_norm=0,mu_phi_norm=0;
  float mu1_pt_norm=0,mu1_eta_norm=0,mu1_phi_norm=0;
  float mu2_pt_norm=0,mu2_eta_norm=0,mu2_phi_norm=0;
  float jpsi_pt_norm=0,jpsi_eta_norm=0,jpsi_phi_norm=0,jpsi_mass_norm=0;

  //declaring all the required variable for signal channel
  float bc_pt_sig=0,bc_eta_sig=0,bc_phi_sig=0,bc_mass_sig=0;
  float mu_pt_sig=0,mu_eta_sig=0,mu_phi_sig=0;
  float mu1_pt_sig=0,mu1_eta_sig=0,mu1_phi_sig=0;
  float mu2_pt_sig=0,mu2_eta_sig=0,mu2_phi_sig=0;
  float jpsi_pt_sig=0,jpsi_eta_sig=0,jpsi_phi_sig=0,jpsi_mass_sig=0;

  
  TFile *f1 = TFile::Open("bc_jpsi_mu_nu_gen_v2.root"); //opening the normalization root file
  TTree *tree_norm = (TTree*)f1->Get("tree"); //reading the tree from the ntuple
  TFile *f2 = TFile::Open("bc_jpsi_tau_nu_gen_v2.root"); //opening the signal root file
  TTree *tree_sig = (TTree*)f2->Get("tree"); //reading the tree from the ntuple


  //reading variables from the normalization tree
  tree_norm->SetBranchAddress("bc_pt",&bc_pt_norm); 
  tree_norm->SetBranchAddress("bc_eta",&bc_eta_norm); 
  tree_norm->SetBranchAddress("bc_phi",&bc_phi_norm); 
  tree_norm->SetBranchAddress("bc_mass",&bc_mass_norm); 

  tree_norm->SetBranchAddress("mu_pt",&mu_pt_norm); 
  tree_norm->SetBranchAddress("mu_eta",&mu_eta_norm); 
  tree_norm->SetBranchAddress("mu_phi",&mu_phi_norm);

  tree_norm->SetBranchAddress("mu1_pt",&mu1_pt_norm); 
  tree_norm->SetBranchAddress("mu1_eta",&mu1_eta_norm); 
  tree_norm->SetBranchAddress("mu1_phi",&mu1_phi_norm);

  tree_norm->SetBranchAddress("mu2_pt",&mu2_pt_norm); 
  tree_norm->SetBranchAddress("mu2_eta",&mu2_eta_norm); 
  tree_norm->SetBranchAddress("mu2_phi",&mu2_phi_norm);

  tree_norm->SetBranchAddress("jpsi_pt",&jpsi_pt_norm); 
  tree_norm->SetBranchAddress("jpsi_eta",&jpsi_eta_norm); 
  tree_norm->SetBranchAddress("jpsi_phi",&jpsi_phi_norm);
  tree_norm->SetBranchAddress("jpsi_mass",&jpsi_mass_norm);

  //reading variables from the signal tree
  tree_sig->SetBranchAddress("bc_pt",&bc_pt_sig); 
  tree_sig->SetBranchAddress("bc_eta",&bc_eta_sig); 
  tree_sig->SetBranchAddress("bc_phi",&bc_phi_sig); 
  tree_sig->SetBranchAddress("bc_mass",&bc_mass_sig);

  tree_sig->SetBranchAddress("mu_pt",&mu_pt_sig); 
  tree_sig->SetBranchAddress("mu_eta",&mu_eta_sig); 
  tree_sig->SetBranchAddress("mu_phi",&mu_phi_sig);

  tree_sig->SetBranchAddress("mu1_pt",&mu1_pt_sig); 
  tree_sig->SetBranchAddress("mu1_eta",&mu1_eta_sig); 
  tree_sig->SetBranchAddress("mu1_phi",&mu1_phi_sig);

  tree_sig->SetBranchAddress("mu2_pt",&mu2_pt_sig); 
  tree_sig->SetBranchAddress("mu2_eta",&mu2_eta_sig); 
  tree_sig->SetBranchAddress("mu2_phi",&mu2_phi_sig);

  tree_sig->SetBranchAddress("jpsi_pt",&jpsi_pt_sig); 
  tree_sig->SetBranchAddress("jpsi_eta",&jpsi_eta_sig); 
  tree_sig->SetBranchAddress("jpsi_phi",&jpsi_phi_sig); 
  tree_sig->SetBranchAddress("jpsi_mass",&jpsi_mass_sig);
  

  //Defining Canvas, removing statistics and setting the legend
  auto c1 = new TCanvas("c", "c", 600,500);
  //gStyle->SetOptStat(0);
  auto* legend = new TLegend(0.7, 0.3, 0.9, 0.5);
   

  //booking the histograms
  TH1D* hmu_m2_miss_norm = new TH1D("hmu_m2_miss_norm","Missing mass squared",150,-5,10); 
  TH1D* hmu_m2_miss_sig = new TH1D("hmu_m2_miss_sig","Missing mass squared",150,-5,10);
  TH1D* hmu_Q2_norm = new TH1D("hmu_Q2_norm","Squared four momentum transfered to lepton system",500,-20,30);
  TH1D* hmu_Q2_sig = new TH1D("hmu_Q2_sig","Squared four momentum transfered to lepton system",500,-20,30);
  TH1D* hmu_Pt_miss_norm = new TH1D("hmu_Pt_miss_norm","Missing transverse momentum",200,0,20);
  TH1D* hmu_Pt_miss_sig = new TH1D("hmu_Pt_miss_sig","Missing transverse momentum",200,0,20);
  TH1D* hmu_m2_miss_corr_norm = new TH1D("hmu_m2_miss_corr_norm","Missing mass squared corrected",400,-20,20); 
  TH1D* hmu_m2_miss_corr_sig = new TH1D("hmu_m2_miss_corr_sig","Missing mass squared corrected",400,-20,20);
  TH1D* hmu_Q2_corr_norm = new TH1D("hmu_Q2_corr_norm","Squared four momentum transfered to lepton system corrected",500,-20,30);
  TH1D* hmu_Q2_corr_sig = new TH1D("hmu_Q2_corr_sig","Squared four momentum transfered to lepton system corrected",500,-20,30);
  TH1D* hmu_Pt_miss_corr_norm = new TH1D("hmu_Pt_miss_corr_norm","Missing transverse momentum corrected",500,0,50);
  TH1D* hmu_Pt_miss_corr_sig = new TH1D("hmu_Pt_miss_corr_sig","Missing transverse momentum corrected",500,0,50);
  TH1D* hmu_Pt_var_norm = new TH1D("hmu_Pt_var_norm","Tranverse variable momentum",600,-30,30);
  TH1D* hmu_Pt_var_sig = new TH1D("hmu_Pt_var_sig","Tranverse variable momentum",600,-30,30);
  TH1D* hmu_del_R_norm = new TH1D("hmu_del_R_norm","Delta R",100,0,10);
  TH1D* hmu_del_R_sig = new TH1D("hmu_del_R_sig","Delta R",100,0,10);
  TH1D* hmu_mu_pt_norm = new TH1D("hmu_mu_pt_norm","Unpaired muon tranverse momentum",200,0,20);
  TH1D* hmu_mu_pt_sig = new TH1D("hmu_mu_pt_sig","Unpaired muon tranverse momentum",200,0,20);
  TH1D* hmu_mu_eta_norm = new TH1D("hmu_mu_eta_norm","Unpaired muon psuedorapidity",200,-10,10);
  TH1D* hmu_mu_eta_sig = new TH1D("hmu_mu_eta_sig","Unpaired muon psuedorapidity",200,-10,10);
  TH1D* hmu_mu_phi_norm = new TH1D("hmu_mu_phi_norm","Unpaired muon phi",100,-5,5);
  TH1D* hmu_mu_phi_sig = new TH1D("hmu_mu_phi_sig","Unpaired muon phi",100,-5,5);
  TH1D* hmu_mu_en_bc_frame_norm = new TH1D("hmu_mu_en_bc_frame_norm","Energy of Unpaired muon in Bc rest frame",500,0,500);
  TH1D* hmu_mu_en_bc_frame_sig = new TH1D("hmu_mu_en_bc_frame_sig","Energy of Unpaired muon in Bc rest frame",500,0,500);
  TH1D* hmu_mu_en_jpsi_frame_norm = new TH1D("hmu_mu_en_jpsi_frame_norm","Energy of Unpaired muon in Jpsi rest frame",500,0,500);
  TH1D* hmu_mu_en_jpsi_frame_sig = new TH1D("hmu_mu_en_jpsi_frame_sig","Energy of Unpaired muon in Jpsi rest frame",500,0,500);
  TH1D* hmu_bc_pt_norm = new TH1D("hmu_bc_pt_norm","Transverse momentum of B_{c}",100,0,100);
  TH1D* hmu_bc_pt_sig = new TH1D("hmu_bc_pt_sig","Transverse momentum of B_{c}",100,0,100);
  TH1D* hmu_bc_pt_corr_norm = new TH1D("hmu_bc_pt_corr_norm","Corrected transverse momentum of B_{c}",100,0,100);
  TH1D* hmu_bc_pt_corr_sig = new TH1D("hmu_bc_pt_corr_sig","Corrected transverse momentum of B_{c}",100,0,100);
  auto hprof_norm  = new TProfile("hprof_norm","Profile of Transverse momentum of B_{c}",100,0,200,0,1000);
  auto hprof_sig  = new TProfile("hprof_sig","Profile of Transverse momentum of B_{c}",100,0,200,0,1000);
  TH2D* hmu_bc_pt_scatter_norm = new TH2D("hmu_bc_pt_scatter_norm","Scatter plot of transverse momentum of B_{c}",100,0,100,100,0,100);
  TH2D* hmu_bc_pt_scatter_sig = new TH2D("hmu_bc_pt_scatter_sig","Scatter plot of transverse momentum of B_{c}",100,0,100,100,0,100);
 


  //ParticleMass muonMass = 0.10565837;
  float mu_mass = 0.113428;

  //loop over events for normalized channel
  for(int i=0; i<tree_norm->GetEntries();i++){
    tree_norm->GetEntry(i);
    
    //TLorentzVector class for calculating four momenta
    TLorentzVector momntm_bc_norm;
    momntm_bc_norm.SetPtEtaPhiM(bc_pt_norm, bc_eta_norm,bc_phi_norm,bc_mass_norm);
    TLorentzVector momntm_mu1_norm;
    momntm_mu1_norm.SetPtEtaPhiM(mu1_pt_norm, mu1_eta_norm,mu1_phi_norm,mu_mass);
    TLorentzVector momntm_mu2_norm;
    momntm_mu2_norm.SetPtEtaPhiM(mu2_pt_norm, mu2_eta_norm,mu2_phi_norm,mu_mass);
    TLorentzVector momntm_mu_norm;
    momntm_mu_norm.SetPtEtaPhiM(mu_pt_norm, mu_eta_norm,mu_phi_norm,mu_mass);
    TLorentzVector momntm_jpsi_norm;
    momntm_jpsi_norm.SetPtEtaPhiM(jpsi_pt_norm, jpsi_eta_norm,jpsi_phi_norm,jpsi_mass_norm);

    //calculating the kinematic variables
    float m2_miss_norm =(momntm_bc_norm - momntm_mu1_norm - momntm_mu2_norm - momntm_mu_norm).M2();
    float Q2_norm = (momntm_bc_norm - momntm_mu1_norm - momntm_mu2_norm).M2();
    float Pt_miss_norm = (bc_pt_norm - mu1_pt_norm - mu2_pt_norm - mu_pt_norm);
    float Pt_var_norm = (jpsi_pt_norm - mu_pt_norm );
    float del_R_norm = sqrt(pow((mu1_phi_norm - mu2_phi_norm),2)+pow((mu1_eta_norm - mu2_eta_norm),2));
    float muon_system_mass_norm = (momntm_mu1_norm+momntm_mu2_norm+momntm_mu_norm).M();
    //cout << muon_system_mass_norm ;
    float muon_system_pt_norm = mu_pt_norm + mu1_pt_norm + mu2_pt_norm;
    float bc_pt_corr_norm = (bc_mass_norm * muon_system_pt_norm)/ (muon_system_mass_norm); //corrected Pt according to recipe in Jona thesis
    float bc_pt_ratio_norm = bc_pt_corr_norm/bc_pt_norm;
    
    TLorentzVector momntm_bc_corr_norm;
    momntm_bc_corr_norm.SetPtEtaPhiM(bc_pt_corr_norm, bc_eta_norm,bc_phi_norm,momntm_bc_norm.M());
    float Q2_corr_norm = (momntm_bc_corr_norm - momntm_mu1_norm - momntm_mu2_norm).M2();
    float m2_miss_corr_norm = (momntm_bc_corr_norm - momntm_mu1_norm - momntm_mu2_norm - momntm_mu_norm).M2();
    float Pt_miss_corr_norm = (bc_pt_corr_norm - mu1_pt_norm - mu2_pt_norm - mu_pt_norm);

    TVector3 X_bc_norm = momntm_bc_corr_norm.BoostVector();
    TVector3 X_jpsi_norm = momntm_jpsi_norm.BoostVector();
    TLorentzVector momntm_mu_bc_frame_norm = momntm_mu_norm;
    momntm_mu_bc_frame_norm.Boost(X_bc_norm);
    TLorentzVector momntm_mu_jpsi_frame_norm = momntm_mu_norm;
    momntm_mu_jpsi_frame_norm.Boost(X_jpsi_norm);

    float mu_en_bc_frame_norm = momntm_mu_bc_frame_norm.E();
    float mu_en_jpsi_frame_norm = momntm_mu_jpsi_frame_norm.E();
        
    //Filling the histograms

    if ((abs(mu_eta_norm) < 1.3 and mu_pt_norm > 3.3) or (1.3 < abs(mu_eta_norm) < 2.2 and mu_pt_norm > 2.9) or (2.2 < abs(mu_eta_norm) < 2.4 and mu_pt_norm > 2.4)){
      //if(mu_pt_norm > 4 and jpsi_pt_norm > 6.9){
	// and
      if(mu_pt_norm > 2 and mu1_pt_norm > 3.5 and  mu2_pt_norm > 3.5){
	hmu_m2_miss_norm->Fill(m2_miss_norm);
	hmu_Q2_norm->Fill(Q2_norm);
	hmu_Pt_miss_norm->Fill(Pt_miss_norm);
	hmu_m2_miss_corr_norm->Fill(m2_miss_corr_norm);
	hmu_Q2_corr_norm->Fill(Q2_corr_norm);
	hmu_Pt_miss_corr_norm->Fill(Pt_miss_corr_norm);
	hmu_Pt_var_norm->Fill(Pt_var_norm);
	hmu_mu_pt_norm->Fill(mu_pt_norm);
	hmu_mu_eta_norm->Fill(mu_eta_norm);
	hmu_mu_phi_norm->Fill(mu_phi_norm);
	hmu_del_R_norm->Fill(del_R_norm);
	hmu_mu_en_bc_frame_norm->Fill(mu_en_bc_frame_norm);
	hmu_mu_en_jpsi_frame_norm->Fill(mu_en_jpsi_frame_norm);
	hmu_bc_pt_norm->Fill(bc_pt_norm);
	hmu_bc_pt_corr_norm->Fill(bc_pt_corr_norm);
	hprof_norm->Fill(bc_pt_norm,bc_pt_corr_norm,bc_pt_ratio_norm);
	hmu_bc_pt_scatter_norm->Fill(bc_pt_norm,bc_pt_corr_norm);
      }
    }
  }

  //loop over events for signal channel
  for(int i=0; i<tree_sig->GetEntries();i++){
    tree_sig->GetEntry(i);

    //TLorentzVector class for calculating four momenta
    TLorentzVector momntm_bc_sig;
    momntm_bc_sig.SetPtEtaPhiM(bc_pt_sig, bc_eta_sig,bc_phi_sig,bc_mass_sig);
    TLorentzVector momntm_mu1_sig;
    momntm_mu1_sig.SetPtEtaPhiM(mu1_pt_sig, mu1_eta_sig,mu1_phi_sig,mu_mass);
    TLorentzVector momntm_mu2_sig;
    momntm_mu2_sig.SetPtEtaPhiM(mu2_pt_sig, mu2_eta_sig,mu2_phi_sig,mu_mass);
    TLorentzVector momntm_mu_sig;
    momntm_mu_sig.SetPtEtaPhiM(mu_pt_sig, mu_eta_sig,mu_phi_sig,mu_mass);
    TLorentzVector momntm_jpsi_sig;
    momntm_jpsi_sig.SetPtEtaPhiM(jpsi_pt_sig, jpsi_eta_sig,jpsi_phi_sig,jpsi_mass_sig);

    //calculating the kinematic variables
    float m2_miss_sig = (momntm_bc_sig - momntm_mu1_sig - momntm_mu2_sig - momntm_mu_sig).M2();
    float Q2_sig = (momntm_bc_sig - momntm_mu1_sig - momntm_mu2_sig).M2();
    float Pt_miss_sig = (bc_pt_sig-mu1_pt_sig-mu2_pt_sig-mu_pt_sig);
    float Pt_var_sig = (jpsi_pt_sig - mu_pt_sig );
    float del_R_sig = sqrt(pow((mu1_phi_sig - mu2_phi_sig),2)+pow((mu1_eta_sig - mu2_eta_sig),2));
    float muon_system_mass_sig = (momntm_mu1_sig+momntm_mu2_sig+momntm_mu_sig).M();
    //cout << muon_system_mass_sig ;
    float muon_system_pt_sig = mu_pt_sig + mu1_pt_sig + mu2_pt_sig;
    float bc_pt_corr_sig = (bc_mass_sig * muon_system_pt_sig)/ (muon_system_mass_sig);
    float bc_pt_ratio_sig = bc_pt_corr_sig/bc_pt_sig;

    TLorentzVector momntm_bc_corr_sig;
    momntm_bc_corr_sig.SetPtEtaPhiM(bc_pt_corr_sig, bc_eta_sig,bc_phi_sig,momntm_bc_sig.M());
    float Q2_corr_sig = (momntm_bc_corr_sig - momntm_mu1_sig - momntm_mu2_sig).M2();
    float m2_miss_corr_sig = (momntm_bc_corr_sig - momntm_mu1_sig - momntm_mu2_sig - momntm_mu_sig).M2();
    float Pt_miss_corr_sig = (bc_pt_corr_sig - mu1_pt_sig - mu2_pt_sig - mu_pt_sig);
   
    TVector3 X_bc_sig = momntm_bc_corr_sig.BoostVector();
    TVector3 X_jpsi_sig = momntm_jpsi_sig.BoostVector();
    TLorentzVector momntm_mu_bc_frame_sig = momntm_mu_sig;
    momntm_mu_bc_frame_sig.Boost(X_bc_sig);
    TLorentzVector momntm_mu_jpsi_frame_sig = momntm_mu_sig;
    momntm_mu_jpsi_frame_sig.Boost(X_jpsi_sig);
    
    float mu_en_bc_frame_sig = momntm_mu_bc_frame_sig.E();
    float mu_en_jpsi_frame_sig = momntm_mu_jpsi_frame_sig.E();
    
    //Filling the histograms
    if ((abs(mu_eta_sig) < 1.3 and mu_pt_sig > 3.3) or (1.3 < abs(mu_eta_sig) < 2.2 and mu_pt_sig > 2.9) or (2.2 < abs(mu_eta_sig) < 2.4 and mu_pt_sig > 2.4)){
      //if(mu_pt_sig > 4 and jpsi_pt_sig > 6.9)
      if(mu_pt_sig > 2 and mu1_pt_sig > 3.5 and  mu2_pt_sig > 3.5){
      hmu_m2_miss_sig->Fill(m2_miss_sig);
      hmu_Q2_sig->Fill(Q2_sig);
      hmu_Pt_miss_sig->Fill(Pt_miss_sig);
      hmu_m2_miss_corr_sig->Fill(m2_miss_corr_sig);
      hmu_Q2_corr_sig->Fill(Q2_corr_sig);
      hmu_Pt_miss_corr_sig->Fill(Pt_miss_corr_sig);
      hmu_Pt_var_sig->Fill(Pt_var_sig);
      hmu_mu_pt_sig->Fill(mu_pt_sig);
      hmu_mu_eta_sig->Fill(mu_eta_sig);
      hmu_mu_phi_sig->Fill(mu_phi_sig);
      hmu_del_R_sig->Fill(del_R_sig);
      hmu_mu_en_bc_frame_sig->Fill(mu_en_bc_frame_sig);
      hmu_mu_en_jpsi_frame_sig->Fill(mu_en_jpsi_frame_sig);
      hmu_bc_pt_sig->Fill(bc_pt_sig);
      hmu_bc_pt_corr_sig->Fill(bc_pt_corr_sig);
      hprof_sig->Fill(bc_pt_sig,bc_pt_corr_sig,bc_pt_ratio_sig);
      hmu_bc_pt_scatter_sig->Fill(bc_pt_sig,bc_pt_corr_sig);
      }
    }
  }  
  
  //Drawing Histograms

  
  //Missing mass Squared
  //float norm = hmu_m2_miss_norm->GetEntries();
  hmu_m2_miss_norm->SetLineColor(kRed);
  hmu_m2_miss_norm->GetXaxis()->SetTitle("m^{2}_{miss}[GeV^{2}]");
  hmu_m2_miss_norm->GetYaxis()->SetTitle("a.u.");
  hmu_m2_miss_norm->DrawNormalized();
  hmu_m2_miss_sig->SetLineColor(kBlue);
  hmu_m2_miss_sig->DrawNormalized("same");
  legend->AddEntry(hmu_m2_miss_norm, "#mu channel", "l");
  legend->AddEntry(hmu_m2_miss_sig, "#tau channel", "l");
  legend->Draw();
  c1->SaveAs("M2_miss.png");

  
  //Squared four momentum transfered to lepton system
  hmu_Q2_norm->SetLineColor(kRed);
  hmu_Q2_norm->GetXaxis()->SetTitle("Q^{2}[GeV^{2}]");
  hmu_Q2_norm->GetYaxis()->SetTitle("a.u.");
  hmu_Q2_norm->DrawNormalized();
  hmu_Q2_sig->SetLineColor(kBlue);
  hmu_Q2_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Q2.png");
  


  //Missing transverse momentum
  hmu_Pt_miss_norm->SetLineColor(kRed);
  hmu_Pt_miss_norm->GetXaxis()->SetTitle("P_{T}^{miss}[GeV]");
  hmu_Pt_miss_norm->GetYaxis()->SetTitle("a.u.");
  hmu_Pt_miss_norm->DrawNormalized();
  hmu_Pt_miss_sig->SetLineColor(kBlue);
  hmu_Pt_miss_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Pt_miss.png");


   //Missing mass Squared corrected
  hmu_m2_miss_corr_norm->SetLineColor(kRed);
  hmu_m2_miss_corr_norm->GetXaxis()->SetTitle("m^{2}_{miss}[GeV^{2}]");
  hmu_m2_miss_corr_norm->GetYaxis()->SetTitle("a.u.");
  hmu_m2_miss_corr_norm->DrawNormalized();
  hmu_m2_miss_corr_sig->SetLineColor(kBlue);
  hmu_m2_miss_corr_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("M2_miss_corr.png");

  
  //Squared four momentum transfered to lepton system corrected
  hmu_Q2_corr_norm->SetLineColor(kRed);
  hmu_Q2_corr_norm->GetXaxis()->SetTitle("Q^{2}[GeV^{2}]");
  hmu_Q2_corr_norm->GetYaxis()->SetTitle("a.u.");
  hmu_Q2_corr_norm->DrawNormalized();
  hmu_Q2_corr_sig->SetLineColor(kBlue);
  hmu_Q2_corr_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Q2_corr.png");
  


  //Missing transverse momentum corrected
  hmu_Pt_miss_corr_norm->SetLineColor(kRed);
  hmu_Pt_miss_corr_norm->GetXaxis()->SetTitle("P_{T}^{miss}[GeV]");
  hmu_Pt_miss_corr_norm->GetYaxis()->SetTitle("a.u.");
  hmu_Pt_miss_corr_norm->DrawNormalized();
  hmu_Pt_miss_corr_sig->SetLineColor(kBlue);
  hmu_Pt_miss_corr_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Pt_miss_corr.png");
  

  //Tranverse variable momentum
  hmu_Pt_var_norm->SetLineColor(kRed);
  hmu_Pt_var_norm->GetXaxis()->SetTitle("P_{T}^{var}[GeV]");
  hmu_Pt_var_norm->GetYaxis()->SetTitle("a.u.");
  hmu_Pt_var_norm->DrawNormalized();
  hmu_Pt_var_sig->SetLineColor(kBlue);
  hmu_Pt_var_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Pt_var.png");
  
  //Delta R
  hmu_del_R_norm->SetLineColor(kRed);
  hmu_del_R_norm->GetXaxis()->SetTitle("#Delta R(#mu_{1},#mu_{2})");
  hmu_del_R_norm->GetYaxis()->SetTitle("a.u.");
  hmu_del_R_norm->DrawNormalized();
  hmu_del_R_sig->SetLineColor(kBlue);
  hmu_del_R_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("del_R.png");


  //Unpaired muon tranverse momentum
  hmu_mu_pt_norm->SetLineColor(kRed);
  hmu_mu_pt_norm->GetXaxis()->SetTitle("P_{T}^{#mu}[GeV]");
  hmu_mu_pt_norm->GetYaxis()->SetTitle("a.u.");
  hmu_mu_pt_norm->DrawNormalized();
  hmu_mu_pt_sig->SetLineColor(kBlue);
  hmu_mu_pt_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("mu_pt.png");

  
  //Unpaired muon psuedorapidity
  hmu_mu_eta_norm->SetLineColor(kRed);
  hmu_mu_eta_norm->GetXaxis()->SetTitle("#eta^{#mu}");
  hmu_mu_eta_norm->GetYaxis()->SetTitle("a.u.");
  hmu_mu_eta_norm->DrawNormalized();
  hmu_mu_eta_sig->SetLineColor(kBlue);
  hmu_mu_eta_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("mu_eta.png");

  
  //Unpaired muon phi
  hmu_mu_phi_norm->SetLineColor(kRed);
  hmu_mu_phi_norm->GetXaxis()->SetTitle("#phi^{#mu}");
  hmu_mu_phi_norm->GetYaxis()->SetTitle("a.u.");
  hmu_mu_phi_norm->DrawNormalized();
  hmu_mu_phi_sig->SetLineColor(kBlue);
  hmu_mu_phi_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("mu_phi.png");

  
  //Energy of unpaired muon in Bc rest frame
  hmu_mu_en_bc_frame_norm->SetLineColor(kRed);
  hmu_mu_en_bc_frame_norm->GetXaxis()->SetTitle("E(#mu) in rest frame of B_{c} (GeV)");
  hmu_mu_en_bc_frame_norm->GetYaxis()->SetTitle("a.u.");
  hmu_mu_en_bc_frame_norm->DrawNormalized();
  hmu_mu_en_bc_frame_sig->SetLineColor(kBlue);
  hmu_mu_en_bc_frame_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("E_bc.png");

  //Energy of unpaired muon in Jpsi rest frame
  hmu_mu_en_jpsi_frame_norm->SetLineColor(kRed);
  hmu_mu_en_jpsi_frame_norm->GetXaxis()->SetTitle("E(#mu) in rest frame of J/(#Psi) (GeV)");
  hmu_mu_en_jpsi_frame_norm->GetYaxis()->SetTitle("a.u.");
  hmu_mu_en_jpsi_frame_norm->DrawNormalized();
  hmu_mu_en_jpsi_frame_sig->SetLineColor(kBlue);
  hmu_mu_en_jpsi_frame_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("E_jpsi.png");\

  
  //Transverse momentum of Bc
  hmu_bc_pt_norm->SetLineColor(kRed);
  hmu_bc_pt_norm->GetXaxis()->SetTitle("P_{T}^{Bc} (GeV)");
  hmu_bc_pt_norm->GetYaxis()->SetTitle("a.u.");
  hmu_bc_pt_norm->DrawNormalized();
  hmu_bc_pt_sig->SetLineColor(kBlue);
  hmu_bc_pt_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Pt_Bc.png");

  
  //Corrected transverse momentum of Bc
  hmu_bc_pt_corr_norm->SetLineColor(kRed);
  hmu_bc_pt_corr_norm->GetXaxis()->SetTitle("Corrected P_{T}^{Bc} (GeV)");
  hmu_bc_pt_corr_norm->GetYaxis()->SetTitle("a.u.");
  hmu_bc_pt_corr_norm->DrawNormalized();
  hmu_bc_pt_corr_sig->SetLineColor(kBlue);
  hmu_bc_pt_corr_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("Corr_pt_bc.png");
  

  //Scatter plot of Transverse momentum of Bc
  hmu_bc_pt_scatter_norm->SetMarkerColor(kRed);
  hmu_bc_pt_scatter_norm->GetXaxis()->SetTitle("P_{T}^{Bc} (GeV)");
  hmu_bc_pt_scatter_norm->GetYaxis()->SetTitle("Corrected P_{T}^{Bc} (GeV)");
  hmu_bc_pt_scatter_norm->DrawNormalized();
  hmu_bc_pt_scatter_sig->SetMarkerColor(kBlue);
  hmu_bc_pt_scatter_sig->DrawNormalized("same");
  legend->Draw();
  c1->SaveAs("scatter_Pt_Bc.png");


  //Profile histogram of transverse momentum of Bc
  hprof_norm->SetLineColor(kRed);
  hprof_norm->GetXaxis()->SetTitle("P_{T}^{Bc} (GeV)");
  hprof_norm->GetYaxis()->SetTitle("P_{T}^{Bc} corrected (GeV)");
  hprof_norm->Draw();
  hprof_sig->SetLineColor(kBlue);
  hprof_sig->Draw("same");
  legend->Draw();
  c1->SaveAs("Profile_pt_bc.png");
  
  
  //Comparison of Bc Pt and corrected Bc Pt
  hmu_bc_pt_norm->SetLineColor(kRed);
  hmu_bc_pt_norm->GetXaxis()->SetTitle("Corrected P_{T}^{Bc} (GeV)");
  hmu_bc_pt_norm->GetYaxis()->SetTitle("a.u.");
  hmu_bc_pt_norm->DrawNormalized();
  hmu_bc_pt_sig->SetLineColor(kBlue);
  hmu_bc_pt_sig->DrawNormalized("same");
  hmu_bc_pt_corr_norm->SetLineColor(kGreen);
  hmu_bc_pt_corr_norm->DrawNormalized("same");
  hmu_bc_pt_corr_sig->SetLineColor(kYellow);
  hmu_bc_pt_corr_sig->DrawNormalized("same");
  legend->AddEntry(hmu_bc_pt_corr_norm, "#mu channel_corr", "l");
  legend->AddEntry(hmu_bc_pt_corr_sig, "#tau channel_corr", "l");
  legend->Draw();
  c1->SaveAs("Compare_pt_bc.png");


  //Closing the files
  f1->Close();
  f2->Close();
  
}
