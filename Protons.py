from ROOT import TFile
print("This analysis is for the electrons with run 1695634174")
inputFile = TFile.Open("1695634174.root")
inputFile.ls()
RAWdata_tree = inputFile.Get("RAWdata")
RAWdata_tree.Print()
import numpy as np
NS1=0
NS4=0
timeNS4 = np.zeros(1024, dtype=np.int32)
timeNS0 = np.zeros(1024, dtype=np.int32)
RAWdata_tree.SetBranchAddress("TDC1_ch0", timeNS0)
RAWdata_tree.SetBranchAddress("TDC1_ch6", timeNS4)
RAWdata_tree.SetBranchAddress("NTDC1_ch3", NS1)
RAWdata_tree.SetBranchAddress("NTDC1_ch6", NS4)
numEvents = RAWdata_tree.GetEntries()
from ROOT import TH1D
from ROOT import TCanvas
c4 = TCanvas("c4", "c4", 1200, 100, 500,500)
tofHist = TH1D("tofHist", "Time of Flight of all Particles", 240, 0, 60)
tof =0.0
print(numEvents)
for i in range(numEvents):
  RAWdata_tree.GetEntry(i)
  tof =(timeNS4[0]-timeNS0[0])/40.0
  tofHist.Fill(tof)
  tofHist.Draw()
c4.Draw()
import ROOT
from sklearn.mixture import GaussianMixture
import numpy as np
import matplotlib.pyplot as plt
bin_edges = [tofHist.GetBinCenter(i) for i in range(1, tofHist.GetNbinsX() + 1)]
bin_counts = [tofHist.GetBinContent(i) for i in range(1, tofHist.GetNbinsX() + 1)]
gmm = GaussianMixture(n_components=2)
data = np.repeat(bin_edges, bin_counts)
gmm = GaussianMixture(n_components=2)
gmm.fit(data.reshape(-1, 1))
means = gmm.means_.flatten()
stds = np.sqrt(gmm.covariances_).flatten()
weights = gmm.weights_.flatten()
print("Means:", means)
print("Standard Deviations:", stds)
print("Weights:", weights)
x_range = np.linspace(min(data), max(data), 1000)
#y_gmm = np.sum([weights[i] * np.exp(-(x_range - means[i])**2 / (2 * stds[i]**2)) / (stds[i] * np.sqrt(2 * np.pi)) for i in range(2)], axis=0)
y_gmm_0 = np.sum([weights[0] * np.exp(-(x_range - means[0])**2 / (2 * stds[0]**2)) / (stds[0] * np.sqrt(2 * np.pi))], axis=0)
y_gmm_1 = np.sum([weights[1] * np.exp(-(x_range - means[1])**2 / (2 * stds[1]**2)) / (stds[1] * np.sqrt(2 * np.pi))], axis=0)
plt.plot(x_range, y_gmm_0, label='tof e/mu/pi/k')
plt.plot(x_range, y_gmm_1, label='tof Protons')
plt.xlabel('Time of Flight')
plt.ylabel('Count')
plt.legend()
plt.show()
plt.hist(data, bins=240, label='tof Histogram')
plt.legend()
plt.show()
num_data_points = len(data)
proportions = weights * num_data_points
print(proportions)
percentages =  weights* 100
