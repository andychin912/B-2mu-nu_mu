from basf2 import *
from modularAnalysis import *
from stdCharged import *
from stdPi0s import *
from stdV0s import *
from stdCharm import *

# input mdst file
inputMdst('default','~/B+2mu+nu_mu/mdst/B+2mu+nu_mu_mdst.root')

# load particles
loadStdCharged()
#loadStdPi0()
#loadStdKS()
#loadStdD0()
#loadStdDplus()
#loadStdDstar0()
#loadStdDstarPlus()

# skim
reconstructDecay('B+:all -> mu+:all','')

# event selection

# MC truth matching
matchMCTruth('B+:all')

#udst file
particlelist = ['B+:all']
skimOutputUdst('RootOutput',particlelist)

# NTuple maker
toolsmu = ['EventMetaData','^B- -> ^mu-']
toolsmu += ['MCTruth','^B- -> ^mu-']
toolsmu += ['Kinematics','^B- -> ^mu-']
toolsmu += ['MCKinematics','^B- -> ^mu-']
toolsmu += ['DeltaEMbc','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(E):useCMSFrame(px):useCMSFrame(py):useCMSFrame(pz):useCMSFrame(p)]','^B- -> ^mu-']
toolsmu += ['CustomFloats[d0]','B- -> ^mu-']
toolsmu += ['CustomFloats[z0]','B- -> ^mu-']
toolsmu += ['CustomFloats[muid]','B- -> ^mu-']
toolsmu += ['CustomFloats[eid]','B- -> ^mu-']


ntupleFile('~/B+2mu+nu_mu/temp/20181018_eeccbar_noskim.root')
ntupleTree('muon','B-:all',toolsmu)

#processing
process(analysis_main)




#print out the summary
print(statistics)
