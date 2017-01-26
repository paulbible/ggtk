#########################################################
# gene correlation evaluations, Pearson

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder = "gene_correlations"
pearson.files <- generateFilenames(data.folder, "pearson", onto.list, sim.list, si.list)
pearson.labels <- gsub(".txt","",gsub("gene_correlations/pearson_","",pearson.files))

## *** UI methods ********************************* ##
# add UI file names to the list
ui.list <- c("ui", "gic", "dic", "uic")
ui.files <- generateFilenamesUI(data.folder, "pearson", onto.list, ui.list)
ui.labels <- gsub("_new.txt","",gsub("gene_correlations/pearson_","",ui.files))
# ** add the new filenames and labels to the list
pearson.files <- c(pearson.files, ui.files)
pearson.labels <- c(pearson.labels, ui.labels)

# call the functions to load and bootstrap and indifidual file with out keeping all data in memory
pearson.boot.mat <- bootCatMatrix(pearson.files, bootstrap_cor_s)
colnames(pearson.boot.mat) <- pearson.labels
pearson.boot.means <- colMeans(pearson.boot.mat)
pearson.boot.sd <- apply(pearson.boot.mat,2,sd)

#boxplot(pearson.boot.mat[,order(pearson.boot.means,decreasing=TRUE)])

pearson.dtable <- data.frame(pearson.boot.means, pearson.boot.sd)
colnames(pearson.dtable) <- c("mean", "sd")
pearson.dtable[order(pearson.boot.means, decreasing=TRUE),]

write.table(pearson.dtable, file="results/pearson_gene_exp_table.csv", quote=FALSE, sep=",")
write.table(pearson.boot.mat, file="results/pearson_gene_exp_bootstrap.txt")

rm(pearson.boot.mat, pearson.dtable)
