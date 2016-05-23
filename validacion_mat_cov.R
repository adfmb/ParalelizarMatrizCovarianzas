setwd("~/Dropbox/01_ITAM_Ciencia_de_Datos/2do_semestre/ComputoParalelo/Comp_Paralelo/ParalelizarMatrizCovarianzas")
generar_matriz(50,500,-2,100)
Matriz<-read.csv("fuente.csv",header = FALSE)
M_covarianzas<-cov(Matriz)*(nrow(Matriz)-1)/nrow(Matriz)
M_covarianzas[ncol(M_covarianzas),ncol(M_covarianzas)]
#View(M_covarianzas)
