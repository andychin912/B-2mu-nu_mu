import ROOT
ROOT.gROOT.SetBatch(True)
from basf2 import *
register_module("EnableMyVariables", shared_lib_path='/home/belle/ytchin/git/B-2mu-nu_mu/libytchin.so')
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

parser.add_argument('-out', '--outputfile', dest='outputfile', type=str, default='/home/belle/ytchin/B+2mu+nu_mu/temp/20181027_signal.root',
                    help='Name of the outputted file')
args = parser.parse_args()
variables.addAlias('Nlep','countInList(pi+:lep)')
variables.addAlias('NhighP','countInList(pi+:highP)')
#-------------------------------------------Input mdst file---------------------------------------------
inputMdstList('default',['/ghi/fs01/belle/bdata2/users/ytchin/MC9signal/20171025_4_B+2mu+nu_mu_Udst.root.udst.root'])


#------------------------------------------Mbc and deltaE cut----------------------------------------------
buildRestOfEvent('B-:good', path=analysis_main)




#------------------------------------continuum suppression-------------------------------------------------


appendROEMask('B-:good','cleanMask','useCMSFrame(p)<=3.2 and nCDCHits>0 and abs(d0)<5 and abs(z0)<10','p>=0.05 and useCMSFrame(p)<=3.2',[0.09,0.11,0.62,0.14,0.048,0],path=analysis_main)
appendROEMask('B-:good','MC','useCMSFrame(p)<=3.2 and nCDCHits>0 and abs(d0)<5 and abs(z0)<10','p>=0.05 and useCMSFrame(p)<=3.2',[-1,-1,-1,-1,-1,-1],path=analysis_main)
appendROEMask('B-:good','noimpact','useCMSFrame(p)<=3.2 and nCDCHits>0','p>=0.05 and useCMSFrame(p)<=3.2',[0.09,0.11,0.62,0.14,0.048,0],path=analysis_main)
#,[0.09,0.11,0.62,0.14,0.048,0]
analysis_main.add_module('ContinuumSuppressionBuilder', particleList='B-:good', ROEMask='cleanMask')

fillParticleList("pi+:lep","abs(d0)<0.08 and abs(z0)<0.3 and muonID>0.9 and pidDeltaLogLikelihoodValueExpert(13,211,ALL)>28.9")
fillParticleList("pi+:highP","abs(d0)<5 and abs(z0)<10 and useCMSFrame(p)>2.2")

#event selection
cutAndCopyList('B-:evtslt','B-:good','nTracks>4 and ROE_mbc(cleanMask)>5.1 and ROE_deltae(cleanMask)>-2.4 and ROE_deltae(cleanMask)<0.8 and daughter(0,chiProb)>0.001 and abs(daughter(0,d0))<0.08 and abs(daughter(0,z0))<0.3 and useCMSFrame(p)>2.2 and useCMSFrame(p)<3.1 and daughter(0,nCDCHits)>0 and daughter(0,kaonID)<0.04 and daughter(0,electronID)<0.1 and thrustOm<0.99 and daughter(0,pidDeltaLogLikelihoodValueExpert(13,211,ALL))>28.9 and NhighP<2 and nROEKLMClusters<6 and ROE_eextra(cleanMask)<4.4 and missP(cleanMask,0)>2.3')
#

from flavorTagger import *
use_central_database("analysis_AAT-parameters_release-01-02-03")
flavorTagger(particleLists = ['B-:evtslt'])

#-------------------------------------------------NTuple maker---------------------------------------------
toolsmu = ['EventMetaData','^B- -> ^mu-']
toolsmu += ['MCTruth','^B- -> ^mu-']
toolsmu += ['Kinematics','^B- -> ^mu-']
toolsmu += ['MCKinematics','^B- -> ^mu-']
toolsmu += ['DeltaEMbc','B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(E):useCMSFrame(px):useCMSFrame(py):useCMSFrame(pz):useCMSFrame(p)]','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(mcE):useCMSFrame(mcP)]','^B- -> ^mu-']
toolsmu += ['CustomFloats[d0]','B- -> ^mu-']
toolsmu += ['CustomFloats[z0]','B- -> ^mu-']
toolsmu += ['CustomFloats[muonID]','B- -> ^mu-']
toolsmu += ['CustomFloats[electronID]','B- -> ^mu-']
toolsmu += ['CustomFloats[kaonID]','B- -> ^mu-']
toolsmu += ['CustomFloats[pionID]','B- -> ^mu-']
toolsmu += ['CustomFloats[protonID]','B- -> ^mu-']
toolsmu += ['CustomFloats[nCDCHits]','B- -> ^mu-']
toolsmu += ['CustomFloats[abs(useCMSFrame(cosTheta))]','^B- -> mu-']
toolsmu += ['CustomFloats[nROETracks(cleanMask)]','^B- -> mu-']
toolsmu += ['CustomFloats[nROETracks(noimpact)]','^B- -> mu-']
toolsmu += ['CustomFloats[ROE_mbc(cleanMask)]','^B- -> mu-']
toolsmu += ['CustomFloats[ROE_deltae(cleanMask)]','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(ROE_E(cleanMask)):useCMSFrame(ROE_P(cleanMask))]','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(ROE_E(MC)):useCMSFrame(ROE_P(MC))]','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(mcROE_E):useCMSFrame(mcROE_P)]','^B- -> mu-']
toolsmu += ['CustomFloats[useCMSFrame(mcROE_P)]','^B- -> mu-']
toolsmu += ['CustomFloats[missP(cleanMask,0):missE(cleanMask,0)]','^B- -> mu-']
toolsmu += ['CustomFloats[missP(cleanMask,1):missE(cleanMask,1)]','^B- -> mu-']
toolsmu += ['CustomFloats[missP(cleanMask,2):missE(cleanMask,2)]','^B- -> mu-']
toolsmu += ['ContinuumSuppression[KsfwFS1CcROE]','^B- -> mu-']
toolsmu += ['ContinuumSuppression','^B- -> mu-']
toolsmu += ['CustomFloats[chiProb]','B- -> ^mu-']
toolsmu += ['CustomFloats[nROEKLMClusters]','^B- -> mu-']
toolsmu += ['CustomFloats[ROE_eextra(cleanMask)]','^B- -> mu-']
toolsmu += ['CustomFloats[ROE_E(MC):ROE_E(cleanMask):ROE_E(noimpact):useCMSFrame(ROE_E(noimpact)):useCMSFrame(ROE_P(noimpact))]','^B- -> mu-']
toolsmu += ['CustomFloats[ROE_neextra(cleanMask):useCMSFrame(ROE_Px(cleanMask)):useCMSFrame(ROE_Py(cleanMask)):useCMSFrame(ROE_Pz(cleanMask))]','^B- -> mu-']
toolsmu += ['CustomFloats[nTracks]','^B- -> mu-']
toolsmu += ['CustomFloats[pidPairProbabilityExpert(13,211,ALL)]','B- -> ^mu-']
toolsmu += ['CustomFloats[pidProbabilityExpert(13,ALL)]','B- -> ^mu-']
toolsmu += ['CustomFloats[pidDeltaLogLikelihoodValueExpert(13,211,ALL)]','B- -> ^mu-']
toolsmu += ['CustomFloats[pidLogLikelihoodValueExpert(13,ALL)]','B- -> ^mu-']
toolsmu += ['CustomFloats[Nlep]','^B- -> ^mu-']
toolsmu += ['CustomFloats[NhighP]','^B- -> ^mu-']
toolsmu += ['CustomFloats[NumberOfMCParticlesInEvent(12)]','^B- -> mu-']
toolsmu += ['CustomFloats[NumberOfMCParticlesInEvent(14)]','^B- -> mu-']
toolsmu += ['CustomFloats[NumberOfMCParticlesInEvent(16)]','^B- -> mu-']
toolsmu += ['CustomFloats[ROE_charge(cleanMask)]','^B- -> mu-']
toolsmu += ['CustomFloats[charge]','B- -> ^mu-']
toolsmu += ['FlavorTagging[TMVA-FBDT,FANN-MLP,qpCategories]','^B- -> mu-']
toolsmu += ['CustomFloats[qrOutput(FBDT):qrOutput(FANN)]','^B- -> mu-']

ntupleFile(args.outputfile)
   #ntupleTree('Gm','gamma:tight',toolsgmECL)
ntupleTree('y4s','B-:evtslt',toolsmu)
   #ntupleTree('mutag','mu-:good',toolsmutag)
   #ntupleTree('etag','e-:good',toolsetag)
   #ntupleTree('pitag','pi-:good',toolspitag)
   #ntupleTree('Ktag','K-:good',toolsKtag)
   #ntupleTree('ptag','p+:good',toolsptag)


#processing
process(analysis_main)




#print out the summary
print(statistics)
