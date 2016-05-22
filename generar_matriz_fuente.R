generar_matriz<-function(filas,columnas,minimo=-1,maximo=50){
#   filas<-3
#   columnas<-5
#   minimo=-1
#   maximo<-50
  
  m<-matrix(cbind(round(runif(filas*columnas,minimo,maximo))),ncol=columnas)
  
  setwd("~/Dropbox/01_ITAM_Ciencia_de_Datos/2do_semestre/ComputoParalelo/Comp_Paralelo/ParalelizarMatrizCovarianzas")
  out <- file("fuente.csv", "w", encoding="latin1") 
  write.table(m, out, sep=",", row.names=FALSE,col.names = FALSE) 
  close(out) 
  
}

generar_matriz(10,100,-2,100)
