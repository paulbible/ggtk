#!/bin/bash

BENCH=/public/users/paul/dev/ggtk_home/python/pub_scripts/benchmark
sdir=sample_dir

# methods
aonto=(bp mf cc)
asim=(ui gic dic uic)
#asi=(casi mica grasm agrasm sf)

#onto=cc
#sim=res
#si=casi

for onto in ${aonto[*]}
do
  for sim in ${asim[*]}
  do
    out_dir=gene_matrix_dir/${onto}_${sim}
    mkdir $out_dir
    for s in `ls $sdir`
    do
      t=${s#*_}
      t=${t/.txt}
      #echo "$out_dir/matrix_${t}.txt"
      time (./calculate_gene_similarity_matrix_simUI.py -o $onto -e $sdir/$s -g $BENCH/go_data/gene_ontology_edit.obo.2016-12-01 -a $BENCH/go_data/goa_human_2016-11-28.gaf -t $sim  -k $out_dir/matrix_${t}.txt) 2> $out_dir/matrix_${t}_time.txt
    done
  done
done

