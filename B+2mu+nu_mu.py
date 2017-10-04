from basf2 import *
from modularAnalysis import *

# input mdst file
inputMdst('default','~/B+2mu+nu_mu/mdst/B+2mu+nu_mu_mdst.root')
fillParticleList('mu+:all','')
reconstructDecay('B+:all -> mu+:all','')
matchMCTruth('B+:all')
toolsmu = ['EventMetaData','^B+ -> ^mu+']
toolsmu += ['MCTruth','^B+ -> ^mu+']
toolsmu += ['Kinematics','^B+ -> ^mu+']
toolsmu += ['MCKinematics','^B+ -> ^mu+']
toolsmu += ['DeltaEMbc','^B+ -> mu+']
ntupleFile('~/B+2mu+nu_mu/20171004_B+2mu+nu_mu2_recons.root')
ntupleTree('muon','B+:all',toolsmu)
process(analysis_main)




#print out the summary
print(statistics)
