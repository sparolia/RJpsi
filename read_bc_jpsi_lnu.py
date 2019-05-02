import ROOT
import glob
from array import array
from collections import OrderedDict
from DataFormats.FWLite import Events, Handle
from PhysicsTools.HeppyCore.utils.deltar import deltaR, deltaPhi
from treeVariables import branches_all # here the ntuple branches are defined
from files import files_jpsi_munu
# from utils import isGenHadTau, finalDaughters, printer # utility functions


# COPY FILES FROM STORAGE
# dccp -H dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/sleontsi/PYTHIA8_BJpsimunu_13TeV_2019_02_28_1/miniAOD/miniAOD_PYTHIA8_BJpsimunu_13TeV_2019_02_28_1_65.root  .

##########################################################################################
# initialise output files to save the flat ntuples
outfile = ROOT.TFile('bc_jpsi_mu_nu_gen_2.root', 'recreate')
branches_all_names = [br.name() for br in branches_all]
ntuple = ROOT.TNtuple('tree', 'tree', ':'.join(branches_all_names))
tofill = OrderedDict(zip(branches_all_names, [-99.]*len(branches_all_names))) # initialise all branches to unphysical -99       

##########################################################################################
# Get ahold of the events
# files_jpsi_munu  = glob.glob('/pnfs/psi.ch/cms/trivcat/store/user/sleontsi/PYTHIA8_BJpsimunu_13TeV_2019_02_28_1/miniAOD/miniAOD_PYTHIA8_BJpsimunu_13TeV_2019_02_28*.root')
# files_jpsi_taunu = glob.glob('/pnfs/psi.ch/cms/trivcat/store/user/sleontsi/PYTHIA8_BJpsitaunu_13TeV_2019_02_27_1_test/miniAOD/miniAOD_PYTHIA8_BJpsitaunu_13TeV_2019_02_27*.root')

# prepend xrd bla bla
# files_jpsi_munu  = ['/'.join(['dcap://t3se01.psi.ch:22125//']+ifile.split('/')) for ifile in files_jpsi_munu ]
# files_jpsi_taunu = ['/'.join(['dcap://t3se01.psi.ch:22125//']+ifile.split('/')) for ifile in files_jpsi_taunu]

# camilla's files
# files_jpsi_taunu = ['root://cms-xrd-global.cern.ch//store/user/cgalloni/BcJpsiTauNu/Fall18_10_2_9-MINIAODSIM_noDuplCheck/190429_122926/0000/miniAOD_302.root']
# files_jpsi_munu  = ['root://cms-xrd-global.cern.ch//store/user/cgalloni/BcJpsiMuNu/Fall18_10_2_9-MINIAODSIM_noDuplCheck/190429_122725/0000/miniAOD_%d.root'%i for i in range(1,510)]

events = Events(files_jpsi_munu[2:3]) # make sure this corresponds to your file name!
maxevents = -1 # max events to process
totevents = events.size() # total number of events in the files

##########################################################################################
# instantiate the handles to the relevant collections.
# Do this *outside* the event loop
# Reminder: you can see the names of the collections stored in your input file by doing:
# edmDumpEventContent outputFULL.root

handles = OrderedDict()
handles['taus'] = ('slimmedTaus'       , Handle('std::vector<pat::Tau>')         )
handles['muon'] = ('slimmedMuons'      , Handle('std::vector<pat::Muon>')        )
handles['genp'] = ('prunedGenParticles', Handle('std::vector<reco::GenParticle>'))

# h1_mass = ROOT.TH1F('mass', '', 50, 5.8, 6.8)

masses = []

##########################################################################################
# start looping on the events
for i, ev in enumerate(events):
    
    ######################################################################################
    # controls on the events being processed
    if maxevents>0 and i>maxevents:
        break
        
    if i%100==0:
        print '===> processing %d / %d event' %(i, totevents)
    
    ######################################################################################
    # access the handles
    for k, v in handles.iteritems():
        ev.getByLabel(v[0], v[1])
        setattr(ev, k, v[1].product())
    
    try:    

        bcs = [gp for gp in ev.genp if abs(gp.pdgId())==541 and gp.statusFlags().isLastCopy()]

        ev.thebc = [ibc for ibc in bcs if any([ibc.daughter(jj) for jj in range(ibc.numberOfDaughters()) if ibc.daughter(jj).pdgId() ==443])][0]
        
#         ev.thebc   = [gp for gp in ev.genp if abs(gp.pdgId())==541 and gp.statusFlags().isLastCopy()][0]
        ev.thejpsi = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters()) if     ev.thebc.daughter(jj).pdgId() ==443][0]
        ev.themu   = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters()) if abs(ev.thebc.daughter(jj).pdgId())==13 ][0]
        ev.thenu   = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters()) if abs(ev.thebc.daughter(jj).pdgId())==14 ][0]
        mm_from_jpsi = sorted([ev.thejpsi.daughter(0), ev.thejpsi.daughter(1)], key=lambda x : x.pt(), reverse=True)
        ev.themu1 = mm_from_jpsi[0]
        ev.themu2 = mm_from_jpsi[1]
    except:
        import pdb ; pdb.set_trace()
        continue
    
    
#     import pdb ; pdb.set_trace()
    bcp4 = ev.thejpsi.p4() + ev.themu.p4() + ev.thenu.p4()
    masses.append(bcp4.mass())

#     try:
#         h1_mass.Fill(bcp4.mass())
#     except:
#         import pdb ; pdb.set_trace() 

    for ibranch in branches_all:
        tofill[ibranch.name()] = ibranch.value(ev)
    
    # fill the tree
    ntuple.Fill(array('f', tofill.values()))
        
    
##########################################################################################
# write the ntuples and close the files
outfile.cd()
ntuple.Write()
outfile.Close()

# mass.Draw()
# ROOT.gPad.SaveAs('mass.pdf')
