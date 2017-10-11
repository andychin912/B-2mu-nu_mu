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
loadStdPi0()
loadStdKS()
loadStdD0()
loadStdDplus()
loadStdDstar0()
loadStdDstarPlus()

# skim
cutAndCopyList('mu-:highP','mu-:all','p>2.0',True)
reconstructDecay('B+:L -> mu+:highP','')

# event selection
cutAndCopyList('mu-:impactp','mu-:highP','abs(d0)<0.5 and abs(z0)<2')
reconstructDecay('B-:Im -> mu-:impactp','')

# MC truth matching
matchMCTruth('B+:Im')

# NTuple maker
toolsmu = ['EventMetaData','^B- -> ^mu-']
toolsmu += ['MCTruth','^B- -> ^mu-']
toolsmu += ['Kinematics','^B- -> ^mu-']
toolsmu += ['MCKinematics','^B- -> ^mu-']
toolsmu += ['DeltaEMbc','^B- -> mu-']
toolsmu += ['CustomFloats[d0]','B- -> ^mu-']
toolsmu += ['CustomFloats[z0]','B- -> ^mu-']

ntupleFile('~/B+2mu+nu_mu/20171011_B+2mu+nu_mu_2_impact.root')
ntupleTree('muon','B-:Im',toolsmu)

#processing
process(analysis_main)




#print out the summary
print(statistics)
