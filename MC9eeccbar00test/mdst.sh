i=0
while [ "${i}" != "6" ]
do
    i=$(($i + 1))
    bsub basf2 ~/git/B-2mu-nu_mu/B+2mu+nu_mu_Udst.py -i /ghi/fs01/belle/bdata2/users/ytchin/MC9eeccbar_mdst/output"$i".root -o RootOutput_"$i".udst.root
    
done
