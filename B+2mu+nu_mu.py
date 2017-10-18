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
cutAndCopyList('mu-:highP','mu-:all','',True)
reconstructDecay('B+:L -> mu+:highP','useCMSFrame(p)>2.0')

# event selection
cutAndCopyList('mu-:impactp','mu-:highP','abs(d0)<0.5 and abs(z0)<2 ')
cutAndCopyList('mu-:pid','mu-:impactp','eid>0.5 or muid>0.9 ')
reconstructDecay('B-:good -> mu-:pid','')

# MC truth matching
matchMCTruth('B+:good')

#udst file
#particlelist = ['p+:all','p+:loose','e+:all','e+:loose','mu+:pid','pi+:all','pi+:loose','K+:all','K+:loose','pi0:all','K_S0:all','B+:good']
#outputUdst('20171012_B+2mu+nu_mu_Udst.root',particlelist)

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


ntupleFile('~/B+2mu+nu_mu/20171018_B+2mu+nu_mu_3_CMSframe.root')
ntupleTree('muon','B-:good',toolsmu)

#processing
process(analysis_main)




#print out the summary
print(statistics)
