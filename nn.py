import ROOT
import root_pandas
import numpy as np
import pandas as pd
import seaborn as sb
import matplotlib.pyplot as plt

from itertools import product

from root_numpy import root2array

from keras.models import Sequential
from keras.layers import Dense

from sklearn.model_selection import train_test_split
from sklearn.metrics import roc_curve, roc_auc_score

# fix random seed for reproducibility
np.random.seed(1986)

features = [
    'mu_pt'     ,
    'mu_eta'    ,
    'mu_phi'    ,
    'mu_charge' ,
    'mu1_pt'    ,
    'mu1_eta'   ,
    'mu1_phi'   ,
    'mu1_charge',
    'mu2_pt'    ,
    'mu2_eta'   ,
    'mu2_phi'   ,
    'mu2_charge',
]

mu  = pd.DataFrame(root2array('bc_jpsi_mu_nu_gen.root' , 'tree'))
tau = pd.DataFrame(root2array('bc_jpsi_tau_nu_gen.root', 'tree'))

mu ['target'] = 0
tau['target'] = 1

# concatenate the two samples
dataset = pd.concat([mu, tau])

# shuffle and plit train/test
train, test = train_test_split(dataset, test_size=0.85, random_state=1986, shuffle=True)

# X and Y on the training sample
X = pd.DataFrame(train, columns=features)
Y = pd.DataFrame(train, columns=['target'])

# define the model
model = Sequential()
model.add(Dense(12, input_dim=len(features), activation='relu'))
model.add(Dense(8, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

# compile the model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

# fit the model
model.fit(X, Y, epochs=10, batch_size=10, validation_split=0.5)

# evaluate the model
scores = model.evaluate(X, Y)
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))

# calculate predictions on the test sample
print 'predicting on', test.shape[0], 'events'
x = pd.DataFrame(test, columns=features)
y = model.predict(x)

# add the score to the test sample
test.insert(len(test.columns), 'nn_score', y)

# save file
test.to_root('bc_enriched.root', key='tree', store_index=False)

# let sklearn do the heavy lifting and compute the ROC curves for you
fpr, tpr, wps = roc_curve(test.target, test.nn_score) 

# plot
plt.plot(fpr, tpr, label=r'$\mu$ vs. $\tau$ NN', color='b')

# plot the also the diagonal, that corresponds to no random picks, no discrimination power
xy = [i*j for i,j in product([10.**i for i in range(-8, 0)], [1,2,4,8])]+[1]
plt.plot(xy, xy, color='grey', linestyle='--')

# cosmetics
plt.xlabel(r'$\epsilon(\tau)$')
plt.ylabel(r'$\epsilon(\mu)$')

# axis range
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.0])

# grid
plt.grid(True)

# legend
plt.legend(loc='lower right')

# save figure and then clean it
plt.savefig('roc.pdf')
plt.clf()

# plot the discriminator shape for the muon and tau channel
test_tau = test[test.tau_pt>=0]
test_mu  = test[test.tau_pt <0]
sb.distplot(test_tau['nn_score'], kde=False, norm_hist=True, label=r'$\tau\to\mu$ channel', color='b')
sb.distplot(test_mu ['nn_score'], kde=False, norm_hist=True, label=r'$\mu$ channel' , color='r')
plt.xlabel('classifier score')
plt.ylabel('a.u.')
plt.legend(loc='upper right')
plt.savefig('score.pdf')
plt.clf()

# GPU at PSI
# https://wiki.chipp.ch/twiki/bin/view/CmsTier3/SlurmUsage


