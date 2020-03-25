import numpy as np

class Variable(object):

    def __init__(self, name, getter):
        self._name   = name
        self._getter = getter

    def name(self):
        return self._name

    def value(self, event):
        return self._getter(event)

branches_event = [
    Variable('run'         , lambda ev : ev.eventAuxiliary().run()            ),
    Variable('lumi'        , lambda ev : ev.eventAuxiliary().luminosityBlock()),
    Variable('event'       , lambda ev : ev.eventAuxiliary().event()          ),
    Variable('pv_x'        , lambda ev : ev.thebc.vertex().x()     if hasattr(ev, 'thebc') else ev.the_pv.x()),
    Variable('pv_y'        , lambda ev : ev.thebc.vertex().y()     if hasattr(ev, 'thebc') else ev.the_pv.y()),
    Variable('pv_z'        , lambda ev : ev.thebc.vertex().z()     if hasattr(ev, 'thebc') else ev.the_pv.z()),
    Variable('trigDimuon0' , lambda ev : ev.triggerDimuon0         if hasattr(ev, 'trig') else -99.), 
    Variable('trigJpsiTk'  , lambda ev : ev.triggerJpsiTk          if hasattr(ev, 'trig') else -99.), 
]

branches_bc = [
    Variable('bc_pt'       , lambda ev : ev.thebc.pt()             if hasattr(ev, 'thebc') else -99.),
    Variable('bc_eta'      , lambda ev : ev.thebc.eta()            if hasattr(ev, 'thebc') else -99.),
    Variable('bc_phi'      , lambda ev : ev.thebc.phi()            if hasattr(ev, 'thebc') else -99.),
    Variable('bc_charge'   , lambda ev : np.sign(ev.thebc.pdgId()) if hasattr(ev, 'thebc') else -99.),
    Variable('bc_mass'     , lambda ev : ev.thebc.mass()           if hasattr(ev, 'thebc') else -99.),
]

branches_tau = [
    Variable('tau_pt'       , lambda ev : ev.thetau.pt()              if hasattr(ev, 'thetau') else -99.),
    Variable('tau_eta'      , lambda ev : ev.thetau.eta()             if hasattr(ev, 'thetau') else -99.),
    Variable('tau_phi'      , lambda ev : ev.thetau.phi()             if hasattr(ev, 'thetau') else -99.),
    Variable('tau_charge'   , lambda ev : -np.sign(ev.thetau.pdgId()) if hasattr(ev, 'thetau') else -99.),
]

branches_taunu = [
    Variable('taunu_id'     , lambda ev : ev.thetaunu.pdgId()  if hasattr(ev, 'thetaunu') else -99.),
    Variable('taunu_pt'     , lambda ev : ev.thetaunu.pt()  if hasattr(ev, 'thetaunu') else -99.),
    Variable('taunu_eta'    , lambda ev : ev.thetaunu.eta() if hasattr(ev, 'thetaunu') else -99.),
    Variable('taunu_phi'    , lambda ev : ev.thetaunu.phi() if hasattr(ev, 'thetaunu') else -99.),
]
branches_taunu = [
    Variable('taunu2_id'     , lambda ev : ev.thetaunu2.pdgId()  if hasattr(ev, 'thetaunu2') else -99.),
    Variable('taunu2_pt'     , lambda ev : ev.thetaunu2.pt()  if hasattr(ev, 'thetaunu2') else -99.),
    Variable('taunu2_eta'    , lambda ev : ev.thetaunu2.eta() if hasattr(ev, 'thetaunu2') else -99.),
    Variable('taunu2_phi'    , lambda ev : ev.thetaunu2.phi() if hasattr(ev, 'thetaunu2') else -99.),
]

branches_mu = [
    Variable('mu_pt'       , lambda ev : ev.themu.pt()             ),
    Variable('mu_eta'      , lambda ev : ev.themu.eta()            ),
    Variable('mu_phi'      , lambda ev : ev.themu.phi()            ),
    Variable('mu_charge'   , lambda ev : -np.sign(ev.themu.pdgId())),
]

branches_pi = [
    Variable('pi_pt'       , lambda ev : ev.thepi.pt()             ),
    Variable('pi_eta'      , lambda ev : ev.thepi.eta()            ),
    Variable('pi_phi'      , lambda ev : ev.thepi.phi()            ),
    Variable('pi_charge'   , lambda ev : np.sign(ev.thepi.pdgId()) ),
]

branches_munu = [
    Variable('munu_id'       , lambda ev : ev.themunu.pdgId()  if hasattr(ev, 'themunu') else -99.),
    Variable('munu_pt'       , lambda ev : ev.themunu.pt()  if hasattr(ev, 'themunu') else -99.),
    Variable('munu_eta'      , lambda ev : ev.themunu.eta() if hasattr(ev, 'themunu') else -99.),
    Variable('munu_phi'      , lambda ev : ev.themunu.phi() if hasattr(ev, 'themunu') else -99.),
]

branches_jpsi = [
    Variable('jpsi_pt'     , lambda ev : ev.thejpsi.pt()        ),
    Variable('jpsi_eta'    , lambda ev : ev.thejpsi.eta()       ),
    Variable('jpsi_phi'    , lambda ev : ev.thejpsi.phi()       ),
    Variable('jpsi_mass'   , lambda ev : ev.thejpsi.mass()      ),
    Variable('sv_x'        , lambda ev : ev.thejpsi.vertex().x()),
    Variable('sv_y'        , lambda ev : ev.thejpsi.vertex().y()),
    Variable('sv_z'        , lambda ev : ev.thejpsi.vertex().z()),
]

branches_mu1 = [
    Variable('mu1_pt'      , lambda ev : ev.themu1.pt()             ),
    Variable('mu1_eta'     , lambda ev : ev.themu1.eta()            ),
    Variable('mu1_phi'     , lambda ev : ev.themu1.phi()            ),
    Variable('mu1_charge'  , lambda ev : -np.sign(ev.themu1.pdgId())),
]

branches_mu2 = [
    Variable('mu2_pt'      , lambda ev : ev.themu2.pt()             ),
    Variable('mu2_eta'     , lambda ev : ev.themu2.eta()            ),
    Variable('mu2_phi'     , lambda ev : ev.themu2.phi()            ),
    Variable('mu2_charge'  , lambda ev : -np.sign(ev.themu2.pdgId())),
]

branches_all = branches_event + branches_bc + branches_tau + branches_taunu + branches_mu + branches_munu + branches_jpsi + branches_mu1 + branches_mu2
branches_jpsi_pi = branches_event + branches_bc + branches_pi + branches_jpsi + branches_mu1 + branches_mu2
