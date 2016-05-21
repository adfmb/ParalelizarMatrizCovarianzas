NRA<-200
NCA<-500
Matriz<-matrix(ncol=NCA, nrow=NRA)

for(i in 0:(nrow(Matriz)-1)){
  
  for(j in 0:(ncol(Matriz)-1)){
    
    Matriz[i+1,j+1]<-i+j
    
  }
  
}

M_covarianzas<-cov(Matriz)

Matriz<-Matriz/5