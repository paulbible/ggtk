#########################################################
# RRBS evaluations

## UI methods added

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder = "rrbs"
# files have the form: data.folder/prefix_onto_sim_si.txt
ontoLoader = makeOntoLoader(data.folder, 'rrbs', sim.list, si.list)

#load all data from the SI experiments
rrbs.data.si <- loadCatOnto(onto.list, ontoLoader)

## *** UI methods ********************************* ##
# Load data from the UI experiments
ui.list <- c("ui", "gic", "dic", "uic")
ui.ontoLoader <- makeOntoLoaderUI(data.folder, "rrbs", ui.list)
rrbs.data.ui <- loadCatOnto(onto.list, ui.ontoLoader)
## ************************************************ ##

# ** combine both experiments
rrbs.data <- cbind(rrbs.data.si, rrbs.data.ui)

#load target data
rrbs.one <- read.table(resultFullFileName(data.folder,"rrbs", onto.list[1], sim.list[1], si.list[1]))
rrbs.target = rrbs.one[,3]

# create new matrix of the bootstrap values
# Non-linear correlation, Spearman
rrbs.boot.mat <- bootMatrix(rrbs.target, rrbs.data, bootstrap_cor_s)
colnames(rrbs.boot.mat) <- colnames(rrbs.data)
rrbs.boot.means <- colMeans(rrbs.boot.mat)
rrbs.boot.sd <- apply(rrbs.boot.mat,2,sd)

# boxplot(rrbs.boot.mat[,order(rrbs.boot.means,decreasing=TRUE)])

rrbs.dtable <- data.frame(rrbs.boot.means, rrbs.boot.sd)
colnames(rrbs.dtable) <- c("mean", "sd")
# rrbs.dtable[order(rrbs.boot.means,decreasing=TRUE),]

# Record analysis to file
write.table(rrbs.dtable, file="results/rrbs_table.csv", quote=FALSE, sep=",")
write.table(rrbs.boot.mat, file="results/rrbs_bootstrap.txt")
# load with:  d <- read.table("rrbs_bootstrap.txt")

rm(rrbs.data, rrbs.one, rrbs.target)
rm(rrbs.boot.mat, rrbs.boot.means,rrbs.boot.sd, rrbs.dtable)
# ** remove new data tables
rm(rrbs.data.ui, rrbs.data.si)











