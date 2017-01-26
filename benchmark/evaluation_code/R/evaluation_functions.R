##################################################################################
# Evaluation functions and utility functions
############################################

# Required packages
library(igraph)
library(ROCR)
library(gplots)


##################################################################################
# File name and utility functions
#################################
resultFileName <- function(prefix,onto, sim, si){
  return(paste(paste(prefix,onto,sim,si,sep="_"),".txt",sep=""))
}

resultFullFileName <- function(folder, prefix,onto, sim, si){
  return(paste(folder,resultFileName(prefix,onto, sim, si), sep="/"))
}

folderFile <- function(folder, filename){
  return(paste(folder, filename, sep="/"))
}

prependEach <- function(prefix, alist, s="_"){
  unlist(lapply(alist, function(x){paste(prefix, x, sep=s)}))
}

generateFilenames <- function(folder,prefix,onto.list,sim.list,si.list){
  siFiles <- function(prefix, onto, sim, si.list){
    siNamer <- function(si){resultFileName(prefix, onto,sim, si)}
    return(unlist(lapply(si.list, siNamer)))
  }
  
  simFiles <- function(prefix, onto, sim.list, si.list){
    simNamer <- function(sim){siFiles(prefix, onto,sim, si.list)}
    return(unlist(lapply(sim.list, simNamer)))
  }
  
  ontoFiles <- function(prefix, onto.list, sim.list, si.list){
    ontoName <- function(onto){simFiles(prefix, onto, sim.list, si.list)}
    return(unlist(lapply(onto.list, ontoName)))
  }
  
  filenames <- ontoFiles(prefix, onto.list, sim.list, si.list)
  
  return(unlist(lapply(filenames,function(f){folderFile(folder, f)})))
}

mapCat <- function(alist, blist, sep="_"){
  return(unlist(lapply(alist, function(x) {prependEach(x, blist, sep)})))
}


##################################################################################
# loaders
#########
# using a lot of functions as arguments to avoid passing many parameters each time

## SI Loader, Lowest level
makeSiLoader <- function(folder,prefix,onto,sim){
  return(function(si){
    filename <- resultFileName(prefix,onto, sim, si)
    d <- read.table(folderFile(folder, filename))
    return(d)
  })
}

indexLoader <- function(index, loader){
  return(function(x){loader(x)[,index]})
}


loadCat <- function(alist, loader){
  d <- Reduce(cbind,lapply(alist, indexLoader(4,loader)))
  colnames(d) <- alist
  return(d)
}

## Sim loaders
makeSimLoader <- function(folder,prefix,onto,si.list){
  return(function(sim){
    loader = makeSiLoader(folder,prefix,onto,sim)
    si.data = loadCat(si.list,loader)
    colnames(si.data) <- prependEach(sim,colnames(si.data))
    return(si.data)
  })
}


loadCatSim <- function(alist, simLoader){
  d <- Reduce(cbind,lapply(alist, simLoader))
  return(d)
}


## Ontology loader
makeOntoLoader <- function(folder, prefix, sim.list, si.list){
  return(function(onto){
    simLoader <- makeSimLoader(folder,prefix,onto,si.list)
    sim.data = loadCatSim(sim.list, simLoader)
    colnames(sim.data) <- prependEach(onto, colnames(sim.data))
    return(sim.data)
  })
}


loadCatOnto <- function(alist, simLoader){
  return(loadCatSim(alist, simLoader))
}


##################################################################################
# Bootstrap sampling
####################
sample_cor <- function(a,b,s.size=100000){
  
  all.i <- 1:length(a)
  indices <- sample(all.i,s.size,replace=T)
  
  cor(a[indices],b[indices])
}

sample_cor_s <- function(a,b,s.size=100000){
  
  all.i <- 1:length(a)
  indices <- sample(all.i,s.size,replace=T)
  
  cor(a[indices],b[indices],method="spearman")
}

bootstrap_cor <- function(a,b,nboots=1000,s.size=100000){
  vals <- rep(0,nboots)
  
  for(i in 1:nboots){
    vals[i] <- sample_cor(a,b,s.size)
  }
  vals
}

bootstrap_cor_s <- function(a,b,nboots=1000,s.size=100000){
  vals <- rep(0,nboots)
  
  for(i in 1:nboots){
    vals[i] <- sample_cor_s(a,b,s.size)
  }
  vals
}

bootstrap_abs_score_cor_s <- function(a,b,nboots=1000,s.size=100000){
  vals <- rep(0,nboots)
  
  for(i in 1:nboots){
    vals[i] <- sample_cor_s(abs(a),b,s.size)
  }
  vals
}

bootMatrix <- function(target, mat, bootFun=bootstrap_cor, nboots=1000, s.size=100000){
  Reduce(cbind,
         lapply(1:ncol(mat), function(i){bootFun(target,mat[,i],nboots,s.size)}))
}


##################################################################################
## Gene correltion funcions
###########################
# Much more data for gene correlations, all data can't be laoded at once.

bootstrapLoader <- function(bootFun, nboots=100, s.percent=0.15){
  return(function(filename){
    d <- read.table(filename)
    target <- d[,3]
    scores <- d[,4]
    s.size = as.integer(nrow(d) * s.percent)
    return(bootFun(target,scores,nboots,s.size))
  })
}

bootCatMatrix <- function(filenames, bootFun, nboots=100, s.percent=0.15){
  bootLoader <- bootstrapLoader(bootFun,nboots,s.percent)
  return(Reduce(cbind, lapply(filenames, bootLoader)))
}


##################################################################################
## Reactome funcions
####################
# Reactome needs some clustering analysis to be used.

# load the gene similarity matrix
loadMatrixN <- function(n,folder){
  filename <- folderFile(folder, paste("matrix_", n, ".txt",sep=""))
  d <- read.table(filename, row.names=1, header=FALSE)
  return(d)
}

# load the reactome labels as a cluster partion
loadReactomeLabelsN <- function(n,folder){
  filename <- folderFile(folder, paste("sample_", n, ".txt",sep=""))
  d <- read.table(filename)
  unq<-as.matrix(unique(d[,1]))
  
  # make a function to extract the reactome label
  getLabel <- function(x){as.matrix(subset(d,d[,1] == x))[1,2]}
  
  # make reactome labels, cluster number labels
  labels <- as.numeric(factor(unlist(lapply(unq, getLabel))))
  labels <- as.matrix(labels)
  rownames(labels) <- unq
  return(labels)
}

makeReactomeCalculator <- function(matrix.folder, sample.folder, hclustFun=hclust){
  return(function(n){
    mat <- loadMatrixN(n, matrix.folder)
    
    mat.cmean <- colMeans(mat)
    # print(n)
    filer.index <- which(mat.cmean < 0.01)
    if(length(filer.index) > 0){
      mat.clean <- mat[-filer.index,-filer.index]  
    }else{
      mat.clean <- mat
    }
    
    s <- loadReactomeLabelsN(n, sample.folder)
    in.s <- match(rownames(mat.clean),rownames(s))
    s <- s[in.s,]
    
    hc <- hclustFun(as.dist(1-mat.clean))
    part.hc <- cutree(hc,10)
    return(1-compare(part.hc, s)/log(length(part.hc)))
  })
}

makeReactomeBootstrapper <- function(sample.folder,hclustFun=hclust){
  return(function(folder){
    viCalculator <- makeReactomeCalculator(folder, sample.folder, hclustFun)
    return(unlist(lapply(0:99, viCalculator)))
  })
}

bootCatReactomeMatrix <- function(folders, sample.folder, hclustFun=hclust){
  bootMatrixFolder <- makeReactomeBootstrapper(sample.folder, hclustFun)
  return(Reduce(cbind, lapply(folders, bootMatrixFolder)))
}



##################################################################################
## Interaction prediciton
#########################
# Evalute the predictive power of semantic similarity

loadNetworkData <- function(file1, file2){
  d.train <- read.table(file1, header=FALSE)
  d.test <- read.table(file2, header=FALSE)
  d.all <- rbind(d.train, d.test)
  return(d.all)
}

sampleAUC <- function(d, s.ratio=0.15){
  ## Assumed d has format:
  # gene1 gene2 label score
  s.size <- as.integer(nrow(d)*s.ratio)
  index <- sample(1:nrow(d), s.size, replace=TRUE)
  d.new <- d[index,]
  # predict using score d[,4] and label d.new[,3]
  pred <- prediction(d.new[,4],d.new[,3])
  perf <- performance(pred,"auc")
  return(perf@y.values[[1]][1])
}

bootstrapAUC <- function(d, nboots=100, s.ratio=0.15){
  times <- 1:nboots
  return(unlist(lapply(times, function(x){sampleAUC(d, s.ratio)})))
}


loadAndBootstrapPPI <- function(train.files, test.files, bootFun){
  n.files <- length(train.files)
  loadAndBoot <- function(i){
    d <- loadNetworkData(train.files[i], test.files[i])
    return(bootFun(d))
  }
  return(Reduce(cbind, lapply(1:n.files, loadAndBoot)))
}

# load and train threshold
loadAndTrainThreshold <- function(file1){
  d.train <- read.table(file1, header=FALSE)
  pred <- prediction(d.train[,4],d.train[,3])
  
  #get the f scores for each threshold
  perf <- performance(pred,"f")
  x.vals <- perf@x.values[[1]]
  x.vals <- x.vals[2:length(x.vals)]
  y.vals <- perf@y.values[[1]]
  y.vals <- y.vals[2:length(y.vals)]
  
  # calculate the f score function
  f.score.fun <- approxfun(x.vals,y.vals)
  
  # maximize the f-score
  suppressWarnings(opt <- optimize(f.score.fun,c(0,1), maximum=TRUE))
  return(opt$maximum)
}

trainThreshold <- function(d.train){
  pred <- prediction(d.train[,4],d.train[,3])
  
  #get the f scores for each threshold
  perf <- performance(pred,"f")
  x.vals <- perf@x.values[[1]]
  x.vals <- x.vals[2:length(x.vals)]
  y.vals <- perf@y.values[[1]]
  y.vals <- y.vals[2:length(y.vals)]
  
  # calculate the f score function
  f.score.fun <- approxfun(x.vals,y.vals)
  
  # maximize the f-score
  suppressWarnings(opt <- optimize(f.score.fun,c(0,1), maximum=TRUE))
  return(opt$maximum)
}

calculateThresholds <- function(filenames){
  return(unlist(lapply(filenames, loadAndTrainThreshold)))
}

predictTestData <- function(filename, threshold){
  d.test <- read.table(filename, header=FALSE)
  return(as.numeric(d.test[,4] > threshold))
}

calcPredictionMatrix <- function(files, thresholds){
  indexes <- 1:length(files)
  calcN <- function(i){
    return(predictTestData(files[i], thresholds[i]))
  }
  return(Reduce(cbind, lapply(indexes, calcN)))
}


#############################
# Plotting

pcaPlot2D <- function(mat,cs=rich.colors(ncol(mat)), doCols=T){
  
  if(doCols){
    result <- prcomp(t(mat))
  }else{
    result <- prcomp(mat)
  }
  
  plot(result$x[,1:2],pch=19,xlab="Component 1",ylab="Component 2",col=cs, lwd=3)
}

getTop5 <- function(mat,ms){
  return(mat[,order(ms,decreasing=TRUE)][,1:5])
}

niceBoxplot <- function(mat,title){
  boxplot(mat, main=title, xaxt = "n")
  axis(1,at=1:ncol(mat), labels=colnames(mat), padj=0.5)  
}

#############################
# Cross validation
calcErrorCV <- function(all.data){
  fold.size <- as.integer(nrow(all.data)/10)
  1:10 * fold.size
  starts <- 0:9 * fold.size + 1
  ends   <- 1:10 * fold.size
  ends[10] <- nrow(all.data)
  
  errs <- rep(0,10)
  for(i in 1:10){
    test.data <- all.data[starts[i]:ends[i],]
    table(test.data[,3])
    train.data <- all.data[-(starts[i]:ends[i]),]
    table(train.data[,3])
    
    # train threshold and predict values
    thresh <- trainThreshold(train.data)
    pred <- test.data[,4] > thresh
    
    # calculate the prediction error
    pred.diff <- pred - test.data[,3]
    err <- sum(abs(pred.diff))/nrow(test.data)
    errs[i] <- err
  }
  return(errs)
}

calcPreds <- function(all.data, i){
  fold.size <- as.integer(nrow(all.data)/10)
  1:10 * fold.size
  starts <- 0:9 * fold.size + 1
  ends   <- 1:10 * fold.size
  ends[10] <- nrow(all.data)
  
  test.data <- all.data[starts[i]:ends[i],]
  #table(test.data[,3])
  train.data <- all.data[-(starts[i]:ends[i]),]
  #table(train.data[,3])
  
  # train threshold and predict values
  thresh <- trainThreshold(train.data)
  pred <- test.data[,4] > thresh
  return(pred)
}

makeFoldCalc <- function(fold.index){
  return(function(all.data){
    return(calcPreds(all.data,fold.index))
  })
}


calcVoteErrorsCV <- function(table.list){
  fold.size <- as.integer(nrow(table.list[[1]])/10)
  1:10 * fold.size
  starts <- 0:9 * fold.size + 1
  ends   <- 1:10 * fold.size
  ends[10] <- nrow(table.list[[1]])
  
  errs <- rep(0,10)
  for(i in 1:10){
    foldCalc <- makeFoldCalc(i)
    target <- table.list[[1]][starts[i]:ends[i],3]
    
    all.preds <- Reduce(cbind, lapply(table.list, foldCalc))
    votes <- rowSums(all.preds)
    pred <- votes > floor(length(table.list)/2)
    pred.diff <- pred - target
    err <- sum(abs(pred.diff))/length(target)
    #print(err)
    errs[i] <- err
  }
  return(errs)
}


