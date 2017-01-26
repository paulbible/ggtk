#########################################################
# tf*idf evaluations

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder = "tf-idf"
# files have the form: data.folder/prefix_onto_sim_si.txt
ontoLoader = makeOntoLoader(data.folder, 'tf-idf', sim.list, si.list)

# load all data from the experiments
tfidf.data.si <- loadCatOnto(onto.list, ontoLoader)

## *** UI methods ********************************* ##
# Load data from the UI experiments
ui.list <- c("ui", "gic", "dic", "uic")
ui.ontoLoader <- makeOntoLoaderUI(data.folder, "tf-idf", ui.list)
tfidf.data.ui <- loadCatOnto(onto.list, ui.ontoLoader)
## ************************************************ ##

# ** combine both experiments
tfidf.data <- cbind(tfidf.data.si, tfidf.data.ui)

# load target data
tfidf.one <- read.table(resultFullFileName(data.folder,"tf-idf", onto.list[1], sim.list[1], si.list[1]))
tfidf.target = tfidf.one[,3]

# create new matrix of the bootstrap values
# Non-linear correlation, Spearman
tfidf.boot.mat <- bootMatrix(tfidf.target, tfidf.data, bootstrap_cor_s)
colnames(tfidf.boot.mat) <- colnames(tfidf.data)
tfidf.boot.means <- colMeans(tfidf.boot.mat)
tfidf.boot.sd <- apply(tfidf.boot.mat,2,sd)

# boxplot(tfidf.boot.mat[,order(tfidf.boot.means,decreasing=TRUE)])

tfidf.dtable <- data.frame(tfidf.boot.means, tfidf.boot.sd)
colnames(tfidf.dtable) <- c("mean", "sd")
# tfidf.dtable[order(tfidf.boot.means,decreasing=TRUE),]

# Record analysis to file
write.table(tfidf.dtable, file="results/tf-idf_table.csv", quote=FALSE, sep=",")
write.table(tfidf.boot.mat, file="results/tf-idf_bootstrap.txt")
# load with:  d <- read.table("tf-idf_bootstrap.txt")

rm(tfidf.data, tfidf.one, tfidf.target)
rm(tfidf.boot.mat, tfidf.boot.means, tfidf.boot.sd, tfidf.dtable)
