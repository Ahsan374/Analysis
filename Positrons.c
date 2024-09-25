#include<TFile.h>
#include<TTree.h>
#include <TGraph.h>
#include<TCanvas.h>
#include <string>
#include <vector>
#include <TLatex.h>
#include <TLegend.h>
using namespace std;
void Positrons()
{
TStopwatch stopwatch;
stopwatch.Start();
//program starts here
TGraph*graph = new TGraph();
int vector_entry_index =0;
vector <string> _Runs = {"1695766843.root", "1695779942.root", "1695602999.root", "1695791586.root", "1695675441.root",};
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
unsigned int numNS1 = 0;
unsigned int numNS4 = 0;
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
        if (NS1 >0)
        {numNS1++;}
        if(NS4>0)
        {numNS4++;}

        }
file ->Close();
double electron_percentage = (((double)numNC0)/((double) numNS1S4))*100;
double ratio_NS1NS4 = ((double)numNS1)/((double) numNS4);
cout<< "electron percentage in "<<Run.c_str()<<"  with momentum 1.0 GeV/c is: "<<electron_percentage<< endl;
cout<< "Hits in S1S4 for "<< Run.c_str() << ": "<< numNS1S4<< endl;
cout<< "Hits in C0 for "<< Run.c_str()<< ": "<<numNC0<< endl;
cout<< "Ratio of Hits in S1 and S4: " <<ratio_NS1NS4<< endl;
switch (vector_entry_index)
  {
case 0:
        graph ->AddPoint(1.0, electron_percentage);
        break;
case 1:
        graph ->AddPoint(1.5, electron_percentage);
        break;
case 2:
        graph ->AddPoint(2.0, electron_percentage);
        break;
case 3:
        graph ->AddPoint(4.5, electron_percentage);
        break;
default:
        graph ->AddPoint(6.0, electron_percentage);
}
vector_entry_index++;
}
//Section 3: Drawing and Makeup of the Graph
graph->GetXaxis()->SetTitle("Momentum(GeV/c)");
graph->GetYaxis()->SetTitle("Percentage(%)");
graph->SetMarkerSize(1);
graph->SetMarkerStyle(3);
TCanvas* canvas = new TCanvas("canvas", "Positron Percentage", 900, 100, 500, 500);
graph ->SetLineColor(kRed);
graph ->SetLineWidth(2);
TLatex latex;
latex.SetNDC();
latex.SetTextFont(42);
latex.SetTextSize(0.04);
latex.SetTextAlign(23);
graph ->Draw("AP");
latex.DrawLatex(0.5, 0.04, "Fig 2: Percentage of Positrons in T10");
TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.8);
legend ->AddEntry(graph, "Positrons", "ple");
legend ->Draw();
canvas ->Update();
graph ->SaveAs("Positron_Percentage.png");
//program ends here
stopwatch.Stop();
double elapsedSeconds = stopwatch.RealTime();
cout<< "runtime: "<< elapsedSeconds<< " Seconds" <<endl;

}
