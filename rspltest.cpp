#include <iostream>

extern "C" {
#include "rspl/rspl.h"
}

using namespace std;


// struct rspl;
// Base class for 1D interpolation using the rspl library from Argyll. data.

class Interpolate_1D_Private;	// We wrap the implementation in here mainly
							// so clients don't have to include the C-based rspl headers
class Interpolate_1D
{
	public:
	Interpolate_1D();
	virtual ~Interpolate_1D();
	virtual bool Populate(int count,double *in,double *out);
	virtual double Interpolate(double input);
	virtual double ReverseInterpolate(double output);
	protected:
	Interpolate_1D_Private *priv;
};

class Interpolate_1D_Private
{
	public:
	Interpolate_1D_Private() : interp(NULL)
	{
		interp=new_rspl(0,1,1); // Create a new 1d -> 1d RSPL structure
		gres[0]=256;
		avgdev[0]=0.0;
		low[0]=-0.01;
		high[0]=1.01;
		low[1]=-0.01;
		high[1]=1.01;
	}
	~Interpolate_1D_Private()
	{
		if(interp)
			interp->del(interp);
	}
	bool Populate(int count, double *in, double *out)
	{
		co *myco=new co[count];
		for(int i=0;i<count;++i)
		{
			myco[i].p[0]=in[i];
			myco[i].v[0]=out[i];
		}
		interp->fit_rspl(interp,
		           0,				/* Non-mon and clip flags */
		           myco,			/* Test points */
		           count,				/* Number of test points */
		           low, high, gres,		/* Low, high, resolution of grid */
		           NULL, NULL,			/* Default data scale */
		           1.0,					/* Smoothing */
		           avgdev,				/* Average deviation */
		           NULL);				/* iwidth */
		delete[] myco;
		return(true);
	}
	protected:
	rspl *interp;
	int gres[MXDI];
	double avgdev[MXDO];
	double low[MXDI];
	double high[MXDI];
	friend class Interpolate_1D;
};


Interpolate_1D::Interpolate_1D() : priv(NULL)
{
	priv=new Interpolate_1D_Private();
}


Interpolate_1D::~Interpolate_1D()
{
	if(priv)
		delete priv;
}


double Interpolate_1D::Interpolate(double input)
{
	co point;
	point.p[0]=input;
	if(priv->interp->interp(priv->interp,&point))
		cerr << "Grid clipped... ";
	return(point.v[0]);
}


double Interpolate_1D::ReverseInterpolate(double output)
{
	co point;
	point.v[0]=output;
	int result=priv->interp->rev_interp(priv->interp,0,1,NULL,NULL,&point);
	if(result!=1)
		cerr << "Got solutions: " << result << "  -  ";
	return(point.p[0]);
}


bool Interpolate_1D::Populate(int count,double *in, double *out)
{
	return(priv->Populate(count,in,out));
}


double myin[]=
{
	0.0,
	0.1,
	0.2,
	0.3,
	0.4,
	0.5,
	0.6,
	0.7,
	0.8,
	0.9,
	1.0
};

double myout[]=
{
	0.0,
	0.11,
	0.19,
	0.32,
	0.41,
	0.56,
	0.67,
	0.78,
	0.86,
	0.95,
	0.99
};

int main(int argc,char **argv)
{
	Interpolate_1D interp;
	interp.Populate(11,myin,myout);

	cerr << "Forward lookup..." << endl;

	for(int i=0;i<100;++i)
	{
		double o=interp.Interpolate(i/100.0);
		cerr << i/100.0 << " -> " << o << endl;
	}

	cerr << "Reverse lookup..." << endl;

	for(int i=0;i<100;++i)
	{
		double o=interp.ReverseInterpolate(i/100.0);
		cerr << i/100.0 << " -> " << o << endl;
	}


	return(0);
}


#if 0

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
#endif

