from basf2 import *
fw.add_module_search_path("./myModules")
register_module("EnableMyVariables")
from modularAnalysis import *
from stdCharged import *
from stdPi0s import *
from stdV0s import *
from stdCharm import *
from stdPhotons import *
from variables import variables
import sys
import argparse

#------------Parses the command line options of the fei and returns the corresponding arguments.--------
parser = argparse.ArgumentParser()
parser.add_argument('-train', '--train_data', dest='train_data', type=str, required=False, choices=['Ks','Gm'], action='append', nargs='+',
                    help='Create training data')
parser.add_argument('-out', '--outputfile', dest='outputfile', type=str, default='~/B+2mu+nu_mu/20180123_B+2mu+nu_mu_1.root',
                    help='Name of the outputted file')
args = parser.parse_args()

#-------------------------------------------Input mdst file---------------------------------------------
inputMdstList('default',['~/B+2mu+nu_mu/Udst/20171025_4_B+2mu+nu_mu_Udst.root.udst.root'])

#--------------------------------------Particle identification------------------------------------------
#Kshorts identification
"""Load Kshorts"""
stdKshorts()
cutAndCopyList('K_S0:V0mass','K_S0:all','M<0.518 and M>0.478')
matchMCTruth('K_S0:V0mass')

"""Create file for training"""
toolsKstrain = ['MCTruth','^K_S0']
toolsKstrain += ['CustomFloats[isSignal]','^K_S0']
toolsKstrain += ['Kinematics','^K_S0']
toolsKstrain += ['CustomFloats[lambdaMass]','^K_S0']
toolsKstrain += ['CustomFloats[shorterdr]','^K_S0']
toolsKstrain += ['CustomFloats[longerdr]','^K_S0']
toolsKstrain += ['CustomFloats[M]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,nCDCHits):daughter(1,nCDCHits)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,nSVDHits):daughter(1,nSVDHits)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,pionID):daughter(1,pionID)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,protonID):daughter(1,protonID)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,cosTheta):daughter(1,cosTheta)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,p):daughter(1,p)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,px):daughter(0,py):daughter(0,pz):daughter(1,px):daughter(1,py):daughter(1,pz)]','^K_S0']
toolsKstrain += ['CustomFloats[cosAngleBetweenMomentumAndVertexVector]','^K_S0']
toolsKstrain += ['CustomFloats[dr]','^K_S0']
toolsKstrain += ['CustomFloats[decayAngle(0):decayAngle(1)]','^K_S0']
toolsKstrain += ['CustomFloats[V0Deltad0]','^K_S0']
toolsKstrain += ['CustomFloats[V0Deltaz0]','^K_S0']
toolsKstrain += ['CustomFloats[d0]','^K_S0']
toolsKstrain += ['CustomFloats[dphi]','^K_S0']

"""Cut using FOM of training results"""
if args.train_data is None:
   analysis_main.add_module('MVAExpert',listNames=['K_S0:V0mass'],extraInfoName='KsFastBDT',identifier='KsIdentifier')   
   cutAndCopyList('K_S0:V0good','K_S0:V0mass','extraInfo(KsFastBDT)>0.39')
else:
   cutAndCopyList('K_S0:V0good','K_S0:V0mass','')

#Converted photons identification
"""Load gamma"""
fillConvertedPhotonsList('gamma:V0all','',True)
vertexKFit('gamma:V0all', 0.0, '', '')
cutAndCopyList('gamma:V0mass','gamma:V0all','M>-0.04 and M<0.25 and formula(daughter(0,electronID)+daughter(1,electronID))>=1.0')
matchMCTruth('gamma:V0mass')

"""Create file for training"""
#analysis_main.add_module('ParticleMCDecayString',listName='gamma:V0mass')
toolsgmtrain = ['EventMetaData','^gamma']
toolsgmtrain += ['MCTruth','^gamma']
#toolsgmtrain += ['MCDecayString','^gamma']
toolsgmtrain += ['CMSKinematics','^gamma']
toolsgmtrain += ['Kinematics','^gamma']
toolsgmtrain += ['CustomFloats[pxErr:pyErr:pzErr:ptErr]','^gamma']
toolsgmtrain += ['CustomFloats[M]','^gamma']
toolsgmtrain += ['CustomFloats[isSignal]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,electronID):daughter(1,electronID)]','^gamma']
toolsgmtrain += ['CustomFloats[shorterdr]','^gamma']
toolsgmtrain += ['CustomFloats[longerdr]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,nCDCHits):daughter(1,nCDCHits)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,nSVDHits):daughter(1,nSVDHits)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,cosTheta):daughter(1,cosTheta)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,p):daughter(1,p)]','^gamma']
toolsgmtrain += ['CustomFloats[cosAngleBetweenMomentumAndVertexVector]','^gamma']
toolsgmtrain += ['CustomFloats[dr:dx:dy:dz]','^gamma']
toolsgmtrain += ['CustomFloats[decayAngle(0):decayAngle(1)]','^gamma']
toolsgmtrain += ['CustomFloats[V0Deltad0]','^gamma']
toolsgmtrain += ['CustomFloats[V0Deltaz0]','^gamma']
toolsgmtrain += ['CustomFloats[dphi]','^gamma']


"""Cut using FOM of training results"""
if args.train_data is None:
   analysis_main.add_module('MVAExpert',listNames=['gamma:V0mass'],extraInfoName='GmFastBDT',identifier='GmIdentifier')
   cutAndCopyList('gamma:V0good','gamma:V0mass','extraInfo(GmFastBDT)>0.44')
else:
   cutAndCopyList('gamma:V0good','gamma:V0mass','')

#Photon identification
"""Load gamma"""
stdPhotons('tight')

"""Create gamma ntuple"""
toolsgmECL = ['EventMetaData','^gamma']
toolsgmECL += ['MCTruth','^gamma']
toolsgmECL += ['CustomFloats[E:cosTheta:isSignal]','^gamma']

#Charged particle identification
"""Load charged particle"""
stdMu('95eff')
stdE('99eff')
stdPr()
stdK()
stdPi()

#----------------------------------------multiple candidate selection of B-:good---------------------------
rankByHighest('B-:good','useCMSFrame(p)',1,'signalSelection')

#------------------------------------------Mbc and deltaE cut----------------------------------------------
#reconstruct B:tag
#inclusiveBtagReconstruction('Upsilon(4S):lnuskim','B-:good','B-:tag',['K_S0:V0good','gamma:V0good','gamma:tight','mu+:95eff','e+:99eff','pi+:95eff','K+:95eff','p+:95eff'])
btag = register_module('MyInclusiveBtagReconstruction')
btag.set_name('MyInclusiveBtagReconstruction_' + 'B-:good')
btag.param('upsilonListName', 'Upsilon(4S):lnuskim')
btag.param('bsigListName', 'B-:good')
btag.param('btagListName', 'B-:tag')
btag.param('inputListsNames', ['K_S0:V0good','gamma:V0good','gamma:tight','mu+:95eff','e+:99eff','pi+:95eff','K+:95eff','p+:95eff'])
analysis_main.add_module(btag)

matchMCTruth('B-:tag')

#-------------------------------------------------NTuple maker---------------------------------------------
"""signal side"""
toolsmu = ['EventMetaData','^B- -> ^mu-']
toolsmu += ['MCTruth','^B- -> ^mu-']
toolsmu += ['Kinematics','^B- -> ^mu-']
toolsmu += ['MCKinematics','^B- -> ^mu-']
toolsmu += ['DeltaEMbc','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(E):useCMSFrame(px):useCMSFrame(py):useCMSFrame(pz):useCMSFrame(p)]','^B- -> ^mu-']
toolsmu += ['CustomFloats[d0]','B- -> ^mu-']
toolsmu += ['CustomFloats[z0]','B- -> ^mu-']
toolsmu += ['CustomFloats[muonID]','B- -> ^mu-']
toolsmu += ['CustomFloats[electronID]','B- -> ^mu-']
toolsmu += ['CustomFloats[kaonID]','B- -> ^mu-']
toolsmu += ['CustomFloats[pionID]','B- -> ^mu-']

"""tag side"""
#analysis_main.add_module('ParticleMCDecayString',listName='B-:tag')
toolsBtag = ['EventMetaData','^B-']
toolsBtag += ['DeltaEMbc','^B-']
#toolsBtag += ['MCDecayString','^B-']
toolsBtag += ['MCTruth','^B-']

"""ntuple maker"""
ntupleFile(args.outputfile)
if args.train_data == [['Gm']]:
   ntupleTree('Gm','gamma:V0mass',toolsgmtrain)
elif args.train_data == [['Ks']]:
   ntupleTree('Ks','K_S0:V0mass',toolsKstrain)
elif args.train_data is None:
   #ntupleTree('Gm','gamma:tight',toolsgmECL)
   ntupleTree('muon','B-:good',toolsmu)
   ntupleTree('Btag','B-:tag',toolsBtag)

#processing
process(analysis_main)




#print out the summary
print(statistics)
