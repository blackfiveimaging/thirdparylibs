#include <iostream>

extern "C" {
#include "rspl/rspl.h"
}

using namespace std;

co mydata[]=
{
	{{0.0},{0.0}},
	{{0.1},{0.11}},
	{{0.2},{0.19}},
	{{0.3},{0.32}},
	{{0.4},{0.41}},
	{{0.5},{0.56}},
	{{0.6},{0.67}},
	{{0.7},{0.78}},
	{{0.8},{0.86}},
	{{0.9},{0.95}},
	{{1.0},{0.99}},
};

int main(int argc,char **argv)
{
	rspl *myrspl=new_rspl(0,1,1); // Create a new 1d -> 1d RSPL structure
	int npoints=sizeof(mydata)/sizeof(co);

	int gres[MXDI];
	double avgdev[MXDO];
	double low[MXDI];
	double high[MXDI];
	gres[0]=3000;
	avgdev[0]=0.0;
	low[0]=-0.01;
	high[0]=1.01;
	low[1]=-0.01;
	high[1]=1.01;

	myrspl->fit_rspl(myrspl,
	           0,				/* Non-mon and clip flags */
	           mydata,			/* Test points */
	           npoints,				/* Number of test points */
	           low, high, gres,		/* Low, high, resolution of grid */
	           NULL, NULL,			/* Default data scale */
	           1.0,					/* Smoothing */
	           avgdev,				/* Average deviation */
	           NULL);				/* iwidth */

	cerr << "Forward lookup..." << endl;

	for(int i=0;i<100;++i)
	{
		co point;
		point.p[0]=i/100.0;
		int result=myrspl->interp(myrspl,&point);
		if(result)
			cerr << "Grid clipped... ";
		cerr << point.p[0] << " -> " << point.v[0] << endl;
	}

	cerr << "Reverse lookup..." << endl;

	for(int i=0;i<100;++i)
	{
		co point;
		point.v[0]=i/100.0;
		int result=myrspl->rev_interp(myrspl,0,1,NULL,NULL,&point);
		if(result!=1)
			cerr << "Got solutions: " << result << "  -  ";
		cerr << point.v[0] << " -> " << point.p[0] << endl;
	}

	return(0);
}

