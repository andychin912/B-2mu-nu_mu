from basf2 import *
from modularAnalysis import *
from stdCharged import *
from stdPi0s import *
from stdV0s import *
from stdCharm import *

# input mdst file
inputMdst('default','~/B+2mu+nu_mu/Udst/20171025_4_B+2mu+nu_mu_Udst.root.udst.root')


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


ntupleFile('~/B+2mu+nu_mu/20171101_B+2mu+nu_mu_1.root')
ntupleTree('muon','B-:good',toolsmu)

#processing
process(analysis_main)




#print out the summary
print(statistics)
