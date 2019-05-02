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
]

branches_bc = [
    Variable('bc_pt'       , lambda ev : ev.thebc.pt()            ),
    Variable('bc_eta'      , lambda ev : ev.thebc.eta()           ),
    Variable('bc_phi'      , lambda ev : ev.thebc.phi()           ),
    Variable('bc_charge'   , lambda ev : np.sign(ev.thebc.pdgId())),
    Variable('bc_mass'     , lambda ev : ev.thebc.mass()          ),
]

branches_mu = [
    Variable('mu_pt'       , lambda ev : ev.themu.pt()             ),
    Variable('mu_eta'      , lambda ev : ev.themu.eta()            ),
    Variable('mu_phi'      , lambda ev : ev.themu.phi()            ),
    Variable('mu_charge'   , lambda ev : -np.sign(ev.themu.pdgId())),
]

branches_nu = [
    Variable('nu_pt'       , lambda ev : ev.thenu.pt()  ),
    Variable('nu_eta'      , lambda ev : ev.thenu.eta() ),
    Variable('nu_phi'      , lambda ev : ev.thenu.phi() ),
]

branches_jpsi = [
    Variable('jpsi_pt'     , lambda ev : ev.thejpsi.pt()   ),
    Variable('jpsi_eta'    , lambda ev : ev.thejpsi.eta()  ),
    Variable('jpsi_phi'    , lambda ev : ev.thejpsi.phi()  ),
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

branches_all = branches_event + branches_bc + branches_mu + branches_nu + branches_jpsi + branches_mu1 + branches_mu2
