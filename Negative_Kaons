//Section 1: The necessary header files
#include<TFile.h>
#include<TTree.h>
#include <TGraph.h>
#include<TCanvas.h>
#include <string>
#include <vector>
#include <TLatex.h>
#include <TLegend.h>
#include<iomanip>
using namespace std;
void Negative_Kaons()
{
TStopwatch stopwatch;
stopwatch.Start();
//program starts here
TGraph*graph = new TGraph();
int vector_entry_index =0;
vector <string> _Runs = {"1695728358.root", "1695777255.root", "1695481656.root", "1695500542.root", "1695475966.root", "1695470554.root", "1695566198.root","1695574471.root"};
//cout<< setfill(' ') <<setw(10)<<left<<endl;
//cout<<setw(5)<<"Sr#" <<setw(17)<< "Run"<<setw(15)<< "Momentum"<<setw(15)<<"#Pions"<<setw(15)<< "%Pions"<<endl;
for (const string &Run : _Runs)
{
TFile *file = TFile :: Open(Run.c_str());
TTree* RAWdata_tree  =(TTree*)file ->Get("RAWdata");
auto numEvents = RAWdata_tree ->GetEntries();
unsigned int NC0;
unsigned int NS1;
unsigned int NS4;
unsigned int numNC0 = 0;
unsigned int numNS1S4 = 0;
double per_1;
double per_2;
double Percentage;
RAWdata_tree ->SetBranchAddress("NTDC1_ch1", &NC0);
RAWdata_tree->SetBranchAddress("NTDC1_ch3", &NS1);
RAWdata_tree->SetBranchAddress("NTDC1_ch6", &NS4);
  for (size_t event_index = 0; event_index < numEvents; event_index++)
	{

	RAWdata_tree -> GetEntry(event_index);
	if(NC0 > 0)
	{numNC0++;}
	if(NS1>= 1 && NS4 >= 1)
	{numNS1S4++;}
	}
file ->Close();
if(vector_entry_index%2 ==0)
 {//cout<<"entered in if "<<vector_entry_index<<endl;
  per_1 =((double)numNC0/(double) numNS1S4)*100;
  vector_entry_index++;
  continue;}
else
{//cout<<"entered in else "<<vector_entry_index<<endl;
per_2 =((double)numNC0/(double) numNS1S4)*100;
Percentage = per_1 - per_2;
}
if(vector_entry_index == 1)
{
graph ->AddPoint(4.5, Percentage);
vector_entry_index++;
//cout<<"entered in 1 "<<vector_entry_index<<endl;
}
if(vector_entry_index == 3)
{
graph ->AddPoint(6.0, Percentage);
vector_entry_index++;
//cout<<"entered in 3 "<<vector_entry_index<<endl;
}
if(vector_entry_index == 5)
{
graph ->AddPoint(8.0, Percentage);
vector_entry_index++;
//cout<<"entered in 5 "<<vector_entry_index<<endl;
}
if(vector_entry_index == 7)
{
graph ->AddPoint(10.0, Percentage);
vector_entry_index++;
//cout<<"entered in 7 "<<vector_entry_index<<endl;
}

}
graph->GetXaxis()->SetTitle("Momentum(GeV/c)");
graph->GetYaxis()->SetTitle("Percentage(%)");
graph->SetMarkerSize(1);
graph->SetMarkerStyle(3);
TCanvas* canvas = new TCanvas("canvas", "Negative Kaons Percentage", 900, 100, 500, 500);
graph ->SetLineColor(kRed);
graph ->SetLineWidth(2);
TLatex latex;
latex.SetNDC();
latex.SetTextFont(42);
latex.SetTextSize(0.04);
latex.SetTextAlign(23);
graph ->SetMinimum(0);
graph ->SetMaximum(20);
graph ->Draw("ALP");
latex.DrawLatex(0.5, 0.04, "Fig 1: Percentage of Negative Kaons in T10");
TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.8);
legend ->AddEntry(graph, "Negative Kaons", "ple");
legend ->Draw();
canvas ->Update();
//program ends here
stopwatch.Stop();
double elapsedSeconds = stopwatch.RealTime();
cout<< "runtime: "<< elapsedSeconds<< " Seconds" <<endl;

}
