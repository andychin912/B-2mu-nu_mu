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
cutAndCopyList('mu-:impactp','mu-:highP','abs(d0)<0.5 and abs(z0)<2 ')
cutAndCopyList('mu-:pid','mu-:impactp','eid>0.5 or muid>0.9 ')
reconstructDecay('B-:good -> mu-:pid','')

# MC truth matching
matchMCTruth('B+:good')

# NTuple maker
toolsmu = ['EventMetaData','^B- -> ^mu-']
toolsmu += ['MCTruth','^B- -> ^mu-']
toolsmu += ['Kinematics','^B- -> ^mu-']
toolsmu += ['MCKinematics','^B- -> ^mu-']
toolsmu += ['DeltaEMbc','^B- -> mu-']
toolsmu += ['CustomFloats[d0]','B- -> ^mu-']
toolsmu += ['CustomFloats[z0]','B- -> ^mu-']
toolsmu += ['CustomFloats[muid]','B- -> ^mu-']
toolsmu += ['CustomFloats[eid]','B- -> ^mu-']


ntupleFile('~/B+2mu+nu_mu/20171011_B+2mu+nu_mu_4_pid.root')
ntupleTree('muon','B-:good',toolsmu)

#processing
process(analysis_main)




#print out the summary
print(statistics)
