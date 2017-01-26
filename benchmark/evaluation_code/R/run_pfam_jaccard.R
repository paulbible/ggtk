#########################################################
# Jaccard evaluations

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder = "jaccard"
# files have the form: data.folder/prefix_onto_sim_si.txt
ontoLoader = makeOntoLoader(data.folder, 'jaccard', sim.list, si.list)

# load all data from the experiments
jaccard.data.si <- loadCatOnto(onto.list, ontoLoader)

## *** UI methods ********************************* ##
# Load data from the UI experiments
ui.list <- c("ui", "gic", "dic", "uic")
ui.ontoLoader <- makeOntoLoaderUI(data.folder, "jaccard", ui.list)
jaccard.data.ui <- loadCatOnto(onto.list, ui.ontoLoader)
## ************************************************ ##

# ** combine both experiments
jaccard.data <- cbind(jaccard.data.si, jaccard.data.ui)

#load target data
jaccard.one <- read.table(resultFullFileName(data.folder,"jaccard", onto.list[1], sim.list[1], si.list[1]))
jaccard.target = jaccard.one[,3]

# create new matrix of the bootstrap values
# Non-linear correlation, Spearman
jaccard.boot.mat <- bootMatrix(jaccard.target, jaccard.data, bootstrap_cor_s)
colnames(jaccard.boot.mat) <- colnames(jaccard.data)
jaccard.boot.means <- colMeans(jaccard.boot.mat)
jaccard.boot.sd <- apply(jaccard.boot.mat,2,sd)

# boxplot(jaccard.boot.mat[,order(jaccard.boot.means,decreasing=TRUE)])

jaccard.dtable <- data.frame(jaccard.boot.means, jaccard.boot.sd)
colnames(jaccard.dtable) <- c("mean", "sd")
# jaccard.dtable[order(jaccard.boot.means,decreasing=TRUE),]

# Record analysis to file
write.table(jaccard.dtable, file="results/jaccard_table.csv", quote=FALSE, sep=",")
write.table(jaccard.boot.mat, file="results/jaccard_bootstrap.txt")
# load with:  d <- read.table("jaccard_bootstrap.txt")

rm(jaccard.data, jaccard.one, jaccard.target)
rm(jaccard.boot.mat, jaccard.boot.means, jaccard.boot.sd, jaccard.dtable)
# ** remove new data tables
rm(jaccard.data.si, jaccard.data.ui)
