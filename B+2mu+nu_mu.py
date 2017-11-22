from basf2 import *
basf2.fw.add_module_search_path(".")
basf2.register_module("EnableMyVariables")
from modularAnalysis import *
from stdCharged import *
from stdPi0s import *
from stdV0s import *
from stdCharm import *
from variables import variables

variables.addAlias('KsDaughterprid','formula(daughter(1,prid)+daughter(0,prid))')
variables.addAlias('goodKs','extraInfo(goodKs)')
# input mdst file
inputMdst('default','~/B+2mu+nu_mu/Udst/20171025_4_B+2mu+nu_mu_Udst.root.udst.root')

# particle identification
stdKshorts()

cutAndCopyList('K_S0:impact','K_S0:all','abs(d0)<0.5 and abs(z0)<2')
matchMCTruth('K_S0:all')

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
toolsmu += ['CustomFloats[Kid]','B- -> ^mu-']
toolsmu += ['CustomFloats[piid]','B- -> ^mu-']

toolsKs = ['MCTruth','^K_S0']
toolsKs += ['Kinematics','^K_S0']
toolsKs += ['CustomFloats[PDaughterMomentum:NDaughterMomentum]','^K_S0']
toolsKs += ['CustomFloats[cosAngleBetweenMomentumAndVertexVector]','^K_S0']
toolsKs += ['CustomFloats[dr]','^K_S0']
toolsKs += ['CustomFloats[KsDaughterprid]','^K_S0']
toolsKs += ['CustomFloats[daughterAngle(0,1)]','^K_S0']
toolsKs += ['CustomFloats[V0Deltad0]','^K_S0']
toolsKs += ['CustomFloats[V0Deltaz0]','^K_S0']
toolsKs += ['CustomFloats[goodKs]','^K_S0']

ntupleFile('~/B+2mu+nu_mu/temp/20171122_B+2mu+nu_mu_1_100.root')
ntupleTree('muon','B-:good',toolsmu)
ntupleTree('Ks','K_S0:all',toolsKs)

#processing
process(analysis_main)




#print out the summary
print(statistics)
