#########################################################
# Reactome evaluations

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder <- "reactome"
sample.folder <- paste(data.folder,"sample_dir",sep="/")
matrix.folder <- paste(data.folder, "gene_matrix_dir", sep="/")

si.folders <- prependEach(matrix.folder, Reduce(mapCat,list(onto.list,sim.list,si.list)),"/")
si.labels <- gsub(paste(matrix.folder,"/",sep=""),"",si.folders)

## *** UI methods ********************************* ##
# add UI file names to the list
ui.list <- c("ui", "gic", "dic", "uic")
ui.folders <- prependEach(matrix.folder,mapCat(onto.list,ui.list),"/")
ui.labels <- gsub(paste(matrix.folder,"/",sep=""),"",ui.folders)

si.folders <- c(si.folders, ui.folders)
si.labels <- c(si.labels, ui.labels)


ward.clust <- function(x){hclust(x, method="ward.D")}

reactome.boot.mat.ward <- bootCatReactomeMatrix(si.folders, sample.folder, ward.clust)
colnames(reactome.boot.mat.ward) <- si.labels
reactome.boot.means.ward <- colMeans(reactome.boot.mat.ward)
reactome.boot.sd.ward <- apply(reactome.boot.mat.ward,2,sd)

reactome.dtable.ward <- data.frame(reactome.boot.means.ward, reactome.boot.sd.ward)
colnames(reactome.dtable.ward) <- c("mean", "sd")
# reactome.dtable.ward[order(reactome.boot.means.ward, decreasing=TRUE),]

write.table(reactome.dtable.ward, file="results/reactome_table.csv", quote=FALSE, sep=",")
write.table(reactome.boot.mat.ward, file="results/reactome_bootstrap.txt")
