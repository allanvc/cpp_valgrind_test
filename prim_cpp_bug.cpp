// implementation of Prim's algorithm for MST w/ distance matrix input
#include <iostream>
//#include <Rcpp.h>
#include <RcppArmadillo.h>

//using namespace Rcpp;
//using namespace arma;
using namespace std;


// [[Rcpp::depends(RcppArmadillo)]]


// [[Rcpp::export]]
Rcpp::List prim_cpp(arma::mat x)
{
	
		
	int V = x.n_cols;
	
	arma::uvec parent(V);
	parent.at(0) = 0;
	
	double max_value = x.max()+1;
	
	int v = 0;
	
	int idxmin_geral = 0;
	
	arma::uvec min_subnot;
	
	arma::mat new_m;
	
	arma::uvec from(V-1);
	//from.at(0) = 0;
	
	arma::uvec to(V-1);
	
	
	
	for(int i=0; i < V; i++)
	{
		// "deleting" the row for current vertex by setting the maximum to all entries in this row
		x.row(v).fill(max_value); // better than using loop
		
		// insert object x.col(v) at col i of new_m matrix
		new_m.insert_cols(i,x.col(v)); //see arma.sourceforge.net 
		
		//cout << new_m << endl;
		
		// obtain the minimum index from the selected columns
		idxmin_geral = new_m.index_min();
		
		// obtain the subscript notation from index based on reduced dimensions ***
		min_subnot = arma::ind2sub(arma::size(new_m.n_rows, new_m.n_cols),
                                        idxmin_geral);
		// *** adapted from @coatless
		// https://stackoverflow.com/questions/48045895/how-to-find-the-index-of-the-minimum-value-between-two-specific-columns-of-a-mat                                    
		
		v = min_subnot.at(0);
		parent.at(i+1) = v;
		
		to.at(i) = min_subnot.at(0);
		from.at(i) = parent.at(min_subnot.at(1));
		
		// "deleting" the row for current vertex by setting maximum to all entries in this row
		// now, in the new matrix
		new_m.row(v).fill(max_value); //better than using loop
	
	}
	/*
	 * add 1 to the final vectors - preparing R output
	*/
	return Rcpp::List::create(
	Rcpp::Named("dist",x),
	Rcpp::Named("parent",parent),
	Rcpp::Named("from",from+1),
	Rcpp::Named("to",to+1)
	);
}
