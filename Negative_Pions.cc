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
void Negative_Pions()
{
TStopwatch stopwatch;
stopwatch.Start();
//program starts here
TGraph*graph = new TGraph();
int vector_entry_index =0;
vector <string> _Runs = {"1695594438.root", "1695657805.root", "1695777255.root", "1695500542.root", "1695470554.root", "1695574471.root", "1695549948.root"};
cout<< setfill(' ') <<setw(10)<<left<<endl;
cout<<setw(5)<<"Sr#" <<setw(17)<< "Run"<<setw(15)<< "Momentum"<<setw(15)<<"#Neg_Pions"<<setw(15)<< "%Neg_Pions"<<endl;
for (const string &Run : _Runs)
{
TFile *file = TFile :: Open(Run.c_str());
TTree* RAWdata_tree  =(TTree*)file ->Get("RAWdata");
auto numEvents = RAWdata_tree ->GetEntries();
unsigned int NC0;
unsigned int NS1;
unsigned int NS4;
unsigned int NC1;
unsigned int numNC0 = 0;
unsigned int numNS1S4 = 0;
unsigned int numNS1 = 0;
unsigned int numNS4 = 0;
unsigned int numNC1 = 0;
RAWdata_tree ->SetBranchAddress("NTDC1_ch1", &NC0);
RAWdata_tree->SetBranchAddress("NTDC1_ch3", &NS1);
RAWdata_tree->SetBranchAddress("NTDC1_ch6", &NS4);
RAWdata_tree->SetBranchAddress("NTDC1_ch2", &NC1);
  for (size_t event_index = 0; event_index < numEvents; event_index++)
	{

	RAWdata_tree -> GetEntry(event_index);
	if(NC0 > 0)
	{numNC0++;}
	if(NS1>= 1 && NS4 >= 1)
	{numNS1S4++;}
	if(NS1 >0)
	{numNS1++;}
	if(NS4 >0)
	{numNS4++;}
	if(NC1 > 0)
	{numNC1++;}
	}
file ->Close();
double pion_percentage = (((double)numNC0-(double)numNC1)/((double) numNS1S4))*100;
double ratio_NS1NS4 = ((double)numNS1)/((double) numNS4);
if(vector_entry_index ==0)
	{
	graph ->AddPoint(2.0, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17) << Run.c_str()<<setw(15)<<"2.0 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
else if(vector_entry_index == 1)
	{
	graph ->AddPoint(3.0, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17) << Run.c_str()<<setw(15)<<"3.0 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
else if(vector_entry_index ==2)
        {graph ->AddPoint(4.5, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17)<< Run.c_str()<<setw(15)<<"4.5 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
else if(vector_entry_index ==3)
        {graph ->AddPoint(6.0, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17)<< Run.c_str()<<setw(15)<<"6.0 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
else if(vector_entry_index ==4)
        {graph ->AddPoint(8.0, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17)<< Run.c_str()<<setw(15)<<"8.0 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
else if(vector_entry_index ==5)
        {graph ->AddPoint(10.0, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17)<<Run.c_str()<<setw(15)<<"10.0 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
else
	{graph ->AddPoint(11.0, pion_percentage);
	cout<<setw(5)<<vector_entry_index<<setw(17)<< Run.c_str()<<setw(15)<<"11.0 GeV/c"<<setw(15)<<numNC0 - numNC1<<setw(15)<< pion_percentage<<endl;
	}
vector_entry_index++;
/*cout<< "pion percentage: "<<pion_percentage<< endl;
cout<< "Hits in S1S4/Total Events: "<< numNS1S4<< endl;
cout<< "Hits in C0/e, mu, pi: "<<numNC0<< endl;
cout<< "Hits in C1/e, mu: "<<numNC1<< endl;
cout<<"Number of Pions: "<<numNC0 - numNC1<< endl;
cout<< "Ratio of Hits in S1 and S4: " <<ratio_NS1NS4<< endl;
cout<<"..............................................................."<<endl;
*/
}
cout<<"................................................................................."<<endl;
//Section 3: Drawing and Makeup of the Graph
graph->GetXaxis()->SetTitle("Momentum(GeV/c)");
graph->GetYaxis()->SetTitle("Percentage(%)");
graph->SetMarkerSize(1);
graph->SetMarkerStyle(3);
TCanvas* canvas = new TCanvas("canvas", "Negative Pion Percentage", 900, 100, 500, 500);
graph ->SetLineColor(kRed);
graph ->SetLineWidth(2);
TLatex latex;
latex.SetNDC();
latex.SetTextFont(42);
latex.SetTextSize(0.04);
latex.SetTextAlign(23);
graph ->SetMinimum(0);
graph ->SetMaximum(100);
graph ->Draw("ALP");
latex.DrawLatex(0.5, 0.04, "Fig 1: Percentage of Negative Pions in T10");
TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.8);
legend ->AddEntry(graph, "Negative Pions", "ple");
legend ->Draw();
canvas ->Update();
//program ends here
stopwatch.Stop();
double elapsedSeconds = stopwatch.RealTime();
cout<< "runtime: "<< elapsedSeconds<< " Seconds" <<endl;

}
