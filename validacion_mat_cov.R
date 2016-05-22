setwd("~/Dropbox/01_ITAM_Ciencia_de_Datos/2do_semestre/ComputoParalelo/Comp_Paralelo/ParalelizarMatrizCovarianzas")
Matriz<-read.csv("file.csv",header = FALSE)
M_covarianzas<-cov(Matriz)*(nrow(Matriz)-1)/nrow(Matriz)
View(M_covarianzas)
