import ROOT
import glob
from time import time
from datetime import datetime, timedelta
from array import array
from collections import OrderedDict
from DataFormats.FWLite import Events, Handle
from PhysicsTools.HeppyCore.utils.deltar import deltaR, deltaPhi
from treeVariables import branches_all # here the ntuple branches are defined
from files import files_jpsi_munu, files_jpsi_taunu
# from IPython.parallel import Client
# from utils import isGenHadTau, finalDaughters, printer # utility functions

# COPY FILES FROM STORAGE
# dccp -H dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/sleontsi/PYTHIA8_BJpsimunu_13TeV_2019_02_28_1/miniAOD/miniAOD_PYTHIA8_BJpsimunu_13TeV_2019_02_28_1_65.root  .

# possible channels: mu, tau
# channel = 'tau'
channel = 'mu'

##########################################################################################
# initialise output files to save the flat ntuples
if channel == 'mu' : outfile = ROOT.TFile('bc_jpsi_mu_nu_gen_v2.root' , 'recreate')
if channel == 'tau': outfile = ROOT.TFile('bc_jpsi_tau_nu_gen_v2.root', 'recreate')
branches_all_names = [br.name() for br in branches_all]
ntuple = ROOT.TNtuple('tree', 'tree', ':'.join(branches_all_names))
tofill = OrderedDict(zip(branches_all_names, [-99.]*len(branches_all_names))) # initialise all branches to unphysical -99       

##########################################################################################
# Get ahold of the events
files = files_jpsi_munu if channel=='mu' else files_jpsi_taunu
events = Events(files)
# events = Events('miniAOD_1_muon.root')
maxevents = -1 
maxevents = maxevents if maxevents>=0 else events.size() # total number of events in the files
totevents = events.size() # total number of events in the files

##########################################################################################
# instantiate the handles to the relevant collections.
handles = OrderedDict()
handles['taus' ] = ('slimmedTaus'       , Handle('std::vector<pat::Tau>')              )
handles['muon' ] = ('slimmedMuons'      , Handle('std::vector<pat::Muon>')             )
handles['genp' ] = ('prunedGenParticles', Handle('std::vector<reco::GenParticle>')     )
handles['trig' ] = (('TriggerResults','','HLT'),  Handle('edm::TriggerResults')     )
# handles['genpk'] = ('packedGenParticles', Handle('std::vector<pat::PackedGenParticle>'))

##########################################################################################
# start looping on the events
start = time()
for i, ev in enumerate(events):
    
    ######################################################################################
    # controls on the events being processed
    if maxevents>0 and i>maxevents:
        break
        
    if i%100==0:
        percentage = float(i)/maxevents*100.
        speed = float(i)/(time()-start)
        eta = datetime.now() + timedelta(seconds=(maxevents-i) / max(0.1, speed))
        print '===> processing %d / %d event \t completed %.1f%s \t %.1f ev/s \t ETA %s s' %(i, maxevents, percentage, '%', speed, eta.strftime('%Y-%m-%d %H:%M:%S'))
        
    ######################################################################################
    # access the handles
    for k, v in handles.iteritems():
        ev.getByLabel(v[0], v[1])
        setattr(ev, k, v[1].product())
    
    try:    
        # Trigger results
        triggernames = ev.object().triggerNames(ev.trig)
        trigJpsiTk = "HLT_DoubleMu4_JpsiTrk_Displaced_v"
        trigDimuon0 = "HLT_Dimuon0_Jpsi3p5_Muon2_v"
       
        ev.triggerDimuon0 = [float(ev.trig.accept(i)) for i in xrange(ev.trig.size()) if trigDimuon0 in  triggernames.triggerName(i)][0]
        ev.triggerJpsiTk = [float(ev.trig.accept(i)) for i in xrange(ev.trig.size()) if trigJpsiTk in  triggernames.triggerName(i)][0]

        # only take the positive Bc, as that is what EVTGEN creates. If there is more than one Bc, it's because of PYTHIA hadronization
        bcs = [gp for gp in ev.genp if gp.pdgId()==541 and gp.statusFlags().isLastCopy()]
        ev.thebc = [ibc for ibc in bcs if any([ibc.daughter(jj) for jj in range(ibc.numberOfDaughters()) if ibc.daughter(jj).pdgId()==443 and abs(ibc.daughter(jj).daughter(0).pdgId())==13])][0] 
        ev.thejpsi = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters()) if     ev.thebc.daughter(jj).pdgId() ==443][0]
       
        if channel=='mu':
            ev.themu   = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters()) if abs(ev.thebc.daughter(jj).pdgId())==13 ][0]
            ev.themunu = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters()) if abs(ev.thebc.daughter(jj).pdgId())==14 ][0]

        if channel=='tau':
            ev.thetau   = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters())  if abs(ev.thebc.daughter(jj).pdgId())==15 ][0]
            ev.thetaunu = [ev.thebc.daughter(jj) for jj in range(ev.thebc.numberOfDaughters())  if abs(ev.thebc.daughter(jj).pdgId())==16 ][0]
            # the following two lines may fail for non-muonic tau decays
            ev.themu    = [ev.thetau.daughter(jj) for jj in range(ev.thetau.numberOfDaughters()) if abs(ev.thetau.daughter(jj).pdgId())==13 ][0]
            ev.themunu  = [ev.thetau.daughter(jj) for jj in range(ev.thetau.numberOfDaughters()) if abs(ev.thetau.daughter(jj).pdgId())==14 ][0]

        mm_from_jpsi = sorted([ev.thejpsi.daughter(0), ev.thejpsi.daughter(1)], key=lambda x : x.pt(), reverse=True)
        ev.themu1 = mm_from_jpsi[0]
        ev.themu2 = mm_from_jpsi[1]
    except:
#         import pdb ; pdb.set_trace()
#         print '\t\t=============================> event', ev.eventAuxiliary().event()
        continue
    
#     import pdb ;  pdb.set_trace()    
    
    for ibranch in branches_all:
        tofill[ibranch.name()] = ibranch.value(ev)
    
    # fill the tree
    ntuple.Fill(array('f', tofill.values()))
        
    
##########################################################################################
# write the ntuples and close the files
outfile.cd()
ntuple.Write()
outfile.Close()

