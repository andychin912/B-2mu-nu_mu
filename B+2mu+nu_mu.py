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

# reconstrucion


# MC truth matching
matchMCTruth('B+:L')

# NTuple maker
toolsmu = ['EventMetaData','^B- -> ^mu-']
toolsmu += ['MCTruth','^B- -> ^mu-']
toolsmu += ['Kinematics','^B- -> ^mu-']
toolsmu += ['MCKinematics','^B- -> ^mu-']
toolsmu += ['DeltaEMbc','^B- -> mu-']
ntupleFile('~/B+2mu+nu_mu/20171004_B+2mu+nu_mu2_2_skim.root')
ntupleTree('muon','B-:L',toolsmu)

#processing
process(analysis_main)




#print out the summary
print(statistics)
