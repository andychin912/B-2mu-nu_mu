from basf2 import *
from modularAnalysis import *

# input mdst file
inputMdst('default','~/B+2mu+nu_mu/mdst/B+2mu+nu_mu_mdst.root')

fillParticleList('mu+:all','')

matchMCTruth('mu+:all')
toolsmu = ['EventMetaData','^mu+']
toolsmu += ['MCTruth','^mu+']
ntupleFile('B+2mu+nu_mu.root')
ntupleTree('muon','mu+:all',toolsmu)
process(analysis_main)
#print out the summary
print(statistics)
