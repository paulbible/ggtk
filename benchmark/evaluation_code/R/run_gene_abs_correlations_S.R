#########################################################
# gene correlation evaluations, spearman

# Load helper and bootstrapping functions
source("evaluation_functions.R")
source("evaluation_functions_ui.R")

set.seed(42)

onto.list = c("bp", "mf", "cc")
sim.list = c("res", "lin", "jc")
si.list = c("casi", "mica", "grasm", "agrasm", "sf")

data.folder = "gene_correlations"
spearman.files <- generateFilenames(data.folder, "spearman", onto.list, sim.list, si.list)
spearman.labels <- gsub(".txt","",gsub("gene_correlations/spearman_","",spearman.files))

## *** UI methods ********************************* ##
# add UI file names to the list
ui.list <- c("ui", "gic", "dic", "uic")
ui.files <- generateFilenamesUI(data.folder, "spearman", onto.list, ui.list)
ui.labels <- gsub("_new.txt","",gsub("gene_correlations/spearman_","",ui.files))
# ** add the new filenames and labels to the list
spearman.files <- c(spearman.files, ui.files)
spearman.labels <- c(spearman.labels, ui.labels)

# call the functions to load and bootstrap and indifidual file with out keeping all data in memory
spearman.boot.mat <- bootCatMatrix(spearman.files, bootstrap_abs_score_cor_s)
colnames(spearman.boot.mat) <- spearman.labels
spearman.boot.means <- colMeans(spearman.boot.mat)
spearman.boot.sd <- apply(spearman.boot.mat,2,sd)

boxplot(spearman.boot.mat[,order(spearman.boot.means,decreasing=TRUE)])

spearman.dtable <- data.frame(spearman.boot.means, spearman.boot.sd)
colnames(spearman.dtable) <- c("mean", "sd")
spearman.dtable[order(spearman.boot.means, decreasing=TRUE),]

write.table(spearman.dtable, file="results/spearman_abs_gene_exp_table.csv", quote=FALSE, sep=",")
write.table(spearman.boot.mat, file="results/spearman_abs_gene_exp_bootstrap.txt")

rm(spearman.boot.mat, spearman.dtable)
