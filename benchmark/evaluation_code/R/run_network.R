#########################################################
# Protein interaction network evaluations

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder <- "network"
net.train.files <- generateFilenames(data.folder, "train", onto.list, sim.list, si.list)
net.test.files <- generateFilenames(data.folder, "test", onto.list, sim.list, si.list)
net.col.labels <- gsub(".txt","",gsub("network/train_","",net.train.files))

## *** UI methods ********************************* ##
# add UI file names to the list
ui.list <- c("ui", "gic", "dic", "uic")
ui.train.files <- generateFilenamesUI(data.folder, "train", onto.list, ui.list)
ui.test.files <- generateFilenamesUI(data.folder, "test", onto.list, ui.list)
ui.col.labels <- gsub("_new.txt","",gsub("network/train_","",ui.train.files))

net.train.files <- c(net.train.files, ui.train.files)
net.test.files  <- c(net.test.files, ui.test.files)
net.col.labels <- c(net.col.labels, ui.col.labels)

#d.all <- loadNetworkData(net.train.files[1], net.test.files[1])
#d.auc.vals <- bootstrapAUC(d.all)

# modify the bootstrap function to add the number of bootstraps and the sample perentage
bfun <- function(x){bootstrapAUC(x, 100, 0.15)}
# Calculate the AUC data
net.boot.mat <- loadAndBootstrapPPI(net.train.files, net.test.files, bfun)
colnames(net.boot.mat) <- net.col.labels

net.boot.means <- colMeans(net.boot.mat)
net.boot.sd <- apply(net.boot.mat,2,sd)

#boxplot(net.boot.mat[,order(net.boot.means,decreasing=TRUE)])

net.dtable <- data.frame(net.boot.means, net.boot.sd)

write.table(net.dtable, file="results/network_auc_table.csv", quote=FALSE, sep=",")
write.table(net.boot.mat, file="results/network_auc_bootstrap.txt")