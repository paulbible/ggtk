
#source("evaluation_functions.R")

##################################################################################
# File name and utility functions
#################################
resultFileNameUI <- function(prefix,onto, sim){
  return(paste(paste(prefix,onto,sim,sep="_"),"_new.txt",sep=""))
}

resultFullFileNameUI <- function(folder, prefix,onto, sim){
  return(paste(folder,resultFileNameUI(prefix,onto, sim, si), sep="/"))
}

generateFilenamesUI <- function(folder,prefix,onto.list,sim.list){
  simFiles <- function(prefix, onto, sim){
    simNamer <- function(sim){resultFileNameUI(prefix, onto,sim)}
    return(unlist(lapply(sim.list, simNamer)))
  }
  
  ontoFiles <- function(prefix, onto.list, sim.list){
    ontoName <- function(onto){simFiles(prefix, onto, sim.list)}
    return(unlist(lapply(onto.list, ontoName)))
  }
  
  filenames <- ontoFiles(prefix, onto.list, sim.list)
  
  return(unlist(lapply(filenames,function(f){folderFile(folder, f)})))
}


##################################################################################
# loaders
#########
# using a lot of functions as arguments to avoid passing many parameters each time

## SI Loader, Lowest level
makeSimLoaderUI <- function(folder,prefix,onto){
  return(function(sim){
    filename <- resultFileNameUI(prefix, onto, sim)
    d <- read.table(folderFile(folder, filename))
    return(d)
  })
}

makeOntoLoaderUI <- function(folder, prefix, sim.list){
  return(function(onto){
    simLoader <- makeSimLoaderUI(folder,prefix,onto)
    sim.data = loadCat(sim.list, simLoader)
    colnames(sim.data) <- prependEach(onto, colnames(sim.data))
    return(sim.data)
  })
}

