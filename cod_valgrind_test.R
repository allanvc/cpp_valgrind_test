#####################################################################################
################ script to test w/ valgrind ###############

# loc:
library(tcltk)
wd.loc<-tk_choose.dir()
setwd(wd.loc)

# simulating data:
 n=10 # works well
# n=100 #works well
# n=50
# n=1050 #not working 
set.seed(1984)
d1<-matrix(rnorm(n,mean=2,sd=1), n/2, 2)
d2<-matrix(rnorm(n,mean=-2,sd=.5), n/2, 2)
d<-rbind(d1,d2)

# distance matrix (via Rcpp)
# compiling
library(Rcpp)
sourceCpp("dist_matrix_OK.cpp", verbose=TRUE)

# padronizing
x <- scale(d[,1:2])
M <- as.matrix(x)

# euclidian matrix
dist.m<-dist_cpp(M)

# PRIM's algorithm
# compiling
# library(Rcpp)
library(RcppArmadillo)
sourceCpp("prim_cpp_bug.cpp", verbose=TRUE)
# running function
outMST <- prim_cpp(dist.m)
