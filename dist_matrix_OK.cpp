#include <Rcpp.h>
// implementation of the calculaton of a euclidian distance matrix in Rcpp by coatless
// https://stackoverflow.com/questions/36829700/rcpp-my-distance-matrix-program-is-slower-than-the-function-in-package


// [[Rcpp::export]]
Rcpp::NumericMatrix dist_cpp(const Rcpp::NumericMatrix & x){
  unsigned int outrows = x.nrow(), i = 0, j = 0;
  double d;
  Rcpp::NumericMatrix out(outrows,outrows); //esse out(,) eh a representacao de matriz em rcpp

  for (i = 0; i < outrows - 1; i++){
    Rcpp::NumericVector v1 = x.row(i);
    for (j = i + 1; j < outrows ; j ++){
      d = sqrt(sum(pow(v1-x.row(j), 2.0)));
      out(j,i)=d;
      out(i,j)=d;
    }
  }

  return out;
}
